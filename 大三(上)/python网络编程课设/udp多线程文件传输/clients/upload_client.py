import socket
import os
import struct
import time

if __name__ == "__main__":

    s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    addr_msg = ("127.0.0.1", 8877) #server's address

    filename = 'test.zip'
    f = open(filename,'rb')
    count = 0
    while True:
        if count == 0:
            # data = struct.pack('!H8s', 0, (shortname+extension).encode('gb2312'))
            data = struct.pack('!H8s', 0, (filename).encode('gb2312'))
            s.sendto(data, addr_msg)

            data = s.recvfrom(1024)
            new_addr = data[1] # get `ip and random_port` to send data
            
        data = f.read(512)
        if str(data) != "b''":
            data = struct.pack('!HH', 3, count) + data # count 块编号
            s.sendto(data, new_addr)
            print(str(count)+'packets')

        else:
            data = struct.pack('!HH', 3, count) + 'end'.encode('gb2312') # count 块编号
            s.sendto(data, new_addr)
            break
        data, server_addr = s.recvfrom(1024)
        count+=1

    f.close()
    s.close()
