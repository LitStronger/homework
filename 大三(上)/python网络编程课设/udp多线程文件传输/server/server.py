import socket
import threading
import struct
import os
import time
def upload(client_addr, filename):
    count = 0
    # f = open(filename, 'wb')
    f = open(os.getcwd()+'/file/'+filename, 'wb')
    print("filename:", filename)

    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    send_data = struct.pack('!HH', 4, count)
    s.sendto(send_data, (client_addr))  # 把将要用于进行数据传输的port发送给客户端
    print("use random_port:",client_addr[1])

    # 文件数据传输
    while True:
        data, client_addr = s.recvfrom(1024)
        count = struct.unpack('!H', data[2:4])  # 数据块编号
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

def download(client_addr, filename):
    count = 0
    print("filename:", filename)
    # f = open(filename, 'rb')
    f = open(os.getcwd()+'/file/'+filename, 'rb')

    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    while True:
        data = f.read(512)
        if str(data) != "b''":
            data = struct.pack('!HH', 3, count) + data # count 块编号
            s.sendto(data, client_addr)
            print(str(count)+'packets')

        else:
            data = struct.pack('!HH', 3, count) + 'end'.encode('gb2312')    # 传输结束 
            s.sendto(data, client_addr)
            break
        data, client_addr = s.recvfrom(1024)
        count+=1
    f.close()
    s.close()
    print("finished!")

def get_list(ip, port):
    path = os.getcwd()+"/file"  # 获取文件夹路径
    dirs = os.listdir(path)
    print("path:",path)
    print("dirs:",dirs)
    udp_server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    dirs = ','.join(dirs).encode('gb2312')  # list转为string并用逗号分隔，再编码
    send_data = struct.pack('!H%ds' %(len(dirs)), 3, dirs)  # 将数据打包
    udp_server.sendto(send_data, (ip, port))    
    print("finished!")

if __name__ == "__main__":
    udp_server = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    msg_server = ("127.0.0.1", 8877)

    udp_server.bind(msg_server)# 绑定端口:
    print("Bind UDP on:",msg_server)
    
    while True:
        data, client_addr = udp_server.recvfrom(1024)
        mode = struct.unpack('!H', data[:2])# 读取操作码

        # 多线程处理      
        if(mode[0] == 0):
            print('connected from %s:%s'%client_addr)
            filename = data[2:].split(b"\x00")[0].decode('gb2312') # 读取文件名
            print('mode:',mode[0]," Upload..")
            my_thread = threading.Thread(target=upload, args=(client_addr, filename))# 创建相应线程
            my_thread.start()# 执行
        if(mode[0] == 1):
            print('connected from %s:%s'%client_addr)
            filename = data[2:].split(b"\x00")[0].decode('gb2312')
            print('mode:',mode[0]," Download..")
            my_thread = threading.Thread(target=download, args=(client_addr, filename))# 创建相应线程
            my_thread.start()
        if(mode[0] == 2):
            print('connected from %s:%s'%client_addr)
            print('mode:',mode[0]," Get list..")
            my_thread = threading.Thread(target=get_list, args=(client_addr))# 创建相应线程
            my_thread.start()
