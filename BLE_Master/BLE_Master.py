
from ctypes import sizeof
from turtle import delay
import serial
import serial.tools.list_ports
import re 
import random
import time 
import ast


class BLE_Master:

    def __init__(self,portDesc='STMicroelectronics STLink'):
        self.port       = ''
        self.baudrate   =9600
        self.bytesize   =8
        self.timeout    =2
        self.stopbits   =serial.STOPBITS_ONE
        self.portDesc   =portDesc
        self.seserialPortr = None
        self.ports=[]


        #functions 
        self.listPorts()
        self.initPort()

    def listPorts(self):
        self.ports = serial.tools.list_ports.comports()

    def initPort(self):
        for port, desc, hwid in sorted(self.ports):
            # print("{}: {} [{}]".format(port, desc, hwid))
            if(re.search(self.portDesc, desc)):
                self.port=port
                print(f'{self.port} port type {type(self.port)}')
                self.serialPort = serialPort=serial.Serial(port = 'COM5', baudrate=9600,bytesize=8, timeout=10, stopbits=serial.STOPBITS_ONE)

    def readSerialPort(self,noBytes):
        return self.serialPort.read(size=noBytes)
        # try:
        #     if(self.serialPort.out_waiting > 0):
        #         return self.serialPort.read(size=noBytes)

        # except:
        #     print("Error in reading the port")

    def writeSerialPort(self,BLE_Data):
        return self.serialPort.write(BLE_Data)

    def readBLEdataLog(self,file ='log_BLE_data.txt'):
        BLE_String=''
        data = []
        BLE_Data=[]
        with open(file) as f:
            lines = f.readlines()

        for i in range(0,9):
            BLE_Data.append(lines[random.randrange(0, 10098, 9)+ i].strip())
        for i in BLE_Data:
            BLE_String=BLE_String+i
            BLE_String=BLE_String+','
        # 1,f,1794,1559,151,2,f,1787,1548,150,3,f,1788,1374,132,4,f,1792,1545,150,5,f,1799,1549,148,6,f,1795,1548,153,7,f,1793,1552,152,@,
        # ['1,f,1793,1559,152', '2,f,1788,1548,152', '3,f,1789,1375,133', '4,f,1793,1471,143', '5,f,1800,1475,144', '6,f,1795,1481,148', '7,f,1793,1486,145', '@']
        # ['0,f,1795,1540,152', '1,f,1794,1560,154', '2,f,1788,1547,150', '3,f,1788,1447,142', '4,f,1792,1545,150', '5,f,1800,1474,145', '6,f,1794,1481,148', '7,f,1793,1486,145', '@']
        # print(BLE_String)
        # print(BLE_Data)
        return BLE_String



if __name__ == '__main__':
    BLE=BLE_Master()
    while (1):
        readData = BLE.readSerialPort(2)
        print(readData)
        # BLE_String= BLE.readBLEdataLog()
        if(readData.decode() == 'FD'):
            BLE_String= BLE.readBLEdataLog()
            # print(len(BLE_String.encode(encoding='utf-8'))) #120 bytes length of the data that we are sending to the FGPA
            noBytesSend = BLE.writeSerialPort(BLE_String.encode(encoding='utf-8'))
            # print(f'Number of bytes send {noBytesSend} ')
        else:
            readData = BLE.readSerialPort(2)
            print(readData.decode())
    
    