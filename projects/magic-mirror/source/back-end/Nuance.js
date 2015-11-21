var Request = require("request");
var ReadableStream = require("stream").Readable;
var helper = require("lodash");


function Nuance() {
	if(this.constructor === Store) {
		throw new Error("Abstract!");
	}
}

Nuance.sendSpeechForTextRecognition = function send(input, options, callback) {
/*
	if(!(input instanceof ReadableStream)) {
		throw new Error("Invalid input!");
	}
//*/
	if(typeof arguments[1] === "function") {
		callback = arguments[1];
		options = {};
	}

	options = helper.merge({
		endPoint: "https://dictation.nuancemobility.net/NMDPAsrCmdServlet/dictation",
		applicationId: undefined,
		applicationKey: undefined,
		language: "fr"
	}, options);

	log("Nuance> Sending speech for text recognition...");

	input.pipe(new Request({
		url: options.endPoint,
		method: "POST",
		qs: {
			appId: options.applicationId,
			appKey: options.applicationKey,
			id: "C4461956B60B" // TODO: What's that?
		},
		headers: {
			"Content-Type": "audio/x-wav;codec=pcm;bit=16;rate=16000",
			"Transfer-Encoding": "chunked",
			"Accept": "text/plain",
			"Accept-Language": options.language === "fr" ? "fr-CA" : "ENUS"
		}
	}, function(error, response, body) {
		if(!error && (response.statusCode !== 200 || ~body.indexOf("<html>"))) {
			log("Nuance> Server error!", body);
			error = new Error("Error recognizing speech!");
		}

		if(error) {
			return exit(error);
		}

		log("Nuance> Text:", body);

		// TODO: here we may choose randomly(?) between the lines since the first one isn't always the best result
		exit(null, body.split("\n")[0]);
	}));

	function exit() {
		return callback && callback.apply(this, arguments);
	}
};

Nuance.sendTextForSpeechSynthesis = function send(text, options, callback) {
	if(typeof arguments[1] === "function") {
		callback = arguments[1];
		options = {};
	}

	options = helper.merge({
		endPoint: "https://tts.nuancemobility.net/NMDPTTSCmdServlet/tts",
		applicationId: undefined,
		applicationKey: undefined,
		language: "fr"
	}, options);

	log("Nuance> Sending text for speech synthesis...");

	new Request({
		url: options.endPoint,
		method: "POST",
		qs: {
			appId: options.applicationId,
			appKey: options.applicationKey,
			voice: options.voice || (options.language === "fr" ? "Nicolas" : "Fiona")
//			ttsLang: options.language === "fr" ? "fra-CAN" : "eng-USA"
		},
		headers: {
			"Content-Type": "text/plain;charset=utf-8",
			"Accept": "audio/x-wav"
		},
		encoding: null,
		body: text
	}, function(error, response, body) {
		if(error) {
			return exit(error);
		}

		exit(null, body);
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


module.exports = Nuance;