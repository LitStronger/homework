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
	char buf[MAX_DATA] = "�������Է���˵���Ӧ 0.0 ����ͨ��������ɣ����ڿ��Կ�ʼ��������"; 
	
		
	/*��ʼ��WSA��ע�ᣨlinux������Ҫ��*/ 
	WSADATA ws;
	printf("WSA��ʼ���ķ���ֵ��%d\n",WSAStartup(MAKEWORD(2,2), &ws)); 
	
	
	dest_addr.sin_port =  htons(PORT);
	dest_addr.sin_family = AF_INET;
	printf("AF_INET��ֵ%d\n", AF_INET);//
	dest_addr.sin_addr.s_addr = INADDR_ANY; 
	
	int sockfd = socket(AF_INET,SOCK_STREAM ,IPPROTO_TCP);
	printf("socket�ķ���ֵ����������ֵ����%d\n", sockfd);
	
	int bindfd = bind(sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr));
	printf("bind�����ķ���ֵ��%d\n", bindfd);
	
	int listenfd = listen(sockfd, 5);//������Ӹ�������Ϊ5
	printf("listen�ķ���ֵ��%d\n", listenfd);
	
	int sin_size = sizeof(struct sockaddr_in);//Э���ַ�ĳ��ȣ��ṹ���С�� 
	int acceptfd = accept(sockfd, (struct sockaddr *)&dest_addr, &sin_size);//sockaddr_in
	printf("accept�ķ���ֵ��%d\n", acceptfd);
	
	
	int sendfd = send(acceptfd, buf, strlen(buf), 0);
	printf("send�ķ���ֵ��%d\n", sendfd);
	send(acceptfd, buf, strlen(buf), 0);
	printf("send�ķ���ֵ��%d\n", sendfd);
	send(acceptfd, buf, strlen(buf), 0);	
	//��ѭ���н�����Ϣ 
	int stop_receive_flag = 0; 
	char buf2[MAX_DATA];

	while(!stop_receive_flag){
		printf("�Ըз�������ߵ���ing...\n");
		int recvfd = recv(acceptfd, buf2, MAX_DATA, 0);
		printf("recv�ķ���ֵ��%d\n", recvfd);
		printf("���Կͻ��˵���Ϣ��%s\n", buf2);
		printf("�������\n"); 
		if(buf2[0] == '1'){		//�ͻ���ͨ������1�رշ���� 
			stop_receive_flag = 1; 
		}
	} 
	
	int closefd_accept_fd = closesocket(acceptfd);
	int close_socket_fd = closesocket(sockfd);
	if(closefd_accept_fd == 0){
		printf("�ѹر�accept"); 
	}
	if(close_socket_fd == 0){
		printf("�ѹر�socket");
	}

	while(1);
	WSACleanup();
} 
