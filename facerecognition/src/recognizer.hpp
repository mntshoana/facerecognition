#ifndef recognizer_hpp
#define recognizer_hpp

#include <iostream>
#include <filesystem>
#include <regex>

#include <sys/types.h>
#include <sys/stat.h>

#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp> // make sure to also install open_contrib extension

#include "frame.hpp"
class Recognizer {
    cv::Ptr<cv::face::FaceRecognizer> model;
    std::vector<cv::Mat> images;
    std::vector<int> ids;
    std::vector<std::string> names;
    bool trained;
public:
    Recognizer();
    void loadPrevImages(const char* path);
    void appendToImages(cv::Mat face, std::string person);
    void train();
    void lookup(Frame& frame, std::vector<cv::Rect> faces);
    bool isReady();
};
#endif
