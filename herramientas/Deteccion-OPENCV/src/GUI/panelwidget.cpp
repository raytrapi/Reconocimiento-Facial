#include "panelwidget.h"

PanelWidget::PanelWidget(QWidget *parent) : QWidget(parent){


   //Panel Imagen

   QHBoxLayout *horizontal1 = new QHBoxLayout;
   QFrame *frame=new QFrame();

   ///PRIMER FRAME
   imgViewer=new VisorWidget(this);
   QVBoxLayout *layout=new QVBoxLayout;
   frame->setLayout(horizontal1);
   horizontal1->addWidget(imgViewer);

   panelInfo=new QFrame;
   panelInfo->setFixedWidth(200);
   panelInfo->setStyleSheet("background-color:#fafafa;");
   horizontal1->addWidget(panelInfo);
   layout->addWidget(frame);


   //QHBoxLayout* parteVideo = new QHBoxLayout();

   QPushButton *selImg=new QPushButton("Selecciona imagen");
   guardar=new QPushButton("Guardar");
   bLanzarVideo=new QPushButton ("Encender Cámara");

   botonera = new QHBoxLayout();

   botonera->addWidget(bLanzarVideo);
   botonera->addWidget(selImg);
   botonera->addWidget(guardar);
   guardar->setEnabled(false);
   layout->addLayout(botonera);

   QObject::connect(bLanzarVideo, SIGNAL(clicked(bool)),
         this, SLOT(lanzarVideo()));
   QObject::connect(selImg, SIGNAL(clicked(bool)), this, SLOT(openFileDialog()));
   QObject::connect(guardar, SIGNAL(clicked(bool)),
         imgViewer, SLOT(guardarImagen()));
   /*QObject::connect(imgViewer,SIGNAL(videoLanzado(bool)),
    				this, SLOT(cambiarEstdoEncendido(bool)));*/
   //parteVideo->addWidget(bLanzarVideo);
   horizontal1 = new QHBoxLayout;
   frame=new QFrame();
   //horizontal1->setLayout(frame);

   QGroupBox *parametros=new QGroupBox(tr("Parámetros"));
   //parametros->setFixedHeight(50);
   QCheckBox *rejilla = new QCheckBox(tr("rejilla"));
   QCheckBox *filtro = new QCheckBox(tr("filtro"));
   QCheckBox *conPartes = new QCheckBox(tr("Partes"));
   QCheckBox *conIoU = new QCheckBox(tr("IoU"));
   QCheckBox *conInfo = new QCheckBox(tr("Info"));
   chekAcotacion = new QCheckBox(tr("Acotado"));
   QHBoxLayout *capaParametros = new QHBoxLayout;
   capaParametros->addWidget(rejilla);
   capaParametros->addWidget(filtro);
   capaParametros->addWidget(chekAcotacion);
   capaParametros->addWidget(conPartes);
   capaParametros->addWidget(conIoU);
   capaParametros->addWidget(conInfo);
   capaParametros->addStretch(1);
   parametros->setLayout(capaParametros);


   QObject::connect(rejilla,SIGNAL(stateChanged(int)),
         this, SLOT(ponerRejilla(int)));
   QObject::connect(filtro,SIGNAL(stateChanged(int)),
            this, SLOT(ponerFiltro(int)));
   QObject::connect(chekAcotacion,SIGNAL(stateChanged(int)),
            this, SLOT(ponerAcotacion(int)));
   QObject::connect(conPartes,SIGNAL(stateChanged(int)),
         this, SLOT(ponerconPartes(int)));
   QObject::connect(conInfo,SIGNAL(stateChanged(int)),
         this, SLOT(ponerconInfo(int)));
   QObject::connect(conIoU,SIGNAL(stateChanged(int)),
            this, SLOT(ponerconIoU(int)));
   horizontal1->addWidget(parametros);
   frame->setLayout(horizontal1);

   QGroupBox *tamMinimo=new QGroupBox(tr("Selector"));
   frame->setFixedHeight(70);
   QHBoxLayout *horizontal2 = new QHBoxLayout;
   QLabel *lTemp=new QLabel();
   lTemp->setText("Ancho:");
   horizontal2->addWidget(lTemp);
   selectorAnchoMinimo=new QLineEdit;
   //selectorAnchoMinimo->setPattern("^[0-9\ \(\)\+]$");
   horizontal2->addWidget(selectorAnchoMinimo);
   lTemp=new QLabel();
   lTemp->setText("Alto:");
   horizontal2->addWidget(lTemp);
   selectorAltoMinimo=new QLineEdit;
   //selectorAltoMinimo->setPattern("^[0-9\ \(\)\+]$");
   horizontal2->addWidget(selectorAltoMinimo);
   tamMinimo->setLayout(horizontal2);
   horizontal1->addWidget(tamMinimo);
   //frame->setLayout(tamMinimo);

   layout->addWidget(frame);


   setLayout(layout);

   img=new Img();
   //imgThread.start();
   //this->moveToThread(&imgThread);
   this->connect(img, SIGNAL(matReady(cv::Mat)),SLOT(setPreImageCV(cv::Mat)));

   QObject::connect(this, SIGNAL(imgFileNameSignal(QString)),
         img, SLOT(cambiarImagen(QString)));


   vision::metodos::Viola_Jones::setClasificador("E:/Desarrollo/Vision/build/bin/clasificadores/haarcascade_frontalface_default.xml","Cara",QColor(255,0,255,0));
   vision::metodos::Viola_Jones::setClasificador("E:/Desarrollo/Vision/build/bin/clasificadores/haarcascade_profileface.xml","Perfil",QColor(255,255,0,0));
   vision::metodos::Viola_Jones::setClasificador("E:/Desarrollo/Vision/build/bin/clasificadores/haarcascade_eye.xml","Ojo",QColor(0,0,255,0));
   vision::metodos::Viola_Jones::setClasificador("E:/Desarrollo/Vision/build/bin/clasificadores/haarcascade_mcs_nose.xml","Nariz",QColor(255,0,0,0));
   vision::metodos::Viola_Jones::setClasificador("E:/Desarrollo/Vision/build/bin/clasificadores/haarcascade_mcs_mouth.xml","Boca",QColor(0,255,0,0));
   indiceCamara=1; //Camara principal
   usandoVideoCamara=false;
   selectorAnchoMinimo->setText(QString::number(anchoMinimo));
   selectorAltoMinimo->setText(QString::number(altoMinimo));
}

