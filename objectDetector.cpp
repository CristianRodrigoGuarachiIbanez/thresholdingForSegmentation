#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "objectDetector.h"

namespace ObjDet{

    ObjectElements::ObjectElements(){
    }

    ObjectElements::ObjectElements(Object object, cv::Rect rect, int x, int y){
        this->object = object;
        this->rect = rect;
        this->position = cv::Point(x, y);
    }


    // ---------------------------      ----------------------------
    ObjectDetector::ObjectDetector(cv::Mat&src, int lowLimit[3], int highLimit[3], Limits limit, Object object, bool iso){

        this->duplicateMat(src, this->background);
        int channels = this->background.channels();
        selectImage(src, this->img, channels);
        this->searchForContoursWithArrayRange(lowLimit, highLimit, limit, object, iso);
    }

    ObjectDetector::ObjectDetector(cv::Mat&image){
       
       this->duplicateMat(image, this->background);
       int channels = image.channels();   
       selectImage(image, this->img, channels);
    }

    ObjectDetector::~ObjectDetector(){
        img.release();
        background.release();
        red.release();
        blue.release();
        green.release();
    }

    std::vector<COORDINATES> ObjectDetector::getObjectCoordinates(){
        std::vector<COORDINATES> OBJ;
        COORDINATES coordinates;
        size_t size = OBJECTS.size();
        if(size==0){
            coordinates.tlx = 0;
            coordinates.tly = 0;
            coordinates.brx = 0;
            coordinates.bry = 0;
           OBJ.push_back(coordinates);
        }
        for(unsigned int i =0; i<size; i++){
            coordinates.tlx = OBJECTS[i].rect.tl().x;
            coordinates.tly = OBJECTS[i].rect.tl().y;
            coordinates.brx = OBJECTS[i].rect.br().x;
            coordinates.bry = OBJECTS[i].rect.br().y;
            OBJ.push_back(coordinates);
        }
        return OBJ;
    }

    void ObjectDetector::selectImage(cv::Mat&src, cv::Mat&target, int imageChannels){
        if(imageChannels==2){
            cv::Mat binaryMat(src.size(), CV_8UC1);
            // Apply Thresholding
            cv::threshold(src, binaryMat, 110, 255, cv::THRESH_BINARY);
            cv::bitwise_not(binaryMat, target);

        }else if(imageChannels > 2){

            cv::cvtColor(src, target, cv::COLOR_BGR2HSV);

        }else if(imageChannels < 2){

            duplicateMat(src, target);
        }
    }

    void ObjectDetector::searchForContoursWithArrayRange( int lowLimit[3], int highLimit[3], Limits limits, Object object, bool iso=false){

        
        this->getObject(this->img, cv::Scalar(lowLimit[0], lowLimit[1], lowLimit[2]) , cv::Scalar(highLimit[0], highLimit[1], highLimit[2]), limits, object, iso);
        this->drawObject(this->background);
    }

    void ObjectDetector::duplicateMat(cv::Mat&src, cv::Mat&target){
        src.copyTo(target);
    }

    void ObjectDetector::getObject(cv::Mat&img, cv::Scalar low, cv::Scalar high, Limits limits, Object object, bool iso) {
        
        cv::Mat mask;
        cv::inRange(img, low, high, mask);
        // std::cout<< "low -> " << low[0] << " " << low[1]<< " " << low[2]<< " limits -> " << limits.area<< " " <<iso<<std::endl;
        if(iso){

            isolateObject(img, this->isolatedImage, mask, low, high);

        }
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        
        for (size_t i = 0; i < contours.size(); i++)
        {
            cv::Rect boundRect = boundingRect(contours[i]);

            //std::cout<< " AREA -> "<< boundRect.area() << " WIDTH -> "<< boundRect.width<< " HEIGHT -> "<< boundRect.height <<std::endl;
            if (boundRect.area() > limits.area && (boundRect.width < limits.width || boundRect.height < limits.height)) {
                this->OBJECTS.emplace_back(object, boundRect, boundRect.x + boundRect.width / 2, boundRect.y + boundRect.height / 2);
            }
        }
    }

    void ObjectDetector::drawObject(cv::Mat&background) {
        //std::cout<<"SIZE -> "<<object.size()<<std::endl;
        for (size_t i = 0; i < OBJECTS.size(); i++) {
            switch (OBJECTS[i].object) {
            case ARM:
                //std::cout<< "RECT BLACK -> "<< object[i].rect.tl() << " "<< object[i].rect.br() <<std::endl;
                rectangle(background, OBJECTS[i].rect.tl(), OBJECTS[i].rect.br(), CV_RGB(255, 0, 0), 2);
                break;
            case HAND:
                //std::cout<< "RECT WHITE -> "<< object[i].rect.tl()<<std::endl;
                rectangle(background, OBJECTS[i].rect.tl(), OBJECTS[i].rect.br(), CV_RGB(0, 255, 0), 2);
                break;
            case OBJECT:
                rectangle(background, OBJECTS[i].rect.tl(), OBJECTS[i].rect.br(), CV_RGB(0, 0, 255), 2);
            }
        }
    }
    void ObjectDetector::isolateObject(cv::Mat&inputHSV, cv::Mat&resultHSV, cv::Mat&maskHSV, cv::Scalar minHSV, cv::Scalar maxHSV){

        cv::bitwise_and(inputHSV, inputHSV, resultHSV, maskHSV);
    }

    void ObjectDetector::getChannels(std::string colorSpace){
        if(background.empty()){
            std::cerr << "Error\n";
            std::cerr << "Cannot Read Image\n";
        }
        if(colorSpace.compare("hsv")==0){
            cv::cvtColor(background, background, cv::COLOR_BGR2HSV);
        }else if(colorSpace.compare("YCrCb")==0){
            cv::cvtColor(background, background, cv::COLOR_BGR2YCrCb);
        }else{
                /* */
        }
        blue = cv::Mat(background.rows, background.cols, CV_8UC3);
        green = cv::Mat(background.rows, background.cols, CV_8UC3);
        red = cv::Mat(background.rows, background.cols, CV_8UC3);
        splitChannels(background, blue, green, red);
    }

    void ObjectDetector::splitChannels(cv::Mat&image, cv::Mat&red, cv::Mat&green, cv::Mat&blue){
        /* image: Mat variable is already in RGB format */

            //cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
            cv::split(image, this->spl);
            cv::Mat empty_image(image.rows, image.cols, CV_8UC1);

            // Create red channel
            cv::Mat in1[] = { spl[0], empty_image, empty_image };
            int from_to1[] = { 0,0, 1,1, 2,2 };
            cv::mixChannels( in1, 3, &red, 1, from_to1, 3 );

            // Create green channel
            cv::Mat in2[] = { empty_image, spl[1], empty_image };
            int from_to2[] = { 0,0, 1,1, 2,2 };
            cv::mixChannels( in2, 3, &green, 1, from_to2, 3 );

            // Create blue channel
            cv::Mat in3[] = { empty_image, empty_image, spl[2]};
            int from_to3[] = { 0,0, 1,1, 2,2 };
            cv::mixChannels( in3, 3, &blue, 1, from_to3, 3 );
        
    }

}