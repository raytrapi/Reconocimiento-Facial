#ifndef VISORWIDGET_H
#define VISORWIDGET_H
#ifdef WIN32
   #ifdef VISORWIDGET
      #define VISORWIDGET   __declspec(dllexport)
   #else
     #define VISORWIDGET   __declspec(dllimport)
   #endif
#else
   #define VISORWIDGET
#endif
#include <QMainWindow>
#include <QWidget>
#include <QtWidgets>
#include <QDebug>
#include <QSplitter>
#include <Qt>

#include "selector.h"

#include <vector>

class VISORWIDGET VisorWidget : public QWidget{
   Q_OBJECT
      QImage image;
      QImage imageOriginal;
      std::vector<vision::recortador::Seleccion>  regiones;
   public:
      explicit VisorWidget(QWidget *parent = 0);
      ~VisorWidget();
      void setImage(const QImage & img);
      void setRegiones(std::vector<vision::recortador::Seleccion>  regiones);


   private:
      void paintEvent(QPaintEvent *);
      void mousePressEvent(QMouseEvent *event);
      void mouseMoveEvent(QMouseEvent *event);
      void mouseReleaseEvent(QMouseEvent *event);
      void wheelEvent(QWheelEvent *event);
      void resizeEvent(QResizeEvent *event);/**/
      void reescalado();
      qreal escala=1;
      qreal zoom=1;
      ulong tiempoZoomAnterior=-1;
      bool botonPulsado[4]={false,false,false,false};
      double xDesplazado=0;
      double yDesplazado=0;
      double xDesplazadoZoom=0;
      double yDesplazadoZoom=0;
      int posXRaton=0;
      int posYRaton=0;
      int ultimoRatonX;
      int ultimoRatonY;
      bool conZoom=false;
   public slots:
      void guardarImagen();
};

#endif // VISORWIDGET_H
