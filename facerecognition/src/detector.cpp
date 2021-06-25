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
        recognizer.lookup(frame.graySnap(), faceVec);
    /*
     
     
     cv2.putText(img, str(id), (x+5,y-5), font, 1, (255,255,255), 2)
     cv2.putText(img, str(confidence), (x+5,y+h-5), font, 1, (255,255,0), 1)
     */
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
        recognizer.appendToImages(singleFace);
    }
}
