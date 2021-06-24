#include <vector>
#include <string>

#include "camera.hpp"
#include "frame.hpp"
#include "detector.hpp"
//
// Capture faces from video
//  - Stores captured faces
//
int main(int argc, char* argv[]) {
    try {
        Camera camera;
        Frame frame;
        Detector detector;

        while (true) {
            camera >> frame; // Capture every frame
            frame.makeGray();
            detector(frame);
            
            for (auto& face : detector.vec){
                frame.drawRect(face);
                //ccv::imwrite(std::string("../FacialRecognition/data/User.") + std::to_string(count) + ".jpg", Mat(grayFrame, face)); // Save into  folder
            }
            frame.display();
            char c =  (char) cv::waitKey(20);
            if (c == 27) // c == ESC
                break;
        }
    }
    catch (CameraError ex){
        ex.Print();
        return -1;
    }
    catch (FrameError ex){
        ex.Print();
        return -1;
    }
    catch (DetectorError ex){
        ex.Print();
        return -1;
    }
    return 0;
}
