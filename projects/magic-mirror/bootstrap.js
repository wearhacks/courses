var MagicMirror = require("./source/back-end/MagicMirror");

// Sensor Option #1 : ZX Distance and Gesture Sensor
var GestureAnalyzer = require("./source/back-end/GestureAnalyzer");

// Sensor Option #2 : APDS9960 RGB Gesture Sensor
// var GestureAnalyzer = require("./source/back-end/GestureAnalyzerApds9960");

var mirror = new MagicMirror();
var gestureAnalyzer;

mirror.start(function() {
	gestureAnalyzer = new GestureAnalyzer();
	gestureAnalyzer.on("gesture", function(gesture) {
		log("GestureAnalyzer> Gesture:", gesture);

		mirror.handleGesture(gesture);
	});

	// FIXME: Dirty trick to refresh page once the HTTP server is started.
	require("child_process").exec(require("path").join(__dirname, "scripts", "refreshHomePage.sh"));
});


function log() {
	if(arguments[0] instanceof Error) {
		return dumpError(arguments[0]);
	}

	return console.log.apply(console, arguments);
}

function dumpError(error) {
	console.error(error.stack);
}
