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
    limits.area = 130; //<
    limits.height = 180; //>
    limits.width = 180; //>

    std::vector<ObjDet::COORDINATES> objects;

    cv::VideoCapture cap(argv[1]); 
    if(!cap.isOpened()){
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }

    while(1){ 
        cv::Mat frame;
        cap>>frame;
        
        //Binary image
        ObjDet::ObjectDetector BWImage(frame);   
        
        BWImage.searchForContoursWithArrayRange(armLow, armHigh, limits,  ObjDet::Object::ARM, true, true);

        BWImage.searchForContoursWithArrayRange(objectLow, objectHigh, limits, ObjDet::Object::OBJECT, false, true);

        BWImage.searchForContoursWithArrayRange(handLow, handHigh, limits, ObjDet::Object::HAND, false, true);

        //cv::imwrite("segmented_output/img_" + std::to_string(i) + ".png", BWImage.getImage());

        cv::imshow("segmented_output", BWImage.getBackground());
    
        char c=(char)cv::waitKey(25);
        if(c==27)
            break;

    }
    cap.release();
 
    // Closes all the frames
    cv::destroyAllWindows();

    return 0;
}