#ifndef frame_hpp
#define frame_hpp

#include <iostream>
#include <opencv2/opencv.hpp>
#include "camera.hpp"

class Frame {
    cv::Mat frame, grayFrame;
    float scalex;
    float scaley;
    
public:
    const cv::Mat& graySnap();
    cv::Mat& liveImageSnap();
    const float getXScaleF();
    const float getYScaleF();
    void makeGray();
    void drawRect(cv::Rect&);
    void display();
    friend Camera& operator >> (Camera& lhs, Frame& rhs);
    
    int getWidth();
    int getHeight();
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
