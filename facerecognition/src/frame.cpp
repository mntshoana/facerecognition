/* Author Motsoaledi Neo Tshoana
 */
#include "frame.hpp"

// convert image to a gray and scales it down too
//
void Frame::makeGray() {
    // Convert to gray scale
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(grayFrame, grayFrame);
    
    // Scale down
    scalex  = 1/ ( (float)frame.cols / 640) /2;
    scaley  = 1/ ( (float)frame.rows / 480) /2;
    
    // Pack back into
    cv::Size scale = cv::Size( frame.cols * scalex, frame.rows * scaley);
    
    cv::resize(grayFrame, grayFrame, scale);
}

// Getter
const cv::Mat& Frame::graySnap(){
    return grayFrame; // scaled down gray image which is used for detection and recognition
}

// Getter
const float Frame::getXScaleF(){
    return scalex;
}

//Getter
const float Frame::getYScaleF(){
    return scaley;
}

// Getter
cv::Mat& Frame::liveImageSnap(){
    return frame; // original image to be displayed on screen
}

// Draws a rectangle on the image which is too be displayed on the screen
void Frame::drawRect(cv::Rect& face) {
    using cv::Scalar, cv::rectangle;
    
    // scale gray image up to original size
    cv::Point topLeft = face.tl();
    cv::Point botRight = face.br();
    
    topLeft.x /= scalex;
    topLeft.y /= scaley;
    
    botRight.x /= scalex;
    botRight.y /= scaley;
    
    // Draw boarder around face
    rectangle(frame, topLeft, botRight, Scalar(0,0,255) ); // BGR color
}

// Display feed to screen
void Frame::display() {
    imshow("Video Feed", frame );
}

Frame::~Frame() {
    cv::destroyAllWindows(); // Closes all the frames
}

// Allows camera to easily pass feed of images here, and stores for detector and later proceccing
Camera& operator >> (Camera& camera, Frame& frame) {
    camera >> frame.frame;
    
    if (frame.frame.empty()){
        throw FrameError("Error: Empty frame. Unable to record.");
    }
    
    frame.makeGray();
    return camera;
}

// Getter
int Frame::getWidth(){
    return frame.cols;
}
//Getter
int Frame::getHeight(){
    return frame.rows;
}
