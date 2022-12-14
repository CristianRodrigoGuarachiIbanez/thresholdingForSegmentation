#ifndef OBJECTDETECTOR_H
#define OBJECTDETECTOR_H

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/types.hpp>
#include <iostream>
#include <string>

namespace ObjDet{

    struct Limits
    {
        int area;
        int height;
        int width;
    };
    
    struct COORDINATES{
        int tlx, tly ,brx, bry;
    };

    #pragma once
        enum Object {HAND, ARM, OBJECT};
    #pragma once

    class ObjectElements{
        public:
            Object object;
            cv::Point position;
            cv::Rect rect;

            ObjectElements();
            ObjectElements(Object object, cv::Rect rect, int x, int y);
    };

    class ObjectDetector{
        public:
            
            
            ObjectDetector(cv::Mat&image);
            ObjectDetector(cv::Mat&src, int lowLimit[3], int highLimit[3], Limits limit, Object object, bool iso);
            ~ObjectDetector();
            void searchForContoursWithArrayRange(int lowLimit[3], int highLimit[3], Limits limits, Object object, bool iso, bool obj);
            void getChannels(std::string colorSpace);
            std::vector<COORDINATES> getObjectCoordinates();

            cv::Mat getBackground(){
                if(background.empty()){
                    std::cerr << "Error\n";
                    std::cerr << "Cannot Read Image Background\n";
                }else{

                    return background;
                }
            }
            cv::Mat getImage(){
                if(img.empty()){
                    std::cerr << "Error\n";
                    std::cerr << "Cannot Read Image\n";
                }else{

                    return img;
                }
            }
     
            std::vector<cv::Mat> splittedChannels(){
                if(spl.size()!=0){
                    return spl;
                }else{
                    std::cerr<<"vector is empty/n";
                }
            }

            cv::Mat getIsolatedImage(){
                if(isolatedImage.empty()){
                    std::cerr << "Error\n";
                    std::cerr << "Cannot Read isolated Image\n";
                }else{
                        return isolatedImage;
                }
            }

        private:

            cv::Scalar low;
            cv::Scalar high;
            cv::Mat background, img, isolatedImage;
            cv::Mat blue, green, red;
            std::vector<cv::Mat> spl;
            std::vector<ObjectElements> OBJECTS;
            std::vector<cv::Rect>srcRects;

            void selectImage(cv::Mat&src, cv::Mat&img, int imageChannels);
            void duplicateMat(cv::Mat&src, cv::Mat&target);
            void getObject( cv::Mat&img, cv::Scalar low, cv::Scalar high, Limits limits, Object object, bool iso, bool obj);
            void drawObject(cv::Mat&background);
            void drawNMSObject(cv::Mat&background, std::vector<cv::Rect>&Rects, Object object);
            void isolateObject(cv::Mat&inputHSV, cv::Mat&resultHSV, cv::Mat&mask, cv::Scalar minHSV, cv::Scalar maxHSV);
            void splitChannels(cv::Mat&image, cv::Mat&r, cv::Mat&g, cv::Mat&b);
            void NonMaxSupp(std::vector<cv::Rect> srcRects, std::vector<cv::Rect> resRects, float threshold, float neighboors);
    };
}

#endif /*  OBJECTDETECTOR_H */