var inherit = require("util").inherits;
var EventEmitter = require("events").EventEmitter;
var ChildProcess = require("child_process");
var helper = require("lodash");

var cfg = require(require("path").join(__dirname, "..", "..", "configuration.json"));

function SoundPlayer() {
	EventEmitter.call(this);
}

inherit(SoundPlayer, EventEmitter);


SoundPlayer.prototype.play = function play(options, callback) {
	if(typeof arguments[0] === "function") {
		callback = arguments[0];
		options = {};
	}

	options = helper.merge({
		file: "synthesis.wav",
	      device: (cfg.audioDevice.playback ? "--device=" + cfg.audioDevice.playback : "")
	}, options);

//	options.input = options.input || FileSystem.createReadStream(options.file);

	log("SoundPlayer> Playing...");

//	var command = "play -t s16 -r 16000 -c 1 ${file}";
//	var command = 'aplay --device="hw:1,0" ${file}';
	var command = 'aplay ${device} ${file}';

	command = helper.template(command)(options);

	log("SoundPlayer> Command:", command);

	ChildProcess.exec(command, function(error, output) {
		if(error) {
			return exit(error);
		}

		exit();
	});

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


module.exports = SoundPlayer;