PanelWidget::~PanelWidget()
{
   img->~Img();
   //imgThread.quit();
   //imgThread.wait();
}
void PanelWidget::openFileDialog(){
   if(usandoVideoCamara){
      this->lanzarVideo();
   }
   QString filename = QFileDialog::getOpenFileName(this, tr("Imagen"));
   if(!filename.isEmpty() && !filename.isNull()){

      guardar->setEnabled(true);
      emit imagenAbierta(filename);
      emit imgFileNameSignal(filename);
   }

}
void PanelWidget::cargarImagen(QString nombre){
   //qDebug()<<"cargo "<<nombre;
   emit imgFileNameSignal(nombre);
}
/*void PanelWidget::ponerImg(QString nombre){

}/**/

void PanelWidget::activarVideo(bool activar){
    //qDebug()<<activar;
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
        this->setVideo(0);

        ////imgViewer->lanzarVideo();
    }else{
        ////imgViewer->pararVideo();
    }
}

void PanelWidget::cambiarEstadoEncendido(bool encendido) {
   usandoVideoCamara=encendido;
	if(encendido){
		bLanzarVideo->setText("Apagar Cámara");
	}else{
		bLanzarVideo->setText("Encender Cámara");
	}

}

void PanelWidget::ponerRejilla(int valor) {
   conRejilla=(valor==2);
   if(conImagen){
      setImageCV(imagenCVOriginal);
   }
}

void PanelWidget::ponerFiltro(int valor) {
   conFiltro=(valor==2);
   if(conFiltro){
      conAcotacion=true;
   }else{
      conAcotacion=chekAcotacion->isChecked();
   }
   chekAcotacion->setEnabled(!conFiltro);
   if(conImagen){
      setImageCV(imagenCVOriginal);
   }
}
void PanelWidget::ponerAcotacion(int valor) {
   conAcotacion=(valor==2);
   if(conImagen){
      setImageCV(imagenCVOriginal);
   }
}
void PanelWidget::ponerconPartes(int valor) {
   conPartes=(valor==2);
   if(conImagen){
      setImageCV(imagenCVOriginal);
   }
}
void PanelWidget::ponerconInfo(int valor) {
   conInfo=(valor==2);
   if(conImagen){
      setImageCV(imagenCVOriginal,false);
   }
}
void PanelWidget::ponerconIoU(int valor) {
   conIoU=(valor==2);
   if(conImagen){
      setImageCV(imagenCVOriginal);
   }
}


