#ifndef recognizer_hpp
#define recognizer_hpp

#include <iostream>
#include <filesystem>
#include <regex>

#include <sys/types.h>
#include <sys/stat.h>

#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp> // make sure to also install open_contrib extension

class Recognizer {
    cv::Ptr<cv::face::FaceRecognizer> model;
    std::vector<cv::Mat> images;
    std::vector<int> ids;
    bool trained;
public:
    Recognizer();
    void loadPrevImages(const char* path);
    void appendToImages(cv::Mat face);
    void train();
    void lookup(cv::Mat frame, std::vector<cv::Rect> faces);
    bool isReady();
};
#endif
