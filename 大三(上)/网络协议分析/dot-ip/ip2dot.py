import IPy
def is_ip(address):
    try:
        IPy.IP(address)
        return True
    except Exception as e:
        print("e: ",e)
        return False

def ip2dot(digit):
    result = []
    digit = int(digit)
    for i in range(4):
        digit, mod = divmod(digit, 256)
        result.insert(0,mod)
    return '.'.join(map(str,result))
ip = input()
print(ip2dot(ip))