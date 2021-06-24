#include "detector.hpp"

Detector::Detector() {
    char haarPath[] = "../facerecognition/data/haarcascade_frontalface_default.xml";
    faceDetector.load(haarPath);
    if (faceDetector.empty()) {
        throw DetectorError("Error: Can't load haarcascade default xml file");
    }
}

void Detector::operator()(Frame& frame){
    vec.clear();
    double scaleFactor = 1.2;
    int minNeighbors = 5;
    int flags = 0;
    cv::Size minSize = cv::Size(frame.getWidth() / 20, frame.getHeight() / 20);
    faceDetector.detectMultiScale(frame.gray(), vec, scaleFactor, minNeighbors, flags, minSize);
}
