1.想蹭网先解开密码

提示WIFI密码为手机号。下载下来是一个cap包，用wireshark打开。网上查了一下，WIFI连接认证的重点在WPA的四次握手包，也就是eapol协议的包，过滤一下，恰好有四个匹配的包。根据题目提示的密码前七位，使用crunch生成11位的密码字典

```
crunch 11 11 -t 1391040%%%% >>wifipass.txt //生成密码字典
aircrack-ng -w wifipass.txt wifi.cap
```

