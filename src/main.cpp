#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

const std::string ascii_grayscale = " .:-=+*#%@";

cv::Mat convertToGray(const cv::Mat& image)
{
    cv::Mat gray_image;
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
    return gray_image;
}

// cv::Mat resizeImage(const cv::Mat& image, int width, int height) 
// {   
//     cv::Mat resize_image;
//     cv::resize(image, resize_image, cv::Size(width, height));
//     return resize_image;
// }

std::string convertToAscii(const cv::Mat& gray_image)
{
    std::string ascii_output;
    for (int i = 0; i < gray_image.rows; ++i) 
    {
        for (int j = 0; j < gray_image.cols; ++j) 
        {
            uchar pixel_value = gray_image.at<uchar>(i, j);
            int index = pixel_value * (ascii_grayscale.size() - 1) / 255;
            ascii_output += ascii_grayscale[index];
            ascii_output += ' ';
        }
        ascii_output += '\n';   
    }
    return ascii_output;
}

int main()
{   
    cv::VideoCapture capture("images/fff.mp4");
    std::vector<std::string> videos;
    
    while(true)
    {
        cv::Mat frame;
        capture >> frame;

        if (frame.empty())
        {
            break;
        }

        cv::resize(frame, frame, cv::Size(64, 64));
        cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);

        std::string ascii = convertToAscii(frame);
        videos.push_back(ascii);
    }

    for(const auto flam : videos) 
    {
        std::cout << flam;
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }


    std::filesystem::path image = "images/icon.jpg";
    cv::Mat img = cv::imread(image);

    cv::resize(img, img, cv::Size(64, 64));

    // int width = 200;
    // int height = 100;
    // img = resizeImage(img, width, height);

    img = convertToGray(img);

    std::string ascii_art = convertToAscii(img);

    std::cout << ascii_art << std::endl;

    return 0;
}