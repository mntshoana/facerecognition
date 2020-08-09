#include <iostream>
#include <opencv2/opencv.hpp>

#include <vector>
#include <string>

using std::endl;

using cv::imshow, cv::imwrite;
using cv::Mat;
using cv::VideoCapture, cv::CascadeClassifier;

//
// Capture faces from video
//  - Stores captured faces
//
int main(int argc, char* argv[]) {
    VideoCapture cap(0); // -0- opens webCamera; -videoFileName- opens video
    if (!cap.isOpened()) {
        std::cout << "Error: Unable to open web camera or video stream." << endl;
        return -1;
    }
    
    while (true) {
        Mat frame, grayFrame;
        cap >> frame; // Capture each frame
        if (frame.empty()){
            std::cout << "Error: Empty frame. Unable to record." << endl;
            break;
        }
        
        // Convert to gray scale
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        //imshow( "Video Feed", frame ); // Display
        imshow ("Video Feed", grayFrame); // Display
        char c =  (char) cv::waitKey(20);
        if (c == 27) // ESC
            break;
    }
    return 0;
}
