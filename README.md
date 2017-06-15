# OpenIrri 

a open source simple event-driven monitoring tool for conduct irrigation experiment with sensors base on Rasp Pi and Arduino

# Usage
1. Upload arduino firmware "sh ul.sh". 
	PS if you change you developing platform(MacOS or Linux), please change the USB port name in platformio.ini
	You can check the USB port name by "pio device list"
2. Monitor the serial port for check "sh mp.sh"
3. Collect sensor data "python src_pi/pi.py
