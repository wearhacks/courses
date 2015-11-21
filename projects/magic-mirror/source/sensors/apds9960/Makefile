
.PHONY: clean

GestureSensor: GestureSensor.cpp APDS9960_RPi.cpp APDS9960_RPi.h
	g++ -Wall -o $@ GestureSensor.cpp APDS9960_RPi.cpp -lwiringPi
	sudo chown root:root GestureSensor
	sudo chmod u+s GestureSensor
clean:
	rm -f GestureSensor
