#include <iostream>
#include <opencv2/opencv.hpp>
#include "camera.hpp"

#ifndef frame_hpp
#define frame_hpp

class Frame {
    cv::Mat frame, grayFrame;
    
public:
    const cv::Mat& gray();
    void resizeGray(cv::Size scale);
    void drawRect(cv::Rect&);
    void display();
    friend Camera& operator >> (Camera& lhs, Frame& rhs);
    
    ~Frame();
};

class FrameError {
    const char* message;
public:
    FrameError (const char* message) : message(message) {}
    
    void Print () {
        std::cout << message << std::endl;
    }
};
#endif /* frame_hpp */
