 #include <stdio.h>
#include <winsock2.h>
//#include <netinet/in.h>
#define DEST_IP "127.0.0.1"
#define DEST_PORT 3001 
#define MAX_DATA 100 
/*sockaddr_in��ͷ�ļ�#include<netinet/in.h>��#include <arpa/inet.h>��*/
/*
	struct sockaddr_in
	{
		sa_family_t     sin_family;��ַ�壨Address family��
		uint16_t 	    sin_port;  16ΪTCP/UDP�˿ں�
		struct in_addr  sin_addr;  32λIP��ַ
		char 			sin_zero[8];  ��֪����ɶ�� 
	}

*/ 
	/*�ͻ���ģ��*/
int main()
{
	char buf[MAX_DATA] = {};
	struct sockaddr_in dest_addr;
	
	
	/*��ʼ��WSA��ע�ᣨlinux������Ҫ��*/ 
	WSADATA ws;
	printf("WSA��ʼ���ķ���ֵ��%d\n",WSAStartup(MAKEWORD(2,2), &ws)); 
	
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(DEST_PORT);
	dest_addr.sin_addr.s_addr = inet_addr(DEST_IP);
	
/*
	inet_addr������Ҫһ���ַ�����Ϊ����������ַ���ָ
	�����Ե��ʮ���Ƹ�ʽ��ʾ��IP��ַ�����磺192.168.0.16��
	������inet_addr�����᷵��һ���ʺϷ����S_addr��u_long��
	�͵���ֵ��
*/	

	/*�����׽���*/
	int sockfd = socket(AF_INET,SOCK_STREAM ,IPPROTO_TCP);
	printf("socket�ķ���ֵ����������ֵ����%d\n", sockfd);
	
	/*��������*/  /*(int*)&p��ȡp��ַ����ǿ��ת��Ϊint��ָ�루ָ��int�������ݣ�*/ 
	printf("��������ing\n"); 
	int connectfd = connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr));
	printf("connect�ķ���ֵ��%d\n", connectfd);
	if(connectfd < 0){
		printf("connect failed\n");
	
	} 
	else{
		printf("connect succeed\n");
	}
	
	
	int recvfd = recv(sockfd, buf, MAX_DATA, 0); 
	printf("recv�ķ���ֵ�ǣ�%d\n",recvfd);
	printf("%s\n", buf);
	recvfd = recv(sockfd, buf, MAX_DATA, 0); 
	printf("recv�ķ���ֵ�ǣ�%d\n",recvfd);
	printf("%s\n", buf);
	
	int exit = 0;
	char buf2[MAX_DATA] = "adc";
	
	
//connectfd = connect(sockfd,(struct sockaddr *)&dest_addr, sizeof(struct sockaddr));
//	printf("connect����ֵ��%d\n", connectfd);
	while(!exit){
		scanf("%s",buf2);
		printf("����ֵΪ%s\n",buf2);
		int sendfd = send(sockfd, buf2, MAX_DATA, 0);
		printf("send����ֵ��%d\n",sendfd);
	}	
	while(1);
	WSACleanup();
}
