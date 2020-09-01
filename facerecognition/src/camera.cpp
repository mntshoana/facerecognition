#include "camera.hpp"

Camera::Camera() {
    cap.open(0); // -0- opens webCamera; -videoFileName- opens video
    if (!cap.isOpened()) {
        throw CameraError("Error: Unable to open web camera or video stream.");
    }
    
    width  = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    scale  = 0.25;
    std::cout << "Camera recording at " << width << 'X' << height << endl;
    std::cout << "Scaling images to " << scale << endl;
}

cv::Size Camera::ScaledSize() {
    return cv::Size(width*scale, height*scale);
}
Camera::~Camera() {
    cap.release();
}