void PanelWidget::setImage(const QImage &img){
   /*if (image.isNull()){
        qDebug() << "Vista sin imagen";
        return;
    }*/
   imageOriginal=img.copy(img.rect());

   /*qreal escalaTemporal=1;

   int w=this->width();
   int h=this->height();
   if(imageOriginal.size().width()>w){
      qDebug()<<w<<"/"<<imageOriginal.size().width();
      escalaTemporal=(qreal)w/(qreal)imageOriginal.size().width();
      qDebug()<<escalaTemporal;
   }
   if(imageOriginal.size().height()>h){
      qDebug()<<h<<"/"<<imageOriginal.size().height();
      qreal escalaTemporal2=(qreal)h/(qreal)imageOriginal.size().height();
      if(escalaTemporal2<escalaTemporal){
         escalaTemporal=escalaTemporal2;
      }
      qDebug()<<escalaTemporal2;
   }
   escala=escalaTemporal;
*/

   //image = img;//img.scaled(this->width(), this->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);;
   /*if (image.size() != size())
        setFixedSize(image.size());*/
   imgViewer->setImage(img);
   this->update();

}
void PanelWidget::setPreImageCV(const cv::Mat &img){
   //cv::Mat m
   //zoom=1;
   //xDesplazado=0;
   //yDesplazado=0;
   //posXRaton=0;
   //posYRaton=0;
   imagenCVOriginal=img.clone();
   conImagen=true;
   setImageCV(img);
}
void PanelWidget::setImageCV(const cv::Mat &img){
   setImageCV(img, true);
}
void PanelWidget::setImageCV(const cv::Mat &img, bool procesar){
   //img.copyTo();
   //bool conPartes=true;
   //bool conFiltro=true;
   emit cambioEstado(false);

   vision::metodos::Viola_Jones::setDeteccionMinima(anchoMinimo, altoMinimo);
   //cv::imshow("Imagen", img);
   //Borramos los controles

   QLayoutItem* layoutHijo;
   int i=1000;//Evitamos un posible desbordamiento
   while(panelInfo->layout()!=0 && panelInfo->layout()->count()!=0 && i-->0){
      layoutHijo=panelInfo->layout()->takeAt(0);
      if ( layoutHijo->layout() != 0 ) {
         layoutHijo->layout()->deleteLater();
      } else if ( layoutHijo->widget() != 0 ) {
         delete layoutHijo->widget();
      }

      delete layoutHijo;
      //panelInfo->layout()->deleteLater();
   }
   panelInfo->setLayout(new QVBoxLayout);
   panelInfo->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);


   if(procesar || zonasInteres.size()==0){
      if(conRejilla || !conPartes || conFiltro || conAcotacion){

         //zonasInteres=vision::metodos::Viola_Jones::procesar(img,{0,1},(conFiltro || conPartes));
         zonasInteres=vision::metodos::Viola_Jones::procesar(img,{0,1},conIoU);
         int zonasEncontradas=zonasInteres.size();
         if(conFiltro || conPartes){
            if(conPartes){
               //Añadimos el resto de clasificadores
               for(int i=2;i<vision::metodos::Viola_Jones::clasificadores.size();i++){
                  zonasInteres.push_back(vision::metodos::RestClasificacion(std::vector<cv::Rect>(),
                        std::get<1>(vision::metodos::Viola_Jones::clasificadores[i]),
                        std::get<2>(vision::metodos::Viola_Jones::clasificadores[i]),
                        true
                        ));
               }/**/
            }
            //int zonasEncontradas=zonasInteres.size()-vision::metodos::Viola_Jones::clasificadores.size()+2;

            for(int i = 0;i < zonasEncontradas;i++){
               std::vector<std::pair<cv::Rect,bool>> zonas=zonasInteres[i].clasificados;

               for(int j = 0;j < zonas.size();j++){
                  bool valida=true;
                  cv::Rect roi=zonas[j].first;
                  //Buscamos los ojos
                  int porcion[2];
                  porcion[0]=roi.width/5;
                  porcion[1]=roi.height/8;
                  std::vector<vision::metodos::RestClasificacion> partes;
                  //vision::metodos::RestClasificacion partesBuenas;
                  //std::vector<cv::Rect> ojos;
                  /*partesBuenas=std::tuple<std::vector<cv::Rect>,const char *, QColor, bool>(ojos,
                        std::get<1>(zonasInteres[j]),
                        std::get<2>(zonasInteres[j]),
                        std::get<3>(zonasInteres[j])
                        );/**/
                  //vision::metodos::Viola_Jones::setDeteccionMinima(roi.width*2/5,roi.height*2/8);
                  vision::metodos::Viola_Jones::setDeteccionMinima(0,0);
                  partes=vision::metodos::Viola_Jones::procesar(cv::Mat(img, cv::Rect(roi.x, roi.y+porcion[1], roi.width, porcion[1]<<2)),{2},conIoU);

                  //Añadimos el calculo de IoU
                   std::cout<<"OJOS"<<std::endl;
                  for(int k=0;k<partes[0].clasificados.size();k++){
                     for(int h=k+1;h<partes[0].clasificados.size();h++){
                        cv::Rect A=partes[0].clasificados[k].first;
                        cv::Rect B=partes[0].clasificados[h].first;
                       /* qDebug()<<"IoU= "<<vision::Utils::calcularIoU(
                              A.x,A.y,A.width+A.x,A.height+A.y,
                              B.x,B.y,B.width+B.x,B.height+B.y
                              );/**/

                     }
                  }

                  std::vector<std::pair<cv::Rect,bool>> ojos=partes[0].clasificados;
                  /*QColor color2=std::get<2>(partes[0]);
                  cv::Scalar colorCV(color2.blue(),color2.green(),color2.red());/**/
                  valida=(ojos.size()>0 && ojos.size()<=2);
                  for(int k=0;k<ojos.size();k++){
                     ojos[k].first.x+=roi.x;
                     ojos[k].first.y+=roi.y+porcion[1];
                  }

                  bool tieneNariz=false;
                  partes=vision::metodos::Viola_Jones::procesar(cv::Mat(img, cv::Rect(roi.x+porcion[0], roi.y+(porcion[1]<<1)+porcion[1], (porcion[0]<<1)+porcion[0], (porcion[1]<<1)+porcion[1])),{3},conIoU);
                  std::vector<std::pair<cv::Rect,bool>> narices=partes[0].clasificados;
                  tieneNariz=(narices.size()==1);
                  for(int k=0;k<narices.size();k++){
                     narices[k].first.x+=roi.x+porcion[0];
                     narices[k].first.y+=roi.y+(porcion[1]<<1)+porcion[1];
                  }

                  partes=vision::metodos::Viola_Jones::procesar(cv::Mat(img, cv::Rect(roi.x, roi.y+(porcion[1]<<2)+porcion[1], roi.width, (porcion[1]<<1)+porcion[1])),{4},conIoU);
                  std::vector<std::pair<cv::Rect,bool>> bocas=partes[0].clasificados;
                  valida=valida && tieneNariz&&(bocas.size()==1);
                  for(int k=0;k<bocas.size();k++){
                     bocas[k].first.x+=roi.x;
                     bocas[k].first.y+=roi.y+(porcion[1]<<2)+porcion[1];
                  }
                  if(conFiltro){
                     zonasInteres[i].clasificados[j].second=valida;
                     if(valida){
                        zonasInteres[zonasEncontradas].uneZonas(ojos);
                        zonasInteres[zonasEncontradas+1].uneZonas(narices);
                        zonasInteres[zonasEncontradas+2].uneZonas(bocas);
                     }
                  }else{
                     zonasInteres[zonasEncontradas].uneZonas(ojos);
                     zonasInteres[zonasEncontradas+1].uneZonas(narices);
                     zonasInteres[zonasEncontradas+2].uneZonas(bocas);
                  }
               }
            }

         }
      }else{
         zonasInteres=vision::metodos::Viola_Jones::procesar(img);
      }
   }

   cv::Mat  temp=img.clone();
   //Pintamos las zonas
   for(int i = 0;i < zonasInteres.size();i++){
      std::vector<std::pair<cv::Rect,bool>> zonas=(std::vector<std::pair<cv::Rect,bool>>)zonasInteres[i].clasificados;
      QColor color=zonasInteres[i].color;
      cv::Scalar colorCV(color.blue(),color.green(),color.red());
      for(int j = 0;j < zonas.size();j++){
         if(zonas[j].second){
            cv::rectangle(temp, zonas[j].first, colorCV);
         }
      }
   }

  /*
   int numRois=0;
   for(int i = 0;i < zonasInteres.size();i++){
      std::vector<cv::Rect> zonas=(std::vector<cv::Rect>)std::get<0>(zonasInteres[i]);
      QColor color=std::get<2>(zonasInteres[i]);
      for(int j = 0;j < zonas.size();j++){
         cv::Rect roi=zonas[j];
         std::vector<std::pair<cv::Rect,cv::Scalar>> rois;

         rois.push_back(std::pair<cv::Rect,cv::Scalar>(roi,cv::Scalar(color.blue(),color.green(),color.red())));
         bool esCara=true;
         if(conPartes && conFiltro){
            //Buscamos los ojos

            int porcion[2];
            porcion[0]=roi.width/5;
            porcion[1]=roi.height/8;
            std::vector<std::tuple<std::vector<cv::Rect>,const char *, QColor, bool>> partes;
            partes=vision::metodos::Viola_Jones::procesar(
               cv::Mat(img, cv::Rect(roi.x, roi.y+porcion[1], roi.width, porcion[1]<<2)),{2});
            std::vector<cv::Rect> partesSolo=std::get<0>(partes[0]);
            QColor color2=std::get<2>(partes[0]);
            cv::Scalar colorCV(color2.blue(),color2.green(),color2.red());
            esCara=(partesSolo.size()>0 && partesSolo.size()<=2);
            for(int j=0;j<partesSolo.size();j++){
               partesSolo[j].x+=roi.x;
               partesSolo[j].y+=roi.y+porcion[1];
               rois.push_back(std::pair<cv::Rect,cv::Scalar>(partesSolo[j],colorCV));
            }

            bool tieneNariz=false;
            partes=vision::metodos::Viola_Jones::procesar(
               cv::Mat(img, cv::Rect(roi.x+porcion[0], roi.y+(porcion[1]<<1)+porcion[1], (porcion[0]<<1)+porcion[0], (porcion[1]<<1)+porcion[1])),{3});
            partesSolo=std::get<0>(partes[0]);
            color2=std::get<2>(partes[0]);
            colorCV=cv::Scalar(color2.blue(),color2.green(),color2.red());
            tieneNariz=(partesSolo.size()==1);
            for(int j=0;j<partesSolo.size();j++){
               partesSolo[j].x+=roi.x+porcion[0];
               partesSolo[j].y+=roi.y+(porcion[1]<<1)+porcion[1];
               rois.push_back(std::pair<cv::Rect,cv::Scalar>(partesSolo[j],colorCV));
            }
            partes=vision::metodos::Viola_Jones::procesar(
               cv::Mat(img, cv::Rect(roi.x, roi.y+(porcion[1]<<2)+porcion[1], roi.width, (porcion[1]<<1)+porcion[1])),{4});
            partesSolo=std::get<0>(partes[0]);
            color2=std::get<2>(partes[0]);
            colorCV=cv::Scalar(color2.blue(),color2.green(),color2.red());
            esCara=esCara && tieneNariz&&(partesSolo.size()==1);
            for(int j=0;j<partesSolo.size();j++){
               partesSolo[j].x+=roi.x;
               partesSolo[j].y+=roi.y+(porcion[1]<<2)+porcion[1];
               rois.push_back(std::pair<cv::Rect,cv::Scalar>(partesSolo[j],colorCV));
            }
         }
         if(esCara){
            for(int k=0;k<rois.size();k++){
               cv::rectangle(temp, rois[k].first, rois[k].second);
            }
         }
         if(conRejilla){
            int rejillasAncho=5;
            int rejillasAlto=8;

            cv::Scalar colorCaraRejilla(128,128,128);
            cv::Scalar colorRejilla(128,128,128, 0.1);
            //temp=new cv::Mat(img.size(),img.type());
            //imagenesResultados.push_back(temp);
            cv::rectangle((cv::Mat)(temp), roi, colorCaraRejilla,1);
            //Representamos la rejilla de proporci�n
            cv::Point pEsquinaSuperior(roi.x,roi.y);
            cv::Point pEsquinaInferior(roi.x+roi.width-1,roi.y+roi.height-1);
            int aumento=roi.width/rejillasAncho;
            int aumentoActual=0;
            //temp=new cv::Mat(img.size(),img.type());
            //imagenesResultados.push_back(temp);
            for(int i=0;i<rejillasAncho;i++){
               cv::line((cv::Mat)(temp),
                     cv::Point(pEsquinaSuperior.x+aumentoActual,pEsquinaSuperior.y),
                     cv::Point(pEsquinaSuperior.x+aumentoActual,pEsquinaInferior.y),
                     colorRejilla,1);
               aumentoActual+=aumento;
            }
            aumento=roi.height/rejillasAlto;
            aumentoActual=0;

            for(int i=0;i<rejillasAlto;i++){
               //cv::Point sup(pEsquinaSuperior.x+aumentoActual,pEsquinaSuperior.y);
               //cv::Point inf(pEsquinaSuperior.x+aumentoActual,pEsquinaInferior.y);
               cv::line((cv::Mat)(temp),
                     cv::Point(pEsquinaSuperior.x,pEsquinaSuperior.y+aumentoActual),
                     cv::Point(pEsquinaInferior.x,pEsquinaSuperior.y+aumentoActual),
                     colorRejilla,1);
               aumentoActual+=aumento;
            }
         }

         if(conInfo) {
            std::string numero=std::to_string(++numRois)+" - "+std::to_string(roi.width)+"x"+std::to_string(roi.height);
            int fontFace = cv::FONT_HERSHEY_COMPLEX_SMALL;
            double fontScale = 1;
            int thickness = 1;
            int baseLine=0;
            const char * numeroStr=numero.c_str();
            int padding= 4;
            qDebug()<<"baseLine: "<<baseLine;
            cv::Size lengthTexto=cv::getTextSize(numeroStr,fontFace,fontScale,thickness,&baseLine);
            cv::rectangle(temp, cv::Rect(roi.x,roi.y-(lengthTexto.height+padding),lengthTexto.width+4,(lengthTexto.height+padding)), cv::Scalar(255,255,255,0.7),-1);
            cv::putText(temp, numeroStr ,cv::Point((roi.x+(padding>>1)),(roi.y-(padding>>1))),fontFace,fontScale,cv::Scalar(0,0,0),thickness,8,false);
         }
      }
   }/**/
   for(i=0;i<zonasInteres.size();i++){
      QLabel *lTemp=new QLabel;
      lTemp->setText( QString(zonasInteres[i].nombre)+"["+QString::number(zonasInteres[i].clasificados.size())+"]");
      lTemp->setStyleSheet("background-color:#fafafa;");
      panelInfo->layout()->addWidget(lTemp);
   }
   panelInfo->layout()->setAlignment(Qt::AlignTop);
   //if(temp->)
   cv::cvtColor(temp,temp, cv::COLOR_BGR2RGB);
   const QImage imageTemp((const unsigned char*)temp.data, temp.cols, temp.rows, temp.step,
                  ((temp.channels()>1)?QImage::Format_RGB888:QImage::Format_Grayscale8), &borrarMat, new cv::Mat(temp));
   imageTemp.rgbSwapped();
   emit cambioEstado(true);
   setImage(imageTemp);
}
void PanelWidget::borrarMat(void *mat){
    delete static_cast<cv::Mat*>(mat);
}

