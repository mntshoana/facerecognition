#include "recognizer.hpp"

const char* path = "resources";

Recognizer::Recognizer(){
    model = cv::face::LBPHFaceRecognizer::create();
    loadPrevImages(path);
    trained = false;
}
void Recognizer::loadPrevImages(const char* path){
    std::cout << "Loading From Database" << std::endl;
    struct stat folderInfo;

    if( stat( path, &folderInfo ) != 0 ){ // No Access
        std::cerr << " [Warning]: Cannot find " << path << std::endl;
        mkdir(path, 0777);
        std::cout << " [LOG]: Created directory " <<  path << std::endl;
        return;
    }
    else if( !( folderInfo.st_mode & S_IFDIR )) {// Not a directory
        std::cerr << " [Error]: " << path << " is not a directory." << std::endl;
        return;
    }
    
    images.clear();
    ids.clear();
    for (const auto & entry : std::filesystem::directory_iterator(path) ){
        std::string filepath = entry.path().u8string();
        if (filepath.substr(filepath.length()-4) != "jpg")
            continue;
        std::cout << filepath << std::endl;
        //from PIL import Image #pillow package
        images.push_back( cv::imread(filepath, cv::IMREAD_GRAYSCALE));
        std::string digits = std::regex_replace( entry.path().u8string(),
                                                std::regex("[^0-9]*([0-9]+).*"),
                                                std::string("$1")
                                                );
        ids.push_back( std::atoi(digits.c_str()) );
    }
    if (ids.size() > 0){
        //load trained model
        train();
        //trained=true;
    }
    std::cout << " [LOG] Load complete" << std::endl;
}

void Recognizer::appendToImages(cv::Mat face){
    std::string filename = "image" + std::to_string(ids.size()) + ".jpg";
    cv::imwrite(path + ("/" + filename), face);
    images.push_back(face);
    ids.push_back(ids.size());
    train();
}

void Recognizer::train(){
    std::cout << "Trainning" << std::endl;
    model->train(images, ids);
    // Save model to trainer.yml
    model->write(std::string(path) + "/trainer.yml");
    
    std::cout << " [LOG] Trained " << images.size() << " faces.";
    trained=true;
}

void Recognizer::lookup(cv::Mat frame, std::vector<cv::Rect> facesRecs){
    int id;
    double confidence;
    for (auto& rect : facesRecs){
        model->predict( (cv::Mat(frame, rect)), id, confidence);
        //confidence of "0" is a perfect match
        // over 100 == poor match
        if (confidence < 100){
            std::cout << " [LOG] id = " << id << " - match success of "
            << round(100 - confidence) << "%" << std::endl;
        }
        else{
            std::cout << " [LOG] unknown - match success of "
                << round(100 - confidence) << "%" << std::endl;
        }
    }
}

bool Recognizer::isReady(){
    return trained;
}
