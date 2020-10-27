import socket
import struct
addr_msg = ("127.0.0.1", 8877) # server's address

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

data = struct.pack('!H8s', 2, 'get_list'.encode('gb2312'))
s.sendto(data, addr_msg)

print('send')
data, client_addr = s.recvfrom(1024)

data = data[2:].decode('gb2312')
print(data)
