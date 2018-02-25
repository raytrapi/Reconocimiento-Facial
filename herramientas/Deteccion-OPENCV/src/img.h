#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include <QObject>
#include <QScopedPointer>
#include <QTimerEvent>
#include <stdio.h>
#include <iostream>
#include <QImage>
#include <QBasicTimer>
#include <QDebug>

class Img : public QObject{
    Q_OBJECT

    cv::String imgFileName;
    cv::Mat img;

    public:
        explicit Img(QObject *parent = 0);
        ~Img();
        QImage convertToQImage( cv::Mat frame );
        cv::Mat getImg() const;

    public slots:
        /*void runSlot();
        void cameraIndexSlot(int index);*/
        void cambiarImagen(QString fileName);
        /*void usingVideoCameraSlot(bool value);
        void stopped();/**/
    signals:
        void started();
        void matReady(const cv::Mat &);
    public slots:
};

