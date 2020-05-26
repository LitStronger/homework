 #include <stdio.h>
#include <winsock2.h>
//#include <netinet/in.h>
#define DEST_IP "127.0.0.1"
#define DEST_PORT 3001 
#define MAX_DATA 100 
/*sockaddr_in在头文件#include<netinet/in.h>或#include <arpa/inet.h>中*/
/*
	struct sockaddr_in
	{
		sa_family_t     sin_family;地址族（Address family）
		uint16_t 	    sin_port;  16为TCP/UDP端口号
		struct in_addr  sin_addr;  32位IP地址
		char 			sin_zero[8];  不知道有啥用 
	}

*/ 
	/*客户端模拟*/
int main()
{
	char buf[MAX_DATA] = {};
	struct sockaddr_in dest_addr;
	
	
	/*初始化WSA，注册（linux下则不需要）*/ 
	WSADATA ws;
	printf("WSA初始化的返回值：%d\n",WSAStartup(MAKEWORD(2,2), &ws)); 
	
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(DEST_PORT);
	dest_addr.sin_addr.s_addr = inet_addr(DEST_IP);
	
/*
	inet_addr函数需要一个字符串作为其参数，该字符串指
	定了以点分十进制格式表示的IP地址（例如：192.168.0.16）
	。而且inet_addr函数会返回一个适合分配给S_addr的u_long类
	型的数值。
*/	

	/*创建套接字*/
	int sockfd = socket(AF_INET,SOCK_STREAM ,IPPROTO_TCP);
	printf("socket的返回值（描述符的值）：%d\n", sockfd);
	
	/*建立连接*/  /*(int*)&p：取p地址，并强制转化为int型指针（指向int类型数据）*/ 
	printf("尝试连接ing\n"); 
	int connectfd = connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr));
	printf("connect的返回值：%d\n", connectfd);
	if(connectfd < 0){
		printf("connect failed\n");
	
	} 
	else{
		printf("connect succeed\n");
	}
	
	
	int recvfd = recv(sockfd, buf, MAX_DATA, 0); 
	printf("recv的返回值是：%d\n",recvfd);
	printf("%s\n", buf);

	
	int exit = 0;
	char buf2[MAX_DATA] = "adc";
	
	
//connectfd = connect(sockfd,(struct sockaddr *)&dest_addr, sizeof(struct sockaddr));
//	printf("connect返回值：%d\n", connectfd);
	while(!exit){
		printf("input: ");
		scanf("%s",buf2);
		printf("输入值为%s\n",buf2);
		int sendfd = send(sockfd, buf2, MAX_DATA, 0);
		printf("send返回值：%d\n",sendfd);
	}	
	while(1);
	WSACleanup();
}
