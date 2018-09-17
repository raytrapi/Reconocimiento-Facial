#include "visorwidget.h"

VisorWidget::VisorWidget(QWidget *parent) : QWidget(parent){

}

VisorWidget::~VisorWidget(){

}
void VisorWidget::setImage(const QImage &img){
   imageOriginal=img.copy(img.rect());

   reescalado();
   image = img;
   this->update();

}
void VisorWidget::reescalado(){
   qreal escalaTemporal=1;

      int w=this->width();
      int h=this->height();
      if(imageOriginal.size().width()>w){
         escalaTemporal=(qreal)w/(qreal)imageOriginal.size().width();
      }
      if(imageOriginal.size().height()>h){
         qreal escalaTemporal2=(qreal)h/(qreal)imageOriginal.size().height();
         if(escalaTemporal2<escalaTemporal){
            escalaTemporal=escalaTemporal2;
         }
      }
      escala=escalaTemporal;
}

void VisorWidget::paintEvent(QPaintEvent *){
    double ancho = this->width();
    double alto = this->height();
    QRectF limite(0, 0, ancho, alto);
    //QPainter fondo(this);
    //fondo.fillRect(0,0,ancho,alto,Qt::white);
    QPainter p(this);
    //qreal escala=this->escala*this->zoom;

    if(conZoom){
       conZoom=false;
       //p.translate(xDesplazadoZoom, yDesplazadoZoom);
       //xDesplazado+=((int)(ultimoRatonX/(zoom*escala)-ultimoRatonX/escala))>>1;

       //yDesplazado+=((int)(ultimoRatonY/(zoom*escala)-ultimoRatonY/escala))>>1;
       //p.translate(-xDesplazadoZoom, -yDesplazadoZoom);
       escala*=zoom;
    }
    p.scale(escala, escala);
    p.drawImage(xDesplazado,yDesplazado, image);
    /*qreal escala=this->zoom;
    p.scale(escala, escala);*/
    double anchoImagen;
    double altoImagen;
    if(image.isNull()){
      anchoImagen = ancho;
      altoImagen = alto;
    }else{
      anchoImagen = static_cast<double>(image.width())*escala;
      altoImagen = static_cast<double>(image.height())*escala;
    }

    int x = 0;
    int y = 0;
    if(anchoImagen < ancho){
        x = ((int)(ancho - anchoImagen))>>1;
    }else{
        x = ((int)(anchoImagen-ancho))>>1;
    }

    if(altoImagen<alto){
        y = ((int)(alto-altoImagen))>>1;
    }else{
        y = ((int)(altoImagen-alto))>>1;
    }/**/

    //p.fillRect(0,0,ancho,alto,Qt::gray);
    if(!regiones.empty()){
          for(std::vector<vision::recortador::Seleccion>::iterator is=regiones.begin();is!=regiones.end();++is){
             vision::recortador::Seleccion s=*is;
             qDebug()<<s.x;
             qDebug()<<s.y;
             qDebug()<<s.w;
             qDebug()<<s.h;
             qDebug()<<image.width();
             qDebug()<<image.height();
             qDebug()<<escala;
             qDebug()<<((s.x)*image.width());
             qDebug()<<((s.y)*image.height());
             qDebug()<<((s.w)*image.width());
             qDebug()<<((s.h)*image.height());
             p.setPen(Qt::blue);
             p.drawRect(
                   ((s.x-s.w/2)*image.width())+xDesplazado,
                   ((s.y-s.h/2)*image.height())+yDesplazado,
                   ((s.w)*image.width()),
                   ((s.h)*image.height())
                );
          }
       }/**/

}

void VisorWidget::guardarImagen(){
    QString filename = QFileDialog::getSaveFileName(this, tr("Guardar imagen"),"untitled.jpg",
                           tr("Images (*.jpg *.png *.xpm)"));
    imageOriginal.save(filename);
}


void VisorWidget::mousePressEvent(QMouseEvent* event) {
   botonPulsado[event->button()]=true;
   posXRaton=event->globalX();
   posYRaton=event->globalY();
}

void VisorWidget::mouseMoveEvent(QMouseEvent* event) {
   if(botonPulsado[1]){
      xDesplazado+=(event->globalX()-posXRaton)/escala;
      yDesplazado+=(event->globalY()-posYRaton)/escala;
      posXRaton=event->globalX();
      posYRaton=event->globalY();
   }
   update();
}

void VisorWidget::mouseReleaseEvent(QMouseEvent* event) {
   botonPulsado[event->button()]=false;
}

void VisorWidget::wheelEvent(QWheelEvent* event) {
   double velocidad=0.2;
   if(tiempoZoomAnterior>0){
      if(event->timestamp()-tiempoZoomAnterior>0.05){
         velocidad=0.2;
      }

   }

   tiempoZoomAnterior=event->timestamp();
   qreal zoomSalto=event->delta()/120;
   //zoomSalto=   velocidad*((event->delta()>>3)/15);
   //zoomSalto=  exp(zoomSalto*velocidad);
   zoom=exp(zoomSalto*velocidad);//velocidad*((event->delta()>>3)/15);
   //Tenemos que compensar el zoom moviendo la imágen para que quede en la misma posición
   //qreal zoomDif=zoom-zoomTemp;
   ultimoRatonX=event->globalX();//-xDesplazado;
   ultimoRatonY=event->globalY();//-yDesplazado;
   this->conZoom=true;

   //xDesplazado-=(ratonX/(zoom*this->escala)-ratonX/this->escala);
   //yDesplazado-=(ratonY/(zoom*this->escala)-ratonY/this->escala);
   update();
   //this->escala*=zoom;
}
void VisorWidget::resizeEvent(QResizeEvent* event) {
   reescalado();
   update();
}

void VisorWidget::setRegiones(std::vector<vision::recortador::Seleccion> regiones) {
   this->regiones=regiones;
}/**/
