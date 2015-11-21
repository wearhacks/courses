var inherit = require("util").inherits;
var EventEmitter = require("events").EventEmitter;
var SerialPort = require("serialport").SerialPort;

var cfg = require(require("path").join(__dirname, "..", "..", "configuration.json"));

var DEFAULT_TTY_PORT = cfg.sensorSerial.device || "/dev/ttyACM0";
var DEFAULT_TTY_SPEED = cfg.sensorSerial.speed || 9600;            // Bauds

function GestureAnalyzer(port) {
    var self = this, own = self;

    EventEmitter.call(self);

    own.serialPort = new SerialPort(port || DEFAULT_TTY_PORT, {
        baudrate: DEFAULT_TTY_SPEED
    });

    var buffer = "";

    own.serialPort.on("open", function () {
        console.log("Serial port opened.");

        own.serialPort.on("data", function (data) {
            buffer = buffer + data;

            var lines = buffer.split("\n");

            lines.forEach(function (row, index) {
                if (index + 1 === lines.length) { // last element
                    buffer = row;
                } else {
                    var result = self.processRow(row);
                    !result.error && self.emit("gesture", result);
                }
            });
        });
    });
}

inherit(GestureAnalyzer, EventEmitter);


GestureAnalyzer.prototype.processRow = function processRow(row) {
    var result = {};

    try {
        row = JSON.parse(row);
    } catch (error) {
        result.error = error;
    }

    if (!result.error) {
        if (row.hasOwnProperty("x") && row.hasOwnProperty("y")) {
            result.x = row.x;
            result.y = row.y;
        }
        else if (row.swipe && row.speed) {
            result.swipe = row.swipe;
            result.speed = row.speed;
        }
        else {
            console.error("Hmm?", JSON.stringify(row));
        }
    }

    return result;
};


module.exports = GestureAnalyzer;
