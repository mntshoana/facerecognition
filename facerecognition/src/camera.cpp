#include "camera.hpp"

Camera::Camera() {
    cap.open(0); // -0- opens webCamera; -videoFileName- opens video
    if (!cap.isOpened()) {
        throw CameraError("Error: Unable to open web camera or video stream.");
    }
    
    width  = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    
    std::cout << "Camera recording at " << width << 'X' << height << endl;
}

cv::Size Camera::Size() {
    return cv::Size(width, height);
}
Camera::~Camera() {
    cap.release();
}
