#include "panelwidget.h"

PanelWidget::PanelWidget(QWidget *parent) : QWidget(parent){
	//Panel Imagen
    imgViewer=new ImgViewer(this);
    QVBoxLayout *layout=new QVBoxLayout;

    layout->addWidget(imgViewer);
    QPushButton *selImg=new QPushButton("Selecciona imagen");
    guardar=new QPushButton("Guardar");
    QHBoxLayout* parteVideo = new QHBoxLayout();

    botonera = new QHBoxLayout();
    
    lanzarVideo=new QPushButton ("Encender Cámara");
    QObject::connect(lanzarVideo, SIGNAL(clicked(bool)),
                     imgViewer, SLOT(lanzarVideo()));
    QObject::connect(imgViewer,SIGNAL(videoLanzado(bool)),
    				this, SLOT(cambiarEstdoEncendido(bool)));
    parteVideo->addWidget(lanzarVideo);

    QGroupBox *parametros=new QGroupBox(tr("Parámetros"));
    parametros->setFixedHeight(50);
    QCheckBox *rejilla = new QCheckBox(tr("Con rejilla"));
    QCheckBox *filtro = new QCheckBox(tr("Con filtro"));
    QCheckBox *conPartes = new QCheckBox(tr("Con Partes"));
    QCheckBox *conInfo = new QCheckBox(tr("Con Info"));
    QHBoxLayout *capaParametros = new QHBoxLayout;
    capaParametros->addWidget(rejilla);
    capaParametros->addWidget(filtro);
    capaParametros->addWidget(conPartes);
    capaParametros->addWidget(conInfo);
    capaParametros->addStretch(1);
    parametros->setLayout(capaParametros);
    parteVideo->addWidget(parametros);
    QObject::connect(rejilla,SIGNAL(stateChanged(int)),
    		imgViewer, SLOT(ponerRejilla(int)));
    QObject::connect(filtro,SIGNAL(stateChanged(int)),
    		imgViewer, SLOT(ponerFiltro(int)));
    QObject::connect(conPartes,SIGNAL(stateChanged(int)),
        		imgViewer, SLOT(ponerconPartes(int)));
    QObject::connect(conInfo,SIGNAL(stateChanged(int)),
        		imgViewer, SLOT(ponerconInfo(int)));



    //parteVideo->setEnabled(false);
    //conVideo->setEnabled(false);
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
    imgViewer->connect(img, SIGNAL(matReady(cv::Mat)),SLOT(setPreImageCV(cv::Mat)));

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
    if(usandoCamara){
    	imgViewer->lanzarVideo();
    }
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

void PanelWidget::cambiarEstdoEncendido(bool encendido) {
qDebug()<<"llego aquí";
	usandoCamara=encendido;
	if(encendido){
		lanzarVideo->setText("Apagar Cámara");
	}else{
		lanzarVideo->setText("Encender Cámara");
	}

}
