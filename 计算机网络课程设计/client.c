#include <stdio.h> 
#include<winsock.h>
#pragma comment(lib, "wS2_32.1ib")
#define SERV UDP PORT 6000                                                /*���������̶˿ں�,�Ӿ����������*/
#define SERV_HOST_ADDR "10.60.46.58" /*��������ַ,�Ӿ����������*/        /*�궨��������ӡ������Ϣ*/
#define PRINTERROR(s) fprintf(stderr, "\n��:��d\n", s, WSAGetLastError()) /*���ݱ�ͨ�ŵķ��������ӳ���*/
void DatagramServer(short nPort)
{
    SOCKET theSocket;                /*����һ�����ݱ����͵� socket*/
    theSocket = socket(AF_INET,      //��ַ��
                       SOCK DGRAM,   //socket ����
                       IPPROTO UDP); //Э������:UDP

    /*������*/
    if (theSoCket == INVALID_SOCKET)
    {
        PRINTERROR("socket()");
        return;
    } /*��д��������ַ�ṹ*/
    SOCKADDR_IN saServer;
    saServer.Sin_family = AF_INET;
    saServer, sin addr.s addr = INADDR ANY; //�� WinSock ָ����ַ
    saServer.sin = (nPort);                 //���������̶˿ں� /*����������ַ���Ѵ����� socket ��*/
    int nRet;
    nRet = bind(theSocket,              //Socket ������
                (LPSOCKADDR)&saServer,  //��������ַ
                sizeof(struct SOCkaddt) //��ַ����
    );

    /*������*/
    if (neet == SOCKET_ERROR)
    {
        PRINTERROR("bind()");
        Closesocket(theSocket);
        return;
    }

    /*�ȴ����Կͻ��˵�����*/
    SOCKADDR_IN saClient;
    char szBUf[1024];
    int nLen = sizeof(saclient);

    while (1)
    {
        /*׼����������*/
        memset(szBuf, 0, sizeof(szBuf));
        nRet = recvfrom(theSocket,             //�Ѱ󶨶���
                        socket szBuf,          //���ջ�����
                        sizeof(szBuf),         //��������С
                        0,                     //Flags
                        (LPSOCKADDR)&saclient, //���տͻ��˵�ַ�Ļ�����
                        &nLen);                //��ַ�������ĳ���
        if (nRet > 0)
        {
            /*��ӡ���յ�����Ϣ*/
            printf("\nData received:��s", szBuf);
            /*�������ݸ��ͻ���*/
            strcpy(szBuf, "From the Server");
            sendto(theSocket,                    //�Ѱ󶨵�
                   socket szBuf,                 //���ͻ�����
                   strlen(szBuf),                //�������ݵĳ���
                   0,                            //Flags
                   (LPSOCKADDR)&saclient, nLen); //Ŀ�ĵ�ַ����ַ����
            closesocket(theSocket);
            return;
        }
    }
}
        /*���ݱ���������������*/
        void main()
        {
            WORD wVersionRequested = MAKEWORD(1, 1);
            WSADATA wsaData;
            int nRet;
            short nPort;
            nPort = SERV_UDP_PORT;
            /*��ʼ�� Winsock*/
            nRet = WSAStartUp(wVersionRequested, &wsaData);
            if (wsaData.wVersion != wVersionRequested)
            {
                fprintf(Stderr, "/n Wrong version\n");
                return;
            }
            /*�������ݷ������ӳ���*/
            DatagramServer(nPort);
            /*���� WinSock*/
            WSACleanup();
        }
