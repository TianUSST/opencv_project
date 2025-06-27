#pragma once
#include<netinet/in.h>
#include<thread>
#include<vector>
#include<opencv2/core.hpp>

//封装服务器类
class TcpServer
{
    public:
        TcpServer(int port);
        ~TcpServer();
        void start();//开始通信
    private:
        int server_fd;//服务器文件描述符
        int port;//端口号
        struct sockaddr_in address;
        bool isRunning;
        void acceptConnections();
        void handleClient(int clnt_sock);

        struct clientContext
        {
            std::vector<uchar> imageBuffer;//存放图像
            bool hasImage = false;//是否有图片
            std::vector<std::string> params;//命令类型可变参数，后续需要分割解析
            cv::Mat decodedImg;
        };

        void handleImagePacket(int client_fd, struct clientContext& ctx);
        void handleCommandPacket(int client_fd, struct clientContext& ctx);

        bool readNBytes(int sock,uint32_t* buffer,size_t n);//从sock读取n个字节，放入buffer缓冲区
      
};