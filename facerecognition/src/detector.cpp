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
    faceDetector.detectMultiScale(frame.gray(), vec);
}
