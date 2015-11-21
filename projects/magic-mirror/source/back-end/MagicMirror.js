var Path = require("path");
var EventEmitter = require("events").EventEmitter;
var FileSystem = require("fs");
var HTTP = require("http");
var helper = require("lodash");
var Flow = require("async");
var Request = require("request");
var WebSocket = require("socket.io");
var Express = require("express");
var SoundRecorder = require("./SoundRecorder");
var SoundPlayer = require("./SoundPlayer");
var Nuance = require("./Nuance");

var DEFAULT_HTTP_SERVER_PORT = 8080;

var configuration = require("../../configuration.json");


function Mirror() {
	var self = this, own = self;

	own.servers = {
		HTTP: undefined,
		WS: undefined
	};
	own.application = undefined;
	own.activity = new EventEmitter();

	own.language = "fr";

	own.activity.on("error", function(error) { log("Mirror> WTF?!", error); });
}

Mirror.prototype.start = function start(callback) {
	var self = this, own = self;

	var sequence = [
		startHTTPServer,
		setUpRoutes,
		startWSServer,
		afterWSServerIsStarted
	];

	function startHTTPServer(callback) {
		var server = own.servers["HTTP"] = HTTP.createServer();

		server.listen(DEFAULT_HTTP_SERVER_PORT, function() {
			log("HTTP> Listening (" + own.servers["HTTP"].address().port + ")...");

			callback(null, server);
		});
	}

	function setUpRoutes(server, callback) {
		var application = own.application = Express();

		application.use(Express.static(Path.resolve(__dirname, "..", "front-end")));

		application.use(require("body-parser").text());
		application.use(require("method-override")());

		application.post("/gesture", function(request, response, next) {
			response.statusCode = 202;
			response.end();

			self.handleGesture(request.body);
		});

		application.post("/stop", function(request, response, next) {
			response.statusCode = 202;
			response.end();

			self.recording = false;
		});

		application.put("/language", function(request, response, next) {
console.log("Mirror> Language:", request.body);
			own.language = request.body;
			response.statusCode = 200;
			response.end();
		});

		server.on("request", own.application);

		callback(null, application);
	}

	function startWSServer(application, callback) {
		var server = own.servers["WS"] = WebSocket.listen(own.servers["HTTP"]);
		log("WS> Listening...");

		server.on("connection", function(socket) {
			log("WS> Socket connected!");

			["gesture", "recording", "processing", "speech", "problem"].forEach(function(event) {
				own.activity.on(event, function() {
					socket.emit.apply(socket, [event].concat(helper.toArray(arguments)));
				});
			});
		});

		callback(null, server);
	}

	function afterWSServerIsStarted(server, callback) {
		own.soundRecorder = new SoundRecorder();
		own.soundPlayer = new SoundPlayer();

		callback(null);
	}

	Flow.waterfall(sequence, function(error) {
		if(error) {
			return log(error);
		}

		console.log("Mirror> Started!");

		callback && callback();
	});
};

Mirror.prototype.handleGesture = function handle(gesture, callback) {
	var self = this, own = self;

	if (gesture.swipe === 'far' || gesture.swipe === 'near') {
		own.soundPlayer.play({file: "synthesis.wav"});
        } else if (true/* TODO: actually handle "up" gesture */ || gesture.swipe && gesture.swipe === "up") {
		var sequence = [
			recordSpeech,
			sendSpeechForTextRecognition,
			sendTextForSpeechSynthesis,
			playSpeech
		];

		function recordSpeech(callback) {
			own.soundRecorder.record(function(error, file) {
				log("Mirror> Done recording:", file);

				if(error) {
					return callback(error);
				}

				var input = FileSystem.createReadStream(file);

				callback(null, input);
			});

			own.activity.emit("recording");
		}

		function sendSpeechForTextRecognition(input, callback) {
			var options = {
				applicationId: configuration["Nuance"].applicationId,
				applicationKey: configuration["Nuance"].applicationKey,
				language: own.language
			};

			Nuance.sendSpeechForTextRecognition(input, options, callback);

			own.activity.emit("processing");
		}

		function sendTextForSpeechSynthesis(text, callback) {
			var options = {
				applicationId: configuration["Nuance"].applicationId,
				applicationKey: configuration["Nuance"].applicationKey,
				language: own.language
			};

			Nuance.sendTextForSpeechSynthesis(text, options, callback);

			// Hack for switching from French to English, and back...
			if(new RegExp("\\b(aim|voudr|veu).+\\bparl(é|er).+\\banglais", "i").test(text)) {
				own.language = "en";
			}
			else if(new RegExp("\\b(like|love).+\\bspeak.+\\bfrench", "i").test(text)) {
				own.language = "fr";
			}

			own.activity.emit("speech", text);
		}

		function playSpeech(contents, callback) {
			FileSystem.writeFile("synthesis.wav", contents, function(error) {
				own.soundPlayer.play({file: "synthesis.wav"}, callback);
			});
		}

		!self.recording && setImmediate(function() {
			Flow.waterfall(sequence, function(error) {
				self.recording = false;

				error && own.activity.emit("problem", error);

				exit.apply(this, arguments);
			});
		});

		self.recording = true;
	}

	own.activity.emit(gesture);

	function exit() {
		return callback && callback.apply(this, arguments);
	}
};


function log() {
	if(arguments[0] instanceof Error) {
		return dumpError(arguments[0]);
	}

	return console.log.apply(console, arguments);
}

function dumpError(error) {
	console.error(error.stack);
}


module.exports = Mirror;
