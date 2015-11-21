#!/usr/bin/env node

var Request = require("request");
var FileSystem = require("fs");

var cfg = require(require("path").join(__dirname, "..", "configuration.json"));


var index = process.argv.indexOf("-i");
if(index < 0) {
	console.log("Please specify the text string to send with `-i`.");
	process.exit(1);
}

var Nuance = require("../source/back-end/Nuance");

var input = process.argv[index + 1];
console.log(process.cwd());

var options = {
	applicationId: cfg.Nuance.applicationId,
	applicationKey: cfg.Nuance.applicationKey,
	language: "fr"
};

Nuance.sendTextForSpeechSynthesis(input, options, function(error, result) {
	error && console.error(error.stack);
 	FileSystem.writeFile("synthesis.wav", result);
	console.log("Byte Length: " + result.length);
});
