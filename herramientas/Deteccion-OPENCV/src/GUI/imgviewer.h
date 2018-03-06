#ifndef IMGVIEWER_H
#define IMGVIEWER_H
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include <QWidget>
#include <QImage>
#include <QString>
#include <QFileDialog>
#include <QPainter>
#include <QDebug>
#include <QTimerEvent>
#include <QScopedPointer>
#include <QBasicTimer>
#include <QtGui/QWheelEvent>
#include <vector>

class ImgViewer : public QWidget{
        Q_OBJECT
        QImage image;
        QImage imageOriginal;
        QString sFacecascade;
        QString sEyecascade;
        cv::CascadeClassifier faceCascade;
        cv::CascadeClassifier eyeCascade;
        cv::CascadeClassifier mouthCascade;
        cv::CascadeClassifier noseCascade;
        cv::CascadeClassifier profileCascade;

        //Zona de Camara
        cv::VideoCapture captura;
        QBasicTimer timer;
        bool estaEjecutando=false;
        bool usandoVideoCamara=false;
        int indiceCamara;



        static void borrarMat(void *mat);

    public:
        explicit ImgViewer(QWidget *parent = 0) : QWidget(parent){
            setAttribute(Qt::WA_OpaquePaintEvent);
            sFacecascade = "E:/Desarrollo/Vision/build/bin/clasificadores/haarcascade_frontalface_default.xml";
            // sFacecascade = "haarcascade_frontalface_alt.xml";
            sEyecascade = "E:/Desarrollo/Vision/build/bin/clasificadores/haarcascade_eye.xml";
            faceCascade.load(sFacecascade.toStdString().c_str());
            eyeCascade.load(sEyecascade.toStdString().c_str());
            QString s="E:/Desarrollo/Vision/build/bin/clasificadores/haarcascade_mcs_mouth.xml";
            mouthCascade.load(s.toStdString().c_str());
            s="E:/Desarrollo/Vision/build/bin/clasificadores/haarcascade_mcs_nose.xml";
            noseCascade.load(s.toStdString().c_str());
            s="E:/Desarrollo/Vision/build/bin/clasificadores/haarcascade_profileface.xml";
            profileCascade.load(s.toStdString().c_str());
            indiceCamara=0; //Camara principal
            usandoVideoCamara=false;

        }

    signals:
        void videoLanzado(bool estado);

    public slots:
        void setImage(const QImage & img);
        void setPreImageCV(const cv::Mat &img);
        void setVideoCamara(bool activar);
        void setIndiceCamara(int indice);
        void setVideo( int indice);
        /*void setVideo(QString fichero);*/
        void pararVideo();
        void lanzarVideo();
        void guardarImagen();
        void ponerRejilla(int);
        void ponerFiltro(int);
        void ponerMasInfo(int);
    private:
        void setImageCV(const cv::Mat &img);
        void timerEvent(QTimerEvent * ev);
        void paintEvent(QPaintEvent *);
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        void wheelEvent(QWheelEvent *event);
        void resizeEvent(QResizeEvent *event);
        qreal escala=1;
        qreal zoom=1;
        ulong tiempoZoomAnterior=-1;
        bool botonPulsado[4]={false,false,false,false};
        int xDesplazado=0;
        int yDesplazado=0;
        int posXRaton=0;
        int posYRaton=0;

        bool conRejilla=false;
        bool conFiltro=false;
        bool conMasInfo=false;
        cv::Mat imagenCVOriginal;
        std::vector<cv::Mat *> imagenesResultados;
        bool conImagen=false;
};

#endif // IMGVIEWER_H

