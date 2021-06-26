/* Author Motsoaledi Neo Tshoana
 */
#ifndef my_camera_header
#define my_camera_header

#include <iostream>
#include <opencv2/opencv.hpp>

using cv::VideoCapture;
using cv::imshow, cv::imwrite;
using std::endl;

// Hndles camera
// to allow capturing of live video feed
class Camera {
private:
    VideoCapture cap;
    float width;
    float height;
public:
    Camera();
    ~Camera();
    cv::Size Size();
    
    // allows easier stream notation for captured image to easily be passed into a frame
    template <class T>
    VideoCapture& operator>> (T& frame) {
        return cap >> frame;
    }
};


// Errors related to the camera
//
class CameraError {
    const char* message;
public:
    CameraError(const char* message) : message(message){
        // nothing
    }
    void Print() {
        std::cerr << message << std::endl;
    }
};

#endif
