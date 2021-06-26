/* Author Motsoaledi Neo Tshoana
 */
#include "recognizer.hpp"

const char* path = "resources";


Recognizer::Recognizer(){
    model = cv::face::LBPHFaceRecognizer::create(); // model does not store images
    trained = false;
    loadPrevImages(path);
}

// Loads any recognized face from before
// run by constructor
void Recognizer::loadPrevImages(const char* path){
    // update user
    std::cout << "Loading From Database" << std::endl;
    
    // find path where recognized faces are stored
    struct stat folderInfo;
    if (stat( path, &folderInfo ) != 0 ){
        // No Access to this path
        std::cerr << " [Warning]: Cannot find " << path << std::endl;
        mkdir(path, 0777); // create path
        std::cout << " [LOG]: Created directory " <<  path << std::endl;
        return; // nothing to laod
    }
    else if (!( folderInfo.st_mode & S_IFDIR )) {
        // path is not a directory
        std::cerr << " [Error]: " << path << " is not a directory." << std::endl;
        return; // conflicting names will cause irreversible damage
    }
    
    for (const auto & entry : std::filesystem::directory_iterator(path) ){
        // Start reading all files in path
        std::string filepath = entry.path().u8string();
        if (filepath.substr(filepath.length()-4) != ".jpg") // find only images
            continue;
        
        std::cout << filepath << std::endl;
        // image
        images.push_back( cv::imread(filepath, cv::IMREAD_GRAYSCALE));
        // id
        std::string digits = std::regex_replace( filepath,
                                                std::regex("[^0-9]*([0-9]+).*"),
                                                std::string("$1") );
        ids.push_back( std::atoi(digits.c_str()) );
        // name
        int nameStartIndex = strlen(path)+1;
        int nameLength = filepath.length() - nameStartIndex - digits.length() - 4 ; /*4 == .jpg*/
        names.push_back( filepath.substr(nameStartIndex, nameLength ));
    }
    
    if (ids.size() > 0){
        // We loaded at least one face, so there must be an existing model
        std::cout << " [LOG] loading previously trained model" << std::endl;
        model->read(std::string(path) + "/trainer.yml");
        trained=true;
    }
    std::cout << " [LOG] Load complete" << std::endl;
}

// Adds a new face to the database, and trains the model to recognize it
//
void Recognizer::appendToImages(cv::Mat face, std::string person){
    std::string filename =   (person == "")
                               ? "known_but_unamed"   :   person;
    filename += std::to_string(ids.size()) + ".jpg";
    
    // Save on disk
    cv::imwrite(path + ("/" + filename), face);
    // add too memory too
    images.push_back(face);
    ids.push_back(ids.size());
    names.push_back( (person == "") ? "known_but_unamed" :person   );
    // retrain model with added face
    train();
}

// Trains a LBPHFaceRecognizer model
//
void Recognizer::train(){
    std::cout << "Trainning" << std::endl;
    
    // Train and save model
    model->train(images, ids);
    model->write(std::string(path) + "/trainer.yml");
    trained=true;
    
    std::cout << " [LOG] Trained " << images.size() << " faces.";
}

// Attempts to recognize a face
//
void Recognizer::lookup(Frame& frame, std::vector<cv::Rect> facesRecs){
    cv::Mat grayimage = frame.graySnap(); // image with face(s)d
    
    int id;
    double confidence;
    for (auto& rect : facesRecs){
        model->predict( (cv::Mat(grayimage, rect)), id, confidence);
        //confidence of "0" is a perfect match
        if (confidence < 100){
            std::stringstream title;
            title << names[id]
                << " - id: " << ids[id]
                << " -- matches " << round(100 - confidence) << "%";
            
            std::cout << " [LOG] " << title.str() << std::endl;
            
            // Write using font on the image too
            rect.x = rect.x / frame.getXScaleF() + 5; // move rectangle a little right
            rect.y = rect.y / frame.getYScaleF() - 5; // up a little
            cv::putText(frame.liveImageSnap(), title.str(), rect.tl(), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0,0,255), 2); //thickness == 2
        }
        else{
            std::cout << " [LOG] unknown - match success of "
                << round(100 - confidence) << "%" << std::endl;
        }
    }
}

// Getter
bool Recognizer::isReady(){
    return trained;
}
