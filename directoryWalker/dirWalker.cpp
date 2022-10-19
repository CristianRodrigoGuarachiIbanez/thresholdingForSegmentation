#include "dirWalker.h"

DirWalker::DirWalker(std::string path, int extension){
    directorieswalker(path, extension);
}

DirWalker::~DirWalker(){
    listOfDirs.clear();
    listOfImages.clear();

}

void DirWalker::directorieswalker(std::string path, int extension){
    cv::Mat image;
    std::string fileName, ext;
    //const std::experimental::filesystem::path path{"./"};
    for (const auto & entry : std::experimental::filesystem::directory_iterator(path)){
            fileName = entry.path().string();
            ext = fileName.substr(fileName.length() - extension, fileName.length());
            if(ext.compare(".png")==0){
                
                this->listOfDirs.push_back(fileName);
                // std::cout << " Dir -> "<<fileName  << " size -> " << listOfDirs.size() << std::endl;
                this->listOfImages.push_back(openImage(fileName));   
            }
    }   

}
inline cv::Mat DirWalker::openImage(std::string fileName){
    cv::Mat image = cv::imread(fileName, cv::IMREAD_COLOR);
    if(image.empty()){
        std::cerr << "Error\n";
        std::cerr << "Cannot Read Image\n";
    }else{
        return image;
    }
}