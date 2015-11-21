#!/usr/bin/env node
var SoundRecorder = require("../source/back-end/SoundRecorder");

var recorder = new SoundRecorder();

recorder.record(function(error, outputFile) {
    if(error) {
        return console.error(error.stack);
    }

    console.log(outputFile);
});
