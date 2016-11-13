import serial
import time
import datetime
from packages.MasterSlaveCommand import MasterSlaveCommand

# Port
production = '/dev/ttyACM0'
test = '/dev/ttyACM2'

# Serial
devPath = test


# Serial initialize
ser = serial.Serial(devPath, 9600, timeout=None)

if __name__ == "__main__":

    print MasterSlaveCommand
    commands = MasterSlaveCommand()

    try:

        # only print the serial from ardiuno
        while True :
            time.sleep(3)

            # Read from slave
            # string = ser.readline()
            # if string :
            #     rawStr = string.rstrip()
            #     print rawStr

            #write some string from master to slave
            deltaMins = 0
            dt = datetime.datetime.fromtimestamp( time.time() + deltaMins * 60 ).strftime('%Y-%m-%d-%H-%M')
            # ser.write(b"{}\n".format(dt))
            # print dt

            tran = commands.get_CMD_TRAN('slave','master','usb')
            sens = commands.get_CMD_SENS(1)
            irri = commands.get_CMD_IRRI(1,60,30)

            ser.write(b"{}\n".format(tran))
            print tran
            time.sleep(5);

            ser.write(b"{}\n".format(sens))
            print sens
            time.sleep(5);

            ser.write(b"{}\n".format(irri))
            print irri
            time.sleep(5);


    except Exception as e:
        raise
ser.close()
