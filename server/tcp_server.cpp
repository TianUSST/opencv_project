#include"tcp_server.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include"../utils/utils.h"

//服务器类构造函数
//创建套接字、绑定、监听
TcpServer::TcpServer(int port):port(port),isRunning(true)//初始化构造函数
{
    //创建套接字
    server_fd=socket(AF_INET,SOCK_STREAM,0);
    if(server_fd==-1)
    {   
        perror("Socket creation failed!");
        exit(EXIT_FAILURE);
    }
    //设置套接字选项，服务器快速重启
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    //设置服务器地址和要监听的端口号
    memset(&address,0,sizeof(address));
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(port);

    //绑定
    if(bind(server_fd,(struct sockaddr*)&address,sizeof(address))<0)
    {
        perror("Bind failed!");
        exit(EXIT_FAILURE);
    }
    //监听
    if(listen(server_fd,5)<0)
    {
        perror("Listen Failed!");
        exit(EXIT_FAILURE);
    }
    //输出服务器初始化信息和监听的端口号
    std::cout << "Server initialized on port " << port << std::endl;
    //构造函数结束
}

TcpServer::~TcpServer()
{   
    //析构函数，关闭连接
    close(server_fd);
}

//服务器启动
//创建新线程进行客户端请求的接受
void TcpServer::start()
{
    std::cout<<"Waiting for connection..."<<std::endl;
    std::thread acceptThread(&TcpServer::acceptConnections,this);//创建新线程接受来自客户端的连接
    acceptThread.join();//进入阻塞状态
}

//子线程接受连接，分离线程对客户端进行处理，多客户端时实现并发
void TcpServer::acceptConnections()
{
    while(isRunning)
    {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        //创建新套接字，处理客户端请求
        int clnt_sock = accept(server_fd,(struct sockaddr*)&client_addr,&client_len);

        if(clnt_sock>=0)//接受连接请求，打印客户端的ip和端口号
        {
        std::cout<<"Connect from  IP:"<<inet_ntoa(client_addr.sin_addr)
                                        <<" port:"<<ntohs(client_addr.sin_port)<<std::endl;
        
        //创建一个新线程处理客户端请求，调用handleClient函数，传入clnt_sock作为参数
        std::thread t(&TcpServer::handleClient,this,clnt_sock);
        t.detach();
        }

        else//accept返回无效
        {
            perror("Accept failed");
        }
        
    }
}

//对单个客户端进行处理，传入对应的客户端套接字
void TcpServer::handleClient(int clnt_scok)
{
    //读取第一个字节
    uint8_t type;
    int n = recv(clnt_scok, &type, 1, MSG_WAITALL);
    if(n!=1)
    {
        std::cerr<<"Fail to receive packet type! \n";
        return;//读取包类型失败，处理线程结束
    }

    switch (type)
    {
    case 0xA0:
        handleImagePacket(clnt_scok);
        break;
    case 0xB0:
        handleCommandPacket(clnt_scok);
        break;
    default:
        std::cerr << "Unknown packet type received: 0x" << std::hex << (int)type << std::endl;
        break;
    }
}