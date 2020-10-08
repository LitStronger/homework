import IPy
def is_ip(address):
    try:
        IPy.IP(address)
        return True
    except Exception as e:
        print("e: ",e)
        return False

def dot2ip(dot):
    temp = dot.split('.')
    if is_ip(dot):
        ip = int(temp[0])*(256**3) + int(temp[1]) * \
            (256**2) + int(temp[2])*256 + int(temp[3])
        return ip
    else:
        print("Invalid input")
        return False

dot = input()
print(dot2ip(dot))
