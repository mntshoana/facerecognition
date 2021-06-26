/* Author Motsoaledi Neo Tshoana
 */
#ifndef detector_hpp
#define detector_hpp

#include <iostream>
#include <opencv2/opencv.hpp>
#include "frame.hpp"
#include "recognizer.hpp"
#include "dialogue.hpp"

using cv::CascadeClassifier;

// Face Detecting features are here
//
class Detector {
    CascadeClassifier faceDetector;
    Recognizer recognizer;
public:
    Detector();
    void operator()(Frame& frame);
    std::vector<cv::Rect> faceVec; // for detected faces only on gray scaled down image, not on of the bigger original live feed
    std::vector<cv::Rect> lableVec;
    void appendToRecognized(cv::Mat face);
};

// Errors related to the detector
//
class DetectorError {
    const char* message;
public:
    DetectorError(const char* message) : message(message) {
        // nothing to see here :)
    }
    void Print() {
        std::cout << message << std::endl;
    }
};
#endif /* detector_hpp */
