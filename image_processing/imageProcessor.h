#pragma once
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>
#include<sstream>

class imageProcessor
{
    public:
        static cv::Mat process(const cv::Mat &decodedImg,const std::string& rawCommand);//在内部做分割字符

    private:
        

//分割客户端传来的数据
    static std::pair<std::string, std::vector<std::string>> splitCommand(const std::string& rawCommand);

        
};