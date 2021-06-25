#ifndef detector_hpp
#define detector_hpp

#include <iostream>
#include <opencv2/opencv.hpp>
#include "frame.hpp"
#include "recognizer.hpp"
#include "dialogue.hpp"

using cv::CascadeClassifier;

class Detector {
    CascadeClassifier faceDetector;
    Recognizer recognizer;
public:
    Detector();
    void operator()(Frame& frame);
    std::vector<cv::Rect> faceVec; // for grayscale images, not live feed
    std::vector<cv::Rect> lableVec;
    void appendToRecognized(cv::Mat face);
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
