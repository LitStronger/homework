1、签到题（BJDCTF）

​	下载附件后得到一个压缩包，解压后得到第二个压缩包，但是第二个压缩包有提示提示，无法打开，用winhex打开发现并不是压缩包，而是张png图片，打开后得到一张二维码，扫码得到flag

​	

2、鸡你太美

​	附件里是两个gif，但第二个无法显示，winhex打开发现缺了文件格式头部缺失（gif的文件头部为GIF89a）

![1584950556875](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1584950556875.png)

​	补全头部

![1584950441737](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1584950441737.png)

​	再打开gif就可以看到flag了

3、Just a rar

​	附件是一个压缩包，需要密码，提示是4位数

​	直接用ARCHPR暴力破解

![1584951081073](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1584951081073.png)

​	解压后得到一张图片，用文本直接打开（这里直接用txt打开）

![1584951223470](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1584951223470.png)

​	得到flag，注意要把中间夹带的空格去掉

4、你猜我是个啥

​	附件zip无法解压，winhex查看，发现是png，修改格式后打开后是张二维码，扫码，提示flag不在这里。

![1584952669358](C:/Users/啦啦啦/AppData/Roaming/Typora/typora-user-images/1584952669358.png)

查看网页源码也没有有用的信息。回头看看winhex内容，在文本末尾找到flag