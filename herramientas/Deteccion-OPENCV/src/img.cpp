#include "img.h"

cv::Mat Img::getImg() const
{
    return img;
}

Img::Img(QObject *parent) : QObject(parent){

}
Img::~Img(){

}

void Img::cambiarImagen(QString fileName){
    imgFileName=fileName.toStdString().c_str();
    img=cv::imread(imgFileName, CV_LOAD_IMAGE_COLOR);
    if(!img.data){
         std::cout<<"Error al cargar la imagen";
    }else{
        emit matReady(img);
    }
}

