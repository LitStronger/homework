import socket
import os
import struct   # 利用pack打包数据
import time

addr_msg = ("127.0.0.1", 8877) # server's address

def upload():
    print('select: upload')
    s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

    print('input file name: ')
    # filename = 'test.zip'
    filename = input()
    f = open(filename,'rb')
    count = 0

    while True:
        if count == 0:
            data = struct.pack('!H8s', 0, (filename).encode('gb2312'))
            s.sendto(data, addr_msg)

            data = s.recvfrom(1024)
            new_addr = data[1] # 把将要用于进行数据传输的port发送给客户端
            
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

    print('finished!','\treceive from:', server_addr,'\n')
    f.close()
    s.close()

def download():
    print('select: download')
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    print('input file name: ')
    # filename = 's.zip'
    filename = input()
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
    f.close()
    s.close()
    print("finished!")

def get_list():
    print('select: get_list')
    addr_msg = ("127.0.0.1", 8877) # server's address

    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    data = struct.pack('!H8s', 2, 'get_list'.encode('gb2312'))
    s.sendto(data, addr_msg)    # send request
    
    data, server_addr = s.recvfrom(1024) # receive
    data = data[2:].decode('gb2312')
    print(data,'\treceive from:', server_addr,'\n')

    s.close()


while True:
    print('####Select mode:')
    print('    0-upload   1-download   2-get files list   3-quit')
  
    mode = input()
    if mode == '0':
        upload()
    elif mode == '1':
        download()
    elif mode == '2':
        get_list()
    elif mode == '3':
        print('goodbye!')
        break
    else:
        print('invalid input')
    
