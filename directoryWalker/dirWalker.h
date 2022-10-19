#include <string>
#include <vector>
#include <iostream>
#include <experimental/filesystem>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/types.hpp>

class DirWalker{
    public:
        DirWalker(std::string path, int extention);
        ~DirWalker();
        std::vector<cv::Mat> images(){
            if(listOfImages.empty()){
                std::cerr << "Error\n";
                std::cerr << "vector images is empty\n";
            }else{

                return listOfImages;
            }
                
        }
        std::vector<std::string> directories(){
            if(listOfDirs.empty()){
                std::cerr << "Error\n";
                std::cerr << "vector strings is empty\n";
            }else{

                return listOfDirs;
            }
        }
    private:
        std::vector<std::string> listOfDirs;
        std::vector<cv::Mat> listOfImages;
        void directorieswalker(std::string path, int extention);
        inline cv::Mat openImage(std::string fileName);

};