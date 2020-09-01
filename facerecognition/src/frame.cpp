#include "frame.hpp"

void Frame::resizeGray(cv::Size scale) {
    cv::resize(grayFrame, grayFrame, scale);
}

const cv::Mat& Frame::gray(){
    return grayFrame;
}

void Frame::drawRect(cv::Rect& face) {
    using cv::Scalar, cv::rectangle;
    // Draw boarder on frame using metrics from face rectangle
    rectangle(frame, face.tl()/0.25, face.br()/0.25, Scalar(0,0,255) ); //0,0,255 = BGR color
}

void Frame::display() {
    imshow("Video Feed", frame );
}

Frame::~Frame() {
    cv::destroyAllWindows(); // Closes all the frames
}
Camera& operator >> (Camera& lhs, Frame& rhs) {
    lhs >> rhs.frame;
    
    if (rhs.frame.empty()){
        throw FrameError("Error: Empty frame. Unable to record.");
    }
    
    // Convert to gray scale
    cv::cvtColor(rhs.frame, rhs.grayFrame, cv::COLOR_BGR2GRAY);
    
    return lhs;
}
