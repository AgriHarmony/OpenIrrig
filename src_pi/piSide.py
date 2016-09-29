import serial
import time
import datetime
import sys

# Calibration function ( for 2500mV )
def potting_calibration( mV ):
    return 2.11 * (10**-3) * mV - 0.675
# Dielectric Permittivity ( for 2500mV )
def dp( mV ):
    return 1/( -3.3326*10**-9 * mV**3 + 7.0218*10**-6 * mV**2 -\
    5.11647*10**-3 * mV + 1.30746 )

def get_mV_index( AnalogId ):
    if AnalogId >= 0 :
        return (id+1)*3-1;
    else:
        return null;


def get_timestamp( deltaHour = 0 ):
    return time.time() + deltaHour * 3600;

def get_datetme( ts ):
    return datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d_%H_%M_%S')

"""
Configuration
"""
executeHour = 5 # time of the script to execute
startTime = get_datetme( get_timestamp(0) )
endTimestamp = get_timestamp( executeHour )
endTime = get_datetme( endTimestamp )

devPath = '/dev/ttyACM0'

# Variales initialize
i = 0
rawStr = ''

if __name__ == "__main__":

    print "now:"
    print startTime
    print get_timestamp()
    print "\nstop at:"
    print endTime
    print endTimestamp

    # Serial initialize
    ser = serial.Serial(devPath, 9600, timeout=None)

    if sys.argv[1] != '--test':
        # File open initialize
        dataDir = "./data/{}.csv".format( startTime )
        fp = open(dataDir, "w+")
        fp.write( "#start_time: {}\n".format(startTime) )
        fp.write( "#end_time: {}\n".format(endTime) )

    try:
        while True :
            t = time.time()

            if endTimestamp - t > 0 :

                string = ser.readline()
                if string :
                    rawStr = string.rstrip()
                    strList = rawStr.split(',')

                    print '--------- {}, cnt: {} ---------'.format( get_datetme( get_timestamp(0) ), i )
                    print rawStr
                    i+=1
                    if sys.argv[1] != '--test':
                        fp.write("{}\n".format(rawStr))



                # print round(endTimestamp - t)


    except Exception as e:
        raise
    if sys.argv[1] != '--test':
        fp.close()
