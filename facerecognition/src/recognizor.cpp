#include "recognizer.hpp"

const char* path = "resources";

Recognizer::Recognizer(){
    model = cv::face::LBPHFaceRecognizer::create();
}
void load(const char* path){
}

void Recognizer::train(const cv::Mat& image){
}
