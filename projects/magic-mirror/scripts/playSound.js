#!/usr/bin/env node
var SoundPlayer = require("../source/back-end/SoundPlayer");

var player = new SoundPlayer();

player.play(function(error, result) {
    console.log(error, result);
});