/* Author Motsoaledi Neo Tshoana
 */
#ifndef frame_hpp
#define frame_hpp

#include <iostream>
#include <opencv2/opencv.hpp>
#include "camera.hpp"

// Handles images that have been captured
// converts and scales down as required
// and also display to screen as required
//
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

// Errors related to the image frame class
//
class FrameError {
    const char* message;
public:
    FrameError (const char* message) : message(message) {}
    
    void Print () {
        std::cout << message << std::endl;
    }
};
#endif /* frame_hpp */
