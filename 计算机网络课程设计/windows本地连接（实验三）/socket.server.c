#include <stdio.h>
#include <winsock2.h>
//#include <netinet/in.h>
#define MAX_DATA 100
#define PORT 3001 
//#define IP 127.0.0.1 
//#define AF_INET 2
int main()
{
	struct sockaddr_in dest_addr;
	char buf[MAX_DATA] = "我是来自服务端的响应 0.0 传输通道建立完成！现在可以开始发东西啦"; 
	
		
	/*初始化WSA，注册（linux下则不需要）*/ 
	WSADATA ws;
	printf("WSA初始化的返回值：%d\n",WSAStartup(MAKEWORD(2,2), &ws)); 
	
	
	dest_addr.sin_port =  htons(PORT);
	dest_addr.sin_family = AF_INET;
	printf("AF_INET的值%d\n", AF_INET);//
	dest_addr.sin_addr.s_addr = INADDR_ANY; 
	
	int sockfd = socket(AF_INET,SOCK_STREAM ,IPPROTO_TCP);
	printf("socket的返回值（描述符的值）：%d\n", sockfd);
	
	int bindfd = bind(sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr));
	printf("bind函数的返回值：%d\n", bindfd);
	
	int listenfd = listen(sockfd, 5);//最大连接个数设置为5
	printf("listen的返回值：%d\n", listenfd);
	
	int sin_size = sizeof(struct sockaddr_in);//协议地址的长度（结构体大小） 
	int acceptfd = accept(sockfd, (struct sockaddr *)&dest_addr, &sin_size);//sockaddr_in
	printf("accept的返回值：%d\n", acceptfd);
	
	
	int sendfd = send(acceptfd, buf, strlen(buf), 0);
	printf("send的返回值：%d\n", sendfd);
	send(acceptfd, buf, strlen(buf), 0);
	printf("send的返回值：%d\n", sendfd);
	send(acceptfd, buf, strlen(buf), 0);	
	//在循环中接收信息 
	int stop_receive_flag = 0; 
	char buf2[MAX_DATA];

	while(!stop_receive_flag){
		printf("性感服务端在线等撩ing...\n");
		int recvfd = recv(acceptfd, buf2, MAX_DATA, 0);
		printf("recv的返回值：%d\n", recvfd);
		printf("来自客户端的消息：%s\n", buf2);
		printf("接收完成\n"); 
		if(buf2[0] == '1'){		//客户端通过发送1关闭服务端 
			stop_receive_flag = 1; 
		}
	} 
	
	int closefd_accept_fd = closesocket(acceptfd);
	int close_socket_fd = closesocket(sockfd);
	if(closefd_accept_fd == 0){
		printf("已关闭accept"); 
	}
	if(close_socket_fd == 0){
		printf("已关闭socket");
	}

	while(1);
	WSACleanup();
} 
