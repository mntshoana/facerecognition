#include "frame.hpp"

void Frame::makeGray() {
    scalex  = 1 / ((float)frame.cols / 640) / 2;
    scaley  = 1 / ((float)frame.rows / 480) / 2;
    cv::Size scale = cv::Size( frame.cols * scalex, frame.rows * scaley);
    cv::resize(grayFrame, grayFrame, scale);
}

const cv::Mat& Frame::graySnap(){
    return grayFrame;
}

const float Frame::getXScaleF(){
    return scalex;
}
const float Frame::getYScaleF(){
    return scaley;
}

cv::Mat& Frame::liveImageSnap(){
    return frame;
}

void Frame::drawRect(cv::Rect& face) {
    using cv::Scalar, cv::rectangle;
    cv::Point topLeft = face.tl();
    cv::Point botRight = face.br();
    
    topLeft.x /= scalex;
    topLeft.y /= scaley;
    
    botRight.x /= scalex;
    botRight.y /= scaley;
    // Draw boarder on frame using metrics from face rectangle
    rectangle(frame, topLeft, botRight, Scalar(0,0,255) ); //0,0,255 = BGR color
}

void Frame::display() {
    imshow("Video Feed", frame );
}

Frame::~Frame() {
    cv::destroyAllWindows(); // Closes all the frames
}
Camera& operator >> (Camera& camera, Frame& frame) {
    camera >> frame.frame;
    
    if (frame.frame.empty()){
        throw FrameError("Error: Empty frame. Unable to record.");
    }
    
    // Convert to gray scale
    cv::cvtColor(frame.frame, frame.grayFrame, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(frame.grayFrame, frame.grayFrame);
    
    return camera;
}

int Frame::getWidth(){
    return frame.cols;
}
int Frame::getHeight(){
    return frame.rows;
}
