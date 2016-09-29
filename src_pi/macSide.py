import serial
import time
import datetime

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

def get_current_datetime():
    ts = time.time()
    return datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d_%H_%M_%S')

# Serial initialize
ser = serial.Serial('/dev/cu.usbmodem1421', 9600, timeout=1)

# File open initialize
dataDir = "../data/{}.csv".format( get_current_datetime() )
fp = open(dataDir, "w+")

# Retrieve information
record_cnt = 1000
skip_cnt = 5 #skip first 5 datas for maintain data quality

fp.write( "#record_cnt: {}\n".format(record_cnt) )

# Variales initialize
i = 0
rawStr = ''


try:
    while i < record_cnt + skip_cnt:
        string = ser.readline()
        i+=1
        if string and i > skip_cnt:

            rawStr = string.rstrip()
            strList = rawStr.split(',')
            # sensorVolt = float(strList[2])
            print '--------- {}, cnt: {} ---------'.format( get_current_datetime(), i )
            print rawStr
            fp.write("{}\n".format(rawStr))
            # fp.write("{},{},{}\n".format (strList[6],strList[7],strList[8]))



except Exception as e:
    raise
fp.close()
