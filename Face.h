//
// Created by prostoichelovek on 21.07.19.
//

#ifndef FACES_FACE_H
#define FACES_FACE_H


#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/face.hpp>

#include "MyClassifier.hpp"
#include "utils.hpp"

namespace Faces {

    class Face {
    public:
        cv::Rect rect;

        cv::RotatedRect rect_normalized;

        int confidence = 0;

        const static int minOffset = 5;
        cv::Point offset; // distance between current position and last

        const static int minLabelNotChanged = 5;
        long labelNotChanged = 0; // number of consecutive label recognitions

        // in most cases use getLabel instated
        int label = -3;

        Face *last = nullptr;

        std::map<std::string, int> executedCallbacks;

        std::vector<cv::Point> landmarks;

        cv::Mat img; // this is aligned face when using dlib

#ifdef USE_DLIB
        // 128D desciptor generated by DNN
        descriptor_type descriptor;
#endif

        Face() = default;

        Face(cv::Point p1, cv::Point p2, int label);

        bool checkBounds(const cv::Size &imgSize);

        void setLast(Face *f);

        void setLabel(int lbl);

        // -1 -- not recognized
        // -2 -- label changed recently
        // -3 -- label has not been set
        int getLabel() const;

        bool hasMoved() const;

        bool operator==(const Face &f);

        bool operator!=(const Face &f);
    };

}

#endif //FACES_FACE_H