void PanelWidget::setVideoCamara(bool activar){
    if(!activar && usandoVideoCamara && estaEjecutando){
        emit pararVideo();
    }
    usandoVideoCamara=false;
}



void PanelWidget::pararVideo(){
    timer.stop();
}

void PanelWidget::lanzarVideo(){
   if(!captura.isOpened()){
      //La intentmaos abrir
      setVideo(0);
      if(captura.isOpened()){
         timer.start(0,this);
         cambiarEstadoEncendido(true);
      }

   }else{
      usandoVideoCamara=false;
      captura.release();
      cambiarEstadoEncendido(false);
    }
}

void PanelWidget::guardarImagen(){
    QString filename = QFileDialog::getSaveFileName(this, tr("Guardar imagen"),"untitled.jpg",
                           tr("Images (*.jpg *.png *.xpm)"));
    imageOriginal.save(filename);
}

void PanelWidget::timerEvent(QTimerEvent *ev){
    if (estaEjecutando || ev->timerId() != timer.timerId())
        return;
   // qDebug()<<"Tiempo "<<timer.timerId();
    cv::Mat frame;
    if (!captura.read(frame)){
        timer.stop();
        return;
    }
    estaEjecutando=true;
    setImageCV(frame);
    estaEjecutando=false;
}

void PanelWidget::setIndiceCamara(int indice){
    indiceCamara=indice;
    if(indice>=-1){
        usandoVideoCamara=true;
    }
}

void PanelWidget::setVideo(int indice){
   if(captura.isOpened()){
      captura.release();
   }
   captura.open(indice);
   usandoVideoCamara=true;
    //captura.reset(new cv::VideoCapture(indice));
    //qDebug()<<captura->isOpened();
}

