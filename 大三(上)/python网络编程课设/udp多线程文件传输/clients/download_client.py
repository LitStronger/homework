import socket 
import struct
import time

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

addr_msg = ("127.0.0.1", 8877)
filename = 's.zip'


f = open(filename, 'wb')
print(filename)

print("downloading..")
print('start-time:',time.localtime().tm_hour,'h',time.localtime().tm_min,'m',time.localtime().tm_sec,'s')
data = struct.pack('!H8s', 1, (filename).encode('gb2312'))
s.sendto(data, addr_msg)

count = 0
while True:
    data, client_addr = s.recvfrom(1024)
    count = struct.unpack('!H', data[2:4])
    data = data[4:]
    if str(data) != "b'end'":
        f.write(data)
        print('receive '+str(count[0])+' packets')
    else:
        break
    s.sendto('ok'.encode('gb2312'), client_addr)
    # count+=1
f.close()
s.close()
print("finished!")

