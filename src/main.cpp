#include <opencv2/opencv.hpp>
#include <filesystem>
#include <iostream>
#include <vector>
#include <string>

const std::string ascii_grayscale = " .:-=+*#%@";

cv::Mat convertToGray(const cv::Mat& image)
{
    cv::Mat gray_image;
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
    return gray_image;
}

cv::Mat resizeImage(const cv::Mat& image, int width, int height) 
{   
    cv::Mat resize_image;
    cv::resize(image, resize_image, cv::Size(width, height));
    return resize_image;
}

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
        }
        ascii_output += '\n';
    }
    return ascii_output;
}

int main()
{
    std::filesystem::path image = "images/icon.jpg";
    cv::Mat img = cv::imread(image);

    int width = 300;
    int height = 150;
    img = resizeImage(img, width, height);

    img = convertToGray(img);

    std::string ascii_art = convertToAscii(img);

    std::cout << ascii_art << std::endl;

    // cv::imshow("_", img);
    // cv::waitKey(0);

    return 0;
}