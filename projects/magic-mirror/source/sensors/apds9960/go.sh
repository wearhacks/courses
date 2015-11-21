make
# sudo chown root:root GestureSensor
# sudo chmod u+s GestureSensor
gpio load i2c
gpio edge 7 falling
sudo ./GestureSensor
