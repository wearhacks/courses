var inherit = require("util").inherits;
var EventEmitter = require("events").EventEmitter;
var ChildProcess = require("child_process");
var helper = require("lodash");

var cfg = require(require("path").join(__dirname, "..", "..", "configuration.json"));

function SoundRecorder() {
	EventEmitter.call(this);
}

inherit(SoundRecorder, EventEmitter);


SoundRecorder.prototype.record = function record(options, callback) {
	if(typeof arguments[0] === "function") {
		callback = arguments[0];
		options = {};
	}

	options = helper.merge({
		file: "recording.pcm"
	}, options);

	log("SoundRecorder> Recording...");

	var command = "rec -t s16 -r 16000 -c 1 ${file} silence -l 1 0:00 5% 0 0:02 5%";
	command = helper.template(command)(options);

	log("SoundRecorder> Command:", command);

	ChildProcess.exec(command, {env: {AUDIODEV: cfg.audioDevice.record}}, function(error, stdout, stderr) {
		console.log('SndRec :: stdout => ' + stdout);
		console.log('SndRec :: stderr => ' + stderr);

		if (error) {
			console.log('SndRec :: error => ' + error);
			return exit(error);
		}

		exit(null, options.file);
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


module.exports = SoundRecorder;
