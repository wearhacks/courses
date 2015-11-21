module.exports = require('./build/myojs.min.js').default
var hub = new Myo.Hub()
var serial = require('serialport')
var lastValue = -20
var sync = 0
var yOffset
var level = 'D090'
var lvl = 0
var difStr = ['Normal','Touchy','Don\'t move a muscle.']

// You may need to change the name of the serial port depending
// on your specific Arduino model. 'ls /dev/tty.usbmodem*' from a 
// terminal window should help work out what name to use.
serialPort = new serial.SerialPort('/dev/tty.usbmodem411', {
	    baudrate: 115200,
        dataBits: 8, 
        parity: 'none', 
        stopBits: 1, 
        flowControl: false 
	})
	hub.on('ready', () => {
   	 console.log('ready')
	})
	hub.on('connect', () => {
        console.log('connected')
    })
    hub.on('frame', (frame) => {
    	var yaw = Math.round(frame.euler.yaw * 28.75 + 90) // Variable defining Myo's yaw axis in a 0-180 range
	
    	/*if(frame.pose.valid == true){
    		console.log(frame.pose)
    	}*/ //prints the ID of a pose, in the case you wish to do your own code adjustments
    	
    	if(sync == 0){
    		serialPort.write(level) //if the Myo is not synced, have the servo straighten out
    	}
    	else if(sync == 1){
		if(frame.pose.type == 3){ // When the Myo recognizes a wave to the left, go to the next difficulty.
			lvl += 1
			if(lvl > 2){
				lvl = 0
			}
			console.log('Selected Level: ' + difStr(lvl))
		}
		if(frame.pose.type == 1){ // If the Myo detects the gesture of a clenched fist, lock the difficulty, and get calibration data.
    		// NOTE: When performing this gesture, the arm should be making an upwards L-shape with the forearm being vertical. This calculates the current arm position as 90 degrees, for being centred in the range. 
            serialPort.write(level)
    		yaw = (yaw - 60) * 2.25
    		yOffset = (90 - yaw)
    		sync = 2
    		console.log(yOffset + ' ' + yaw)
		hub.myo.lock()
		}
    	}
    	else if(sync == 2){
            if(lvl == 0){
        	   yaw = Math.round((((yaw - 60) * 2.25) + yOffset) / 2 + 45)
            }
            else if(lvl == 1){
                yaw = Math.round((((yaw - 60) * 2.25) + yOffset) / 1.5 + 30)
            }
            else if(lvl == 2){
                yaw = Math.round(((yaw - 60) * 2.25) + yOffset)
            }
            if(lastValue != yaw){ // If the data from the Myo has changed, send new data to Arduino
                yaw = ("00" + yaw).slice(-3)
                //console.log('Serial: ' + yaw)
                serialPort.write('D' + String(yaw))
                lastValue = yaw
            }
	
	}
    })
    hub.on('disconnect', () => {
        console.log('disconnect')
    })
    hub.on('onArmUnsync', () => {
    	console.log('DESYNC')
    	sync = 0
    })
    hub.on('onUnlock', () => {
    	if(sync != 1){
    		sync = 1
    		console.log('Synced')
		hub.myo.unlock(1)
    	}
    })
