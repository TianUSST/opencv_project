#include"imageProcessor.h"
#include<opencv2/core.hpp>
#include<iostream>

cv::Mat imageProcessor::process(const cv::Mat& decodedImg, const std::string& rawCommand)
{
    auto [command, args] = splitCommand(rawCommand);

    if (command == "grayscale") 
    {
        if (!args.empty()) throw std::runtime_error("Grayscale should not have arguments.");
        cv::Mat result;
        cv::cvtColor(decodedImg, result, cv::COLOR_BGR2GRAY);
        std::cout<<"ok!!"<<std::endl;
        return result;
    }

    // 其他图像处理逻辑...

    return decodedImg;
}

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
