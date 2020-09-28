import time
import hashlib
from serial import Serial
import serial.tools.list_ports

def findPort():
    ports = serial.tools.list_ports.comports()
    for each in ports:
        com = str(each)
        print(com)
        if 'Silicon' in com:
            com = com.split(' - ')[0]
            print(com)
            return com


def openPort(br=9600, t=1):
    port = findPort()
    try:
        global serial
        serial = Serial(port, baudrate=br, timeout=t)
        if(serial.isOpen()==true):
            print("serial establish successed")
    except Exception as exc:
        print("serial establish failed", exc)


def sendCommand(s):
    s = s + '\n'
    serial.write(str.encode(s))  # 指令转为二进制并发送
    while True:
        s = serial.readline().decode('utf-8').split('\n')[0]  # 接收二进制响应并转为utf8
        if s != '':
            print(s)
            with open("./logs/com_io_logs.txt", mode="a", encoding="utf-8") as f:
                f.write(s)
        else:
            break
            

if __name__ == "__main__":
    openPort(br=9600, t=1)
    with open("./commands.txt", "r", encoding="utf-8") as f:
        list = f.readlines()
        for each in list:
            sendCommand(each)
            time.sleep(3)
