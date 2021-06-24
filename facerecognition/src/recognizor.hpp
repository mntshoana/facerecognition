#ifndef recognizer_hpp
#define recognizer_hpp

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp> // make sure to also install open_contrib extension

class Recognizer {
    cv::Ptr<cv::face::FaceRecognizer> model;
public:
    Recognizer();
    void load(const char* path);
    void train(const cv::Mat& image);
};
#endif
