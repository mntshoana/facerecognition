#include "detector.hpp"

Detector::Detector() {
    char haarPath[] = "../facerecognition/data/haarcascade_frontalface_default.xml";
    faceDetector.load(haarPath);
    if (faceDetector.empty()) {
        throw DetectorError("Error: Can't load haarcascade default xml file");
    }
}

void Detector::operator()(Frame& frame){
    faceVec.clear();
    double scaleFactor = 1.2;
    int minNeighbors = 5;
    int flags = 0;
    cv::Size minSize = cv::Size(frame.getWidth() / 20, frame.getHeight() / 20);
    faceDetector.detectMultiScale(frame.graySnap(), faceVec, scaleFactor, minNeighbors, flags, minSize);
    if (recognizer.isReady())
        recognizer.lookup(frame, faceVec);
    
}

void Detector::appendToRecognized(cv::Mat face){
    if (faceVec.size() == 0){ // no faces detected
        std::cerr << " [ERROR] No face detected. Unable to add face to database.";
    } else {
        int largestIndex = 0;
        int largestValue = 0;
        // find largest rectangle and store its index
        for (int i =0; i < faceVec.size(); i++){
            int value = faceVec[i].width * faceVec[i].height;
            if ( value > largestValue){
                largestValue = value;
                largestIndex = i;
            }
        }
        
        cv::Mat singleFace = cv::Mat(face, faceVec[largestIndex]);
        std::string name = dialogueInput("Please enter a name for this person", "name");
        recognizer.appendToImages(singleFace, name);
    }
}
