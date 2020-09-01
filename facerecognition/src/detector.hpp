#ifndef detector_hpp
#define detector_hpp

#include <iostream>
#include <opencv2/opencv.hpp>
#include "frame.hpp"

using cv::CascadeClassifier;

class Detector {
    CascadeClassifier faceDetector;
public:
    Detector();
    void operator()(Frame& frame);
    std::vector<cv::Rect> vec;
    
};

class DetectorError {
    const char* message;
public:
    DetectorError(const char* message) : message(message) {}
    void Print() {
        std::cout << message << std::endl;
    }
};
#endif /* detector_hpp */
