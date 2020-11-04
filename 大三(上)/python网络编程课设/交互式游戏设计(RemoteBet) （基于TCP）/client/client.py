import socket

num_dict = {0: "一", 1: "二", 2: "三", 3: "四", 4: "五", 5: "六"}
tz_type_dict = {
    'tc': '头彩',
    'dc': '大彩',
    'kp': '空盘',
    'qx': '七星',
    'dd': '单对',
    'sx': '散星',
    'zy': '庄赢'
}
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


def res_print(res):
    print("res", res)
    print("庄家将左手的金盅倒扣在银盘上，玉骰滚了出来。")
    print(touzi[int(res[:1])])
    print("庄家将右手的金盅倒扣在银盘上，玉骰滚了出来。")
    print(touzi[int(res[1:2])])
    print("庄家叫道:", tz_type_dict[res[2:4]])
    print("本次收入:", res[4:])


def main():
    dest_ip = '127.0.0.1'
    dest_port = 8866
    while True:
        tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # 创建套接字socket
        dest_addr = (dest_ip, dest_port)
        tcp_socket.connect(dest_addr)

        recv_data = tcp_socket.recv(1024)  # 预叫头彩信息
        t1 = int(recv_data.decode("utf-8")[:1])
        t2 = int(recv_data.decode("utf-8")[1:2])
        print("====================================================")
        print("  #新开盘！预叫头彩!")
        print("  #庄家将两枚玉骰往银盘中一撒")
        print("  #庄家唱道：头彩骰号是:", num_dict[t1], num_dict[t2])
        print("  #庄家将两枚玉骰扔进两个金盅，一手持一盅摇将起来。买定离手！买定离手！")
        print("====================================================")

        print("格式: <种类> <数量> <盅类型> (以空格隔开)")
        print("种类: tc/dc/kp/qx/dd/sx(头彩/大彩/空盘/七星/单对/散星)")
        print("数量: 金额数")
        print("盅类型: coin/silver/gold(铜/银/金)")
        print("----------------------------------------------------")
        print("示例: tc 2 coin")

        send_data = input("押:")
        tcp_socket.send(send_data.encode("utf-8")) # 发送玩家押注信息

        recv_data = tcp_socket.recv(1024)  # 接收押注结果
        res_print(recv_data.decode("utf-8"))
        print('\n')

        tcp_socket.close()


if __name__ == "__main__":
    main()
