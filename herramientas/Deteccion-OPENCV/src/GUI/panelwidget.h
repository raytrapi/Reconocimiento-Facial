#ifndef PANELWIDGET_H
#define PANELWIDGET_H
#include <QMainWindow>
#include <QWidget>
#include <QtWidgets>
#include <QDebug>
#include <QSplitter>

#include "imgviewer.h"
#include "../img.h"

class PanelWidget : public QWidget
{
        Q_OBJECT
        ImgViewer *imgViewer;
        Img *img;
        QThread imgThread;
        QHBoxLayout* botonera;
        QPushButton *lanzarVideo;
        QPushButton *guardar;
        //QScopedPointer<cv::VideoCapture> videoCamara;
    public:
        explicit PanelWidget(QWidget *parent = 0);
        ~PanelWidget();

    public slots:
        void openFileDialog();
        void ponerImg(QString nombre);
        void activarVideo(bool activar);
    signals:
        void imgFileNameSignal(QString filename);

    public slots:
};

#endif // PANELWIDGET_H
