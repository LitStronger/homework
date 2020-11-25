from scapy.all import *
import time

time_end = 0

def pack_callback(packet):
    print ( packet.show() )
    global time_end 
    time_end = time.time() # 结束计时
    # time.sleep(2)

filter_str = 'ip'
time_out = 120 # 120s, 两分钟

time_start=time.time() # 开始计时
packet = sniff(filter=filter_str, prn=pack_callback, timeout=time_out, iface='Intel(R) Dual Band Wireless-AC 3165', count=0)

print('time cost',time_end-time_start,'s') # 打印抓包开始到现在的时间

wrpcap('data.pcap', packet)  #保存为pcap文件

    # if packet['Ether'].payload:
    #     print (packet['Ether'].src)
    #     print (packet['Ether'].dst)
    #     print (packet['Ether'].type)
    # if packet['ARP'].payload:
    #     print (packet['ARP'].psrc)
    #     print (packet['ARP'].pdst)
    #     print (packet['ARP'].hwsrc)
    #     print (packet['ARP'].hwdst)