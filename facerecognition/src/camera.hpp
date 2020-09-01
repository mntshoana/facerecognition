
#ifndef my_camera_header
#define my_camera_header

#include <iostream>
#include <opencv2/opencv.hpp>

using cv::VideoCapture;
using cv::imshow, cv::imwrite;
using std::endl;

class Camera {
private:
    VideoCapture cap;
    float width;
    float height;
    float scale;
public:
    Camera();
    ~Camera();
    cv::Size ScaledSize();
    
    template <class T>
    VideoCapture& operator>> (T& frame) {
        return cap >> frame;
    }
};

class CameraError {
    const char* message;
public:
    CameraError(const char* message) : message(message)
    {}
    void Print() {
        std::cout << message << std::endl;
    }
};
#endif /* my_camera_header */
