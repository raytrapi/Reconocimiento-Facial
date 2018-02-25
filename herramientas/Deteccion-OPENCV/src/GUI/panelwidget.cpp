#include "panelwidget.h"

PanelWidget::PanelWidget(QWidget *parent) : QWidget(parent){
    imgViewer=new ImgViewer(this);
    QVBoxLayout *layout=new QVBoxLayout;


    /*QSplitter *sp1=new QSplitter;
    QVBoxLayout*lateral1=new QVBoxLayout();
    layout->addWidget(sp1);
    sp1->setOrientation(Qt::Vertical);

    QWidget *izquierdo=new QWidget;
    izquierdo->setLayout(lateral1);
    izquierdo->setMaximumWidth(150);

    sp1->addWidget(izquierdo);

    QLabel *l1=new QLabel("Tam. Min. Faces");
    l1->setAlignment(Qt::AlignCenter);
    lateral1->addWidget(l1);
    //QVBoxLayout*lateral2=new QVBoxLayout();
    //layout->addLayout(lateral2);
    sp1->addWidget(imgViewer);/**/
    layout->addWidget(imgViewer);
    QPushButton *selImg=new QPushButton("Selecciona imagen");
    guardar=new QPushButton("Guardar");
    QHBoxLayout* parteVideo = new QHBoxLayout();

    botonera = new QHBoxLayout();
    //botonera->setEnabled(false);


    QRadioButton *conVideo=new QRadioButton("Video");
    conVideo->setChecked(false);
    parteVideo->addWidget(conVideo);

    QObject::connect(conVideo,SIGNAL(clicked(bool)),
                     this, SLOT(activarVideo(bool)));
    lanzarVideo=new QPushButton ("Encender");
    QObject::connect(lanzarVideo, SIGNAL(clicked(bool)),
                     imgViewer, SLOT(lanzarVideo()));
    parteVideo->addWidget(lanzarVideo);
    parteVideo->setEnabled(false);
    conVideo->setEnabled(false);
    //QObject::connect(selImg, SIGNAL(clicked(bool)), this, SLOT(openFileDialog()));
    layout->addLayout(parteVideo);


    QObject::connect(selImg, SIGNAL(clicked(bool)), this, SLOT(openFileDialog()));
    QObject::connect(guardar, SIGNAL(clicked(bool)),
                     imgViewer, SLOT(guardarImagen()));
    botonera->addWidget(selImg);

    guardar->setEnabled(false);
    botonera->addWidget(guardar);


    layout->addLayout(botonera);
    setLayout(layout);




    img=new Img();
    imgThread.start();
    imgViewer->moveToThread(&imgThread);
    imgViewer->connect(img, SIGNAL(matReady(cv::Mat)),SLOT(setImageCV(cv::Mat)));

    QObject::connect(this, SIGNAL(imgFileNameSignal(QString)),
                     img, SLOT(cambiarImagen(QString)));
    }

    PanelWidget::~PanelWidget()
    {
        img->~Img();
        imgThread.quit();
        imgThread.wait();
    }
void PanelWidget::openFileDialog(){
    QString filename = QFileDialog::getOpenFileName(this, tr("Imagen"));
    guardar->setEnabled(true);
    emit imgFileNameSignal(filename);

}
void PanelWidget::ponerImg(QString nombre){

}

void PanelWidget::activarVideo(bool activar){
    qDebug()<<activar;
    //activar?botonera->a
    botonera->setEnabled(!activar);
    //update();

    if(activar){

        //videoCamara.reset(new cv::VideoCapture(0));
        //qDebug()<<videoCamara->isOpened();
        /*videoCamara->open(-1);
        qDebug()<<videoCamara->isOpened();
        videoCamara->open(0);
        qDebug()<<videoCamara->isOpened();
        videoCamara->release();*/
        imgViewer->setVideo(0);

        //imgViewer->lanzarVideo();
    }else{
        //imgViewer->pararVideo();
    }
}
