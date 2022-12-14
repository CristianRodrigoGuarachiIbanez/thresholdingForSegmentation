#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<iostream>
//Ball.cpp
#include "objectDetector.h"
#include "directoryWalker/dirWalker.h"

int armLow[] = {98,109,20}; //cv::Scalar(98,109,20); //cv::Scalar((int)(208/2), (int)((83/100)*255), (int)((28/100)*255));
int armHigh[] = {112, 255, 255}; //cv::Scalar(112, 255, 255); //cv::Scalar((int)(213/2), (int)((87/100)*255), (int)((25/100)*255));

int handLow[] = {0, 0, 150};
int handHigh[] = {0, 48, 181};

int objectLow[] = {120, 51, 51};
int objectHigh[] = {180, 255, 76};


int main(int argc, char * argv[]){
    ObjDet::Limits limits;
    limits.area = 130;
    limits.height = 160;
    limits.width = 160;

    std::vector<ObjDet::COORDINATES> objects;

    cv::Mat src = cv::imread("./binocular_view_748.png", cv::IMREAD_COLOR);
    if(src.empty()){
        std::cerr << "Error\n";
        std::cerr << "Cannot Read Image\n";
    }else{

        std::cout<< "loaded" <<std::endl;
    }


    DirWalker dirWalk(argv[1], std::atoi(argv[2]));
    std::vector<cv::Mat> listOfImages = dirWalk.images();
    for(int i = 0; i<listOfImages.size(); i++){ 

        //Binary image
        ObjDet::ObjectDetector BWImage(listOfImages[i]);   
        
        BWImage.searchForContoursWithArrayRange(armLow, armHigh, limits,  ObjDet::Object::ARM, true, false);

        BWImage.searchForContoursWithArrayRange(objectLow, objectHigh, limits, ObjDet::Object::OBJECT, false, false);

         BWImage.searchForContoursWithArrayRange(handLow, handHigh, limits, ObjDet::Object::HAND, false, false);

        //cv::imwrite("segmented_output/img_" + std::to_string(i) + ".png", BWImage.getImage());

        cv::imwrite("segmented_output/back_" + std::to_string(i) + ".png", BWImage.getBackground());
    
       

    }
    return 0;
}