import random
import socket
import threading


num_dict = {1: "一", 2: "二", 3: "三", 4: "四", 5: "五", 6: "六"}
money_dict = {'gold': '金', 'sliver': '银', 'coin': '铜'}
money_num = {"gold": 50, "sliver": 50, "coin": 50}


def touzi_start():
    res = ""
    num1 = random.randint(0, 5)
    num2 = random.randint(0, 5)
    res = res + str(num1)
    res = res + str(num2)
    # print(res)
    return res


def calcu(touzi, pre_touzi, u_opt):
    u_opt = u_opt.split(' ')
    money = ''
    reward_type = ''
    res = ''  # 返回的数据: reward_type + money
    t1 = int(touzi[:1]) + 1
    t2 = int(touzi[1:2]) + 1
    # print(t1, t2)
    sum = t1 + t2
    p_t1 = int(pre_touzi[:1]) + 1
    p_t2 = int(pre_touzi[1:2]) + 1

    # 判断骰子点型
    if t1 == p_t1 and t2 == p_t2 or t1 == p_t2 and t2 == p_t1:
        reward_type = 'dc'
        print('dc')
        if touzi == pre_touzi:
            print('tc')
            reward_type = 'tc'
    elif t1 != t2 and t1 % 2 == 0 and t2 % 2 == 0:
        reward_type = 'kp'
        print('kp')
    elif t1+t2 == 7:
        reward_type = 'qx'
        print('qx')
    elif t1 % 2 == 1 and t2 % 2 == 1:
        reward_type = 'dd'
        print('dd')
    elif sum == 3 or sum == 5 or sum == 9 or sum == 11:
        reward_type = 'sx'
        print('sx')
    else:
        reward_type = 'zy'

    # 计算奖励
    if u_opt[0] == 'tc':
        if touzi == pre_touzi:
            money = str(int(u_opt[1]) * money_num[u_opt[2]] * 35)
        else:
            money = '0'
    elif u_opt[0] == 'dc':
        if t1 == p_t1 and t2 == p_t2 or t1 == p_t2 and t2 == p_t1:
            money = str(int(u_opt[1]) * money_num[u_opt[2]] * 17)
        else:
            money = '0'
    elif u_opt[0] == 'kp':
        if t1 != t2 and t1 % 2 == 0 and t2 % 2 == 0:
            money = str(int(u_opt[1]) * money_num[u_opt[2]] * 5)
        else:
            money = '0'
    elif u_opt[0] == 'qx':
        if t1+t2 == 7:
            money = str(int(u_opt[1]) * money_num[u_opt[2]] * 5)
        else:
            money = '0'
    elif u_opt[0] == 'dd':
        if t1 % 2 == 1 and t2 % 2 == 1:
            money = str(int(u_opt[1]) * money_num[u_opt[2]] * 3)
        else:
            money = '0'
    elif u_opt[0] == 'sx':
        if sum == 3 or sum == 5 or sum == 9 or sum == 11:
            money = str(int(u_opt[1]) * money_num[u_opt[2]] * 2)
        else:
            money = '0'
    else:
        money = "invalid_input"

    res = reward_type + money
    return res


def game_start(client_socket):
    pre_touzi = touzi_start() # 预叫头彩!
    client_socket.send(pre_touzi.encode("utf-8"))

    recv_data = client_socket.recv(1024)  # 玩家押注
    print("玩家押注: %s" % recv_data.decode("utf-8"))

    touzi = touzi_start() # 正式摇筛子
    res = calcu(touzi, pre_touzi, recv_data.decode("utf-8"))
    
    client_socket.send((touzi+res).encode("utf-8"))  # 把骰子的结果(2位)和押注结果( reward_type(2位) + money )拼接后返回


def main():
    addr = ("127.0.0.1", 8866)

    # 创建套接字
    tcp_server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # 绑定IP和Port
    tcp_server_socket.bind(addr)
    print("run on:", addr)

    # 限制连接数量
    tcp_server_socket.listen(10)
    print("max connection: 10")

    while(True): 
        # 等待客户端的连接, accept返回(conn, address)其中conn是一个新的套接字对象，用于在此连接上收发数据
        client_socket, client_addr = tcp_server_socket.accept()
        print("connect from:", client_addr)
        # 多线程处理
        my_thread = threading.Thread(target=game_start, args=(client_socket,))
        my_thread.start()

    # 关闭套接字
    client_socket.close()
    tcp_server_socket.close()


if __name__ == "__main__":
    main()
