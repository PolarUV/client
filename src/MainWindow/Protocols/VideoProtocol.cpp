//
// Created by starwalker on 20.07.2021.
//

#include <iostream>
#include "VideoProtocol/VideoProtocol.hpp"

VideoProtocol::VideoProtocol() {
    this->_isOnline = false;
}

VideoProtocol::~VideoProtocol() {
    this->_videoStream.release();
}

void VideoProtocol::Start(const std::string& pipeline) {

    cv::namedWindow("Main", cv::WINDOW_NORMAL);

    cv::UMat inFrame, outFrame;

    this->_videoStream.open(pipeline, cv::CAP_GSTREAMER);

    if (!this->_videoStream.isOpened()) {
        std::cout << "Чё-та стримчанского я не вижу\n";
        return;
    }

    for (;;) {
        this->_videoStream >> inFrame;

        if (inFrame.empty()) {
            std::cout << "Кадров больше нет\n";
            return;
        }

        outFrame = std::move(inFrame);
        cv::waitKey(1);
        cv::imshow("Main", outFrame);
    }

    this->_videoStream.release();
}