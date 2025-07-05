#include"imageProcessor.h"
#include<opencv2/core.hpp>
#include<iostream>

cv::Mat imageProcessor::process(const cv::Mat& decodedImg, const std::string& rawCommand)
{
    auto [command, args] = splitCommand(rawCommand);

    //灰度化
    if (command == "grayscale") 
    {
        if (!args.empty()) throw std::runtime_error("Grayscale should not have arguments.");
        cv::Mat result;
        cv::cvtColor(decodedImg, result, cv::COLOR_BGR2GRAY);
        std::cout<<"ok!!"<<std::endl;
        return result;
    }
    //水平翻转
    if (command == "flipx") 
    {
        if (!args.empty()) throw std::runtime_error("flip should not have arguments.");
        cv::Mat result;
        cv::flip(decodedImg,result,0);
        std::cout<<"ok!!"<<std::endl;
        return result;
    }
    //垂直翻转
    if (command == "flipy") 
    {
        if (!args.empty()) throw std::runtime_error("flip should not have arguments.");
        cv::Mat result;
        cv::flip(decodedImg,result,1);
        std::cout<<"ok!!"<<std::endl;
        return result;
    }
    //均值滤波
    if(command == "blur")
    {
        if(args.size()<1)
        {
            std::cerr<<"Blur Command needs 1 parameter.\n"<<std::endl;
            return decodedImg;//原样返回
        }
        try {
            int ksize = std::stoi(args[0]);  // 把字符串转为int
            if (ksize % 2 == 0) ksize += 1;  // OpenCV要求核大小为奇数
            cv::Mat result;
            cv::blur(decodedImg, result, cv::Size(ksize, ksize));
            return result;
        } catch (std::exception& e) {
            std::cerr << "Invalid parameter for blur: " << e.what() << std::endl;
        }
        return decodedImg;
    }
    // 其他图像处理逻辑...

    return decodedImg;
}

//解析原始命令，返回一个字符串和一个字符串vector。
std::pair<std::string, std::vector<std::string>> imageProcessor::splitCommand(const std::string& rawCommand)
{
    //创建字符串流
    std::stringstream ss(rawCommand);
    //分割字符
    std::string segment;
    std::vector<std::string> tokens;
    //遇到“|”,分割放入segment
    while(std::getline(ss,segment,'|'))
    {
        tokens.push_back(segment);
    }//示例tokens形式：blur,0.1,5,10
    //分割完成，创建保存指令
    std::string command;
    std::vector<std::string> args;
    if(!tokens.empty())
    {
        command = tokens[0];
        args.assign(tokens.begin()+1,tokens.end());
    }

    return {command,args};
}
