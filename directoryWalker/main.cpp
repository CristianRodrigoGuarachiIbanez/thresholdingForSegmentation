#include "dirWalker.h"


int main(int argc, char * argv[]){

DirWalker dirW(argv[1], std::atoi(argv[2]));
for (int i = 0; i<dirW.directories().size(); i++){
    std::cout << dirW.directories()[i]<< std::endl;

}

for (int i = 0; i<dirW.images().size(); i++){
    //std::cout << dirW.images()[i]<< std::endl;
    cv::imshow("image_" + std::to_string(i) + ".png", dirW.images()[i]);
}
cv::waitKey(0);

}