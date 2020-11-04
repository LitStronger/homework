import socket


def res_print(num):
    touzi = [
        """
    ┌─────┐
    │     │
    │  ●  │
    │     │
    └─────┘""", """
    ┌─────┐
    │  ●  │
    │     │
    │  ●  │
    └─────┘""", """
    ┌─────┐
    │  ●  │
    │     │
    │ ● ● │
    └─────┘""", """
    ┌─────┐
    │ ● ● │
    │     │
    │ ● ● │
    └─────┘""", """
    ┌─────┐
    │ ● ● │
    │  ●  │
    │ ● ● │
    └─────┘""", """
    ┌─────┐
    │ ● ● │
    │ ● ● │
    │ ● ● │
    └─────┘"""
    ]
    
    # num1 = random.randint(0, 5)
    # num2 = random.randint(0, 5)

    print(num)
    # print(touzi[ int(num[:1]) ])
    # print(touzi[ int(num[1:2]) ])


def main():
    # 创建套接字socket
    dest_ip = '127.0.0.1'
    dest_port = 8866
    # 连接服务器
    # dest_ip = input("请输入服务器ip：")
    # dest_port = int(input("请输入服务器port："))

    while True:
        tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        dest_addr = (dest_ip, dest_port)
        tcp_socket.connect(dest_addr)

        # 接收/发送数据
        # send_data = input("请输入要发送的数据：")
        send_data = "1"
        tcp_socket.send(send_data.encode("utf-8"))
        
        recv_data = tcp_socket.recv(1024) # 预叫头彩信息
        print("新开盘！预叫头彩:", recv_data.decode("utf-8"))
        print("庄家将两枚玉骰往银盘中一撒。买定离手！买定离手！")

        print("格式: <种类> <数量> <级别> (以空格隔开)")
        print("种类: tc/dc/kp/qx/dd/sx(头彩/大彩/空盘/七星/单对/散星)")
        print("数量: 金额数")
        print("级别: coin/silver/gold(铜/银/金)")
        print("示例: tc 2 coin")
        send_data = input("押:")

        tcp_socket.send(send_data.encode("utf-8"))

        recv_data = tcp_socket.recv(1024) # 接收结果
        print("结果:", recv_data.decode("utf-8"))
        # res_print(recv_data.decode("utf-8"))

        # 关闭套接字socket
        tcp_socket.close()
    


if __name__ == "__main__":
    main()
