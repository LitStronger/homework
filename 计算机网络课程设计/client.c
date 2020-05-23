#include <stdio.h> 
#include<winsock.h>
#pragma comment(lib, "wS2_32.1ib")
#define SERV UDP PORT 6000                                                /*服务器进程端口号,视具体情况而定*/
#define SERV_HOST_ADDR "10.60.46.58" /*服务器地址,视具体情况而定*/        /*宏定义用来打印错误消息*/
#define PRINTERROR(s) fprintf(stderr, "\n％:％d\n", s, WSAGetLastError()) /*数据报通信的服务器端子程序*/
void DatagramServer(short nPort)
{
    SOCKET theSocket;                /*创建一个数据报类型的 socket*/
    theSocket = socket(AF_INET,      //地址族
                       SOCK DGRAM,   //socket 类型
                       IPPROTO UDP); //协议类型:UDP

    /*错误处理*/
    if (theSoCket == INVALID_SOCKET)
    {
        PRINTERROR("socket()");
        return;
    } /*填写服务器地址结构*/
    SOCKADDR_IN saServer;
    saServer.Sin_family = AF_INET;
    saServer, sin addr.s addr = INADDR ANY; //由 WinSock 指定地址
    saServer.sin = (nPort);                 //服务器进程端口号 /*将服务器地址与已创建的 socket 绑定*/
    int nRet;
    nRet = bind(theSocket,              //Socket 描述符
                (LPSOCKADDR)&saServer,  //服务器地址
                sizeof(struct SOCkaddt) //地址长度
    );

    /*错误处理*/
    if (neet == SOCKET_ERROR)
    {
        PRINTERROR("bind()");
        Closesocket(theSocket);
        return;
    }

    /*等待来自客户端的数据*/
    SOCKADDR_IN saClient;
    char szBUf[1024];
    int nLen = sizeof(saclient);

    while (1)
    {
        /*准备接收数据*/
        memset(szBuf, 0, sizeof(szBuf));
        nRet = recvfrom(theSocket,             //已绑定定的
                        socket szBuf,          //接收缓冲区
                        sizeof(szBuf),         //缓冲区大小
                        0,                     //Flags
                        (LPSOCKADDR)&saclient, //接收客户端地址的缓冲区
                        &nLen);                //地址缓冲区的长度
        if (nRet > 0)
        {
            /*打印接收到的信息*/
            printf("\nData received:％s", szBuf);
            /*发送数据给客户端*/
            strcpy(szBuf, "From the Server");
            sendto(theSocket,                    //已绑定的
                   socket szBuf,                 //发送缓冲区
                   strlen(szBuf),                //发送数据的长度
                   0,                            //Flags
                   (LPSOCKADDR)&saclient, nLen); //目的地址，地址长度
            closesocket(theSocket);
            return;
        }
    }
}
        /*数据报服务器端主程序*/
        void main()
        {
            WORD wVersionRequested = MAKEWORD(1, 1);
            WSADATA wsaData;
            int nRet;
            short nPort;
            nPort = SERV_UDP_PORT;
            /*初始化 Winsock*/
            nRet = WSAStartUp(wVersionRequested, &wsaData);
            if (wsaData.wVersion != wVersionRequested)
            {
                fprintf(Stderr, "/n Wrong version\n");
                return;
            }
            /*调用数据服务器子程序*/
            DatagramServer(nPort);
            /*结束 WinSock*/
            WSACleanup();
        }
