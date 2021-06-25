#include "recognizer.hpp"

const char* path = "resources";

Recognizer::Recognizer(){
    model = cv::face::LBPHFaceRecognizer::create();
    trained = false;
    loadPrevImages(path);
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
    names.clear();
    for (const auto & entry : std::filesystem::directory_iterator(path) ){
        std::string filepath = entry.path().u8string();
        if (filepath.substr(filepath.length()-4) != ".jpg")
            continue;
        std::cout << filepath << std::endl;
        
        // image
        images.push_back( cv::imread(filepath, cv::IMREAD_GRAYSCALE));
        // id
        std::string digits = std::regex_replace( filepath,
                                                std::regex("[^0-9]*([0-9]+).*"),
                                                std::string("$1")
                                                );
        ids.push_back( std::atoi(digits.c_str()) );
        // name
        int nameStartIndex = strlen(path)+1;
        int nameLength = filepath.length() - nameStartIndex - digits.length() - 4 /*.jpg*/ ;
        names.push_back( filepath.substr(nameStartIndex, nameLength ));
    }
    if (ids.size() > 0){
        std::cout << " [LOG] loading previously trained model" << std::endl;
        model->read(std::string(path) + "/trainer.yml");
        trained=true;
    }
    std::cout << " [LOG] Load complete" << std::endl;
}

void Recognizer::appendToImages(cv::Mat face, std::string person){
    std::string filename = (person == "") ? "known_but_unamed"
                                            :   person;
    
    filename += std::to_string(ids.size()) + ".jpg";
    
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

void Recognizer::lookup(Frame& frame, std::vector<cv::Rect> facesRecs){
    int id;
    double confidence;
    cv::Mat grayimage = frame.graySnap();
    for (auto& rect : facesRecs){
        model->predict( (cv::Mat(grayimage, rect)), id, confidence);
        //confidence of "0" is a perfect match
        // over 100 == poor match
        if (confidence < 100){
            std::cout << " [LOG] " << names[id] << " with id  = " << id << " - match success of "
            << round(100 - confidence) << "%" << std::endl;
            
            std::stringstream title;
            title << names[id]
                << " - id: " << ids[id]
                << " -- matches " << round(100 - confidence) << "%";
            
            rect.x = rect.x / frame.getXScaleF() + 5; // a little right
            rect.y = rect.y / frame.getYScaleF() - 5; // up a little
            cv::putText(frame.liveImageSnap(), title.str(), rect.tl(), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0,0,255), 2); //thickness == 2
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
