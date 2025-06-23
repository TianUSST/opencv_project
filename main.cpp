#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::Mat img = cv::Mat::zeros(400, 400, CV_8UC3);
    cv::circle(img, cv::Point(200, 200), 100, cv::Scalar(0, 255, 0), -1);
    cv::imshow("OpenCV Test", img);
    cv::waitKey(0);
    return 0;
}
 