import os
import audioop
import time
import errno
import math
import serial
from time import sleep

#Open the FIFO that MPD has created for us
#This represents the sample (44100:16:2) that MPD is currently "playing"
fifo = os.open('/tmp/mpd.fifo', os.O_RDONLY)
ser = serial.Serial('/dev/ttyACM1', 9600) 
while 1:
    try:
        rawStream = os.read(fifo, 4096)
    except OSError as err:
        if err.errno == errno.EAGAIN or err.errno == errno.EWOULDBLOCK:
            rawStream = None
        else:
            raise

    if rawStream:

            leftChannel = audioop.tomono(rawStream, 2, 1, 0)
            rightChannel = audioop.tomono(rawStream, 2, 0, 1)
            stereoPeak = audioop.max(rawStream, 2)
            leftPeak = audioop.max(leftChannel, 2)
            rightPeak = audioop.max(rightChannel, 2)
            leftDB = 20 * math.log10(leftPeak) -74
            rightDB = 20 * math.log10(rightPeak) -74
            #print(rightPeak, leftPeak, rightDB, leftDB)
            #print(int(leftDB)+int(rightDB))
            #print("Value: ",int(leftDB))
            

            newVol = (int(leftDB)+int(rightDB))
            newVolString = ""+str(int(newVol))
            ser.write(str.encode(newVolString))
            
            for i in range(int(leftDB)+int(rightDB)):
                if (i<20):
                        print("\033[1;32m#\033[1;m",end="");
                elif (i<28):
                        print("\033[1;33m#\033[1;m",end="");
                else:
                        print("\033[1;31m#\033[1;m",end="");
            print("");

            sleep(.02)
