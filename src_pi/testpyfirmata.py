import packages.pyFirmata.pyfirmata.pyfirmata 
import time

board = Arduino('/dev/cu.usbmodem1421')

while true:
	board.digital[13].write(1)
	time.delay(1)
