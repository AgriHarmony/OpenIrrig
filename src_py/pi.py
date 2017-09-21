import argparse
import serial
import time
from threading import Timer
import datetime
import sys

# Calibration function ( for 2500mV )
def potting_calibration( mV ):
    return 2.11 * (10**-3) * mV - 0.675
# Dielectric Permittivity ( for 2500mV ), unadoptable
def dp( mV ):
    return 1/( -3.3326*10**-9 * mV**3 + 7.0218*10**-6 * mV**2 -\
    5.11647*10**-3 * mV + 1.30746 )

def get_datetimestamp( deltaMins ):
    return time.time() + deltaMins * 60
def get_datetime( deltaMins ):
    return datetime.datetime.fromtimestamp( time.time() + deltaMins * 60 ).strftime('%Y-%m-%d-%H-%M')
def get_time( deltaMins ):
    return datetime.datetime.fromtimestamp( time.time() + deltaMins * 60 ).strftime('%H:%M')
def get_today_date( ):
    return datetime.datetime.fromtimestamp( time.time() ).strftime('%Y-%m-%d')
# def display_serial():
#     while True :
#         time.sleep(1)
#         t = time.time()
#
#         if endTimestamp - t > 0 :
#             string = ser.readline()
#             if string :
#                 rawStr = string.rstrip()
#                 # print rawStr
#                 ws = '{},{}\n'.format( get_time(0), rawStr )
#                 print ws
#         else:
#             exit()

# def write_serial2file( fp ):
#     while True :
#         time.sleep(1)
#         t = time.time()
#
#         if endTimestamp - t > 0 :
#             string = ser.readline()
#             if string :
#                 rawStr = string.rstrip()
#                 # print rawStr
#                 ws = '{},{}\n'.format( get_time(0), rawStr )
#                 print ws
#                 fp.write(ws)
#         else:
#             exit()

parser = argparse.ArgumentParser(description='a command line tool for collect arduino data')
parser.add_argument('-t', action='store', type=int, \
    help='set the execute time (unit is min) for scrip, default=5mins', default=5, dest='time')
parser.add_argument('-s', '--save', action='store_true', \
    help='save the collect data to a .csv with current datetime as filename, -s(true),default(false),')
parser.add_argument('-p', action='store', type=str, \
    help='set the default output file path. Default=../data/', default='../data/', dest='path')
parser.add_argument('-m', '--msg', action='store', \
    help='Ask user to input a short message of experimental purpose (it will store in output file)', required=True)

args = parser.parse_args()

"""
Configuration
"""

# Serial
# Mac /dev/cu.usbmodem1421
macLeftUSB = '/dev/cu.usbmodem1421'
production = '/dev/ttyACM0'
test = '/dev/ttyACM2'

devPath = macLeftUSB

# Variales initialize
rawStr = ''

# Header
HEADER = ('time', 'status', 'EC5_A0', 'EC5_A1', 'EC5_A2', '\n')

# Start & End Time
starTimeStr = get_datetime(0)
endTimeStr = get_datetime(args.time)
endTimestamp = get_datetimestamp(args.time)

# Serial initialize
ser = serial.Serial(devPath, 9600, timeout=None)

# Commands
commands = MasterSlaveCommand()

if __name__ == "__main__":
    print args.time
    print args.save
    print args.path
    print args.msg

    # CLI prompt for start script information
    print '-- data collecting script --'
    print 'Start @ {}'.format( get_datetime(0) )
    print 'End @ {}'.format( get_datetime(args.time) )

    try:
        if args.save :
            # Write Meta Data
            dataDir = "{}{}.csv".format( args.path ,get_datetime(0) )
            fp = open(dataDir, "w+")
            fp.write( "#start_time: {}\n".format( starTimeStr, get_datetime(0)) )
            fp.write( "#end_time: {}\n".format(endTimeStr) )
            fp.write( "#purpose: {}\n".format( args.msg ) )
            fp.write( "#command: python piSide.py -t {} -s {} -p {} -m {}\n".\
                format(args.time, args.save, args.path, args.msg))

            # Write Data Column Header
            h = ",".join(HEADER)
            print h
            fp.write('#{}'.format(h))
            # listen to serial from ardiuno then write data to file
            # write_serial2file(fp)
            while True :
                time.sleep(1)
                t = time.time()

                if endTimestamp - t > 0 :
                    string = ser.readline()
                    if string :
                        rawStr = string.rstrip()
                        # print rawStr
                        ws = '{},{}\n'.format( get_time(0), rawStr )
                        print ws
                        fp.write(ws)
                else:
                    exit()

            fp.close()

        else:

            # only print the serial from ardiuno
            while True :
                time.sleep(1)
                t = time.time()

                if endTimestamp - t > 0 :

                    # Write Commands to Ardiuno
                    # ser.write(b"{}\n".format(commands.get_CMD_SENS(0)))
                    # ser.write(b"{}\n".format(commands.get_CMD_SENS(1)))
                    # ser.write(b"{}\n".format(commands.get_CMD_SENS(2)))

                    # Receive Response from Ardiuno
                    string = ser.readline()
                    if string :
                        rawStr = string.rstrip()
                        # print rawStr
                        ws = '${},{}\n'.format( get_time(0), rawStr )
                        print ws
                else:
                    exit()

    except Exception as e:
        raise
