#include <vector>
#include <string>

#include "camera.hpp"
#include "frame.hpp"
#include "detector.hpp"
//
// Capture faces from video
//  - Stores captured faces
//

/* Todo
 font = cv2.FONT_HERSHEY_SIMPLEX
 */
int main(int argc, char* argv[]) {
    try {
        Camera camera;
        Frame frame;
        Detector detector;

        while (true) {
            camera >> frame; // Capture every frame
            frame.makeGray();
            detector(frame);
            
            for (auto& face : detector.faceVec){
                frame.drawRect(face);
            }
            frame.display();
            char c =  (char) cv::waitKey(20);
            if (c == 27) // c == ESC
                break;
            else if (c == '\r'){
                // Add a face to the database
                detector.appendToRecognized(frame.graySnap());
                
            }
            // -1 == no key pressed
            else if (c != (char)-1) // print keys
                std::cout << "Pressed " << c << std::endl;
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
