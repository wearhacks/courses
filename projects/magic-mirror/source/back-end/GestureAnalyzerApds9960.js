var inherit = require("util").inherits;
var EventEmitter = require("events").EventEmitter;

var spawn = require('child_process').spawn;

function GestureAnalyzer () {
    var self = this, own = self;

    EventEmitter.call(self);

    // WARNING! Hardcoded filepath. When not reachable we get the obscur error:
    //	events.js:72
    //		throw er; // Unhandled 'error' event
    //		      ^
    //	Error: spawn ENOENT
    //	    at errnoException (child_process.js:1000:11)
    //	    at Process.ChildProcess._handle.onexit (child_process.js:791:34)

    var sensor = spawn('source/sensors/apds9960/GestureSensor');

    sensor.stdout.on('data', function (row) {
        console.log('ROW: ' + row)

        var result = self.processRow(row);
        !result.error && self.emit("gesture", result);
    });
}

inherit(GestureAnalyzer, EventEmitter);

GestureAnalyzer.prototype.processRow = function processRow (row) {
    var result = {};

    try {
        row = JSON.parse(row)
    } catch (error) {
        result.error = error;
    }

    if (!result.error) {
        if (row.swipe) {
            result.swipe = row.swipe;
        }
        else {
            console.error("Hmm?", JSON.stringify(row));
        }
    }

    return result;
};


module.exports = GestureAnalyzer;
