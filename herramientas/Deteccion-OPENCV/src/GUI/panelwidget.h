#ifndef PANELWIDGET_H
#define PANELWIDGET_H
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QtWidgets>
#include <QtCore/QDebug>
#include <QtWidgets/QSplitter>
#include <QtCore/Qt>

#include "../../../../utilidades/controles/visor/src/visorwidget.h"
#include "../img.h"
#include "../v&j/viola_jones.h"
#include "../../../../utilidades/utils/src/utils.h"
#include <vector>
#include <utility>
class PanelWidget : public QWidget{
      Q_OBJECT
      //ImgViewer *imgViewer;
      VisorWidget *imgViewer;
      Img *img;
      QImage image;
      QImage imageOriginal;
      //QThread imgThread;
      QHBoxLayout* botonera;
      QPushButton *bLanzarVideo;
      QPushButton *guardar;
      QLineEdit *selectorAnchoMinimo;
      QLineEdit *selectorAltoMinimo;
      QCheckBox *chekAcotacion;

      QFrame * panelInfo;
      cv::VideoCapture captura;
      QBasicTimer timer;
      bool estaEjecutando=false;
      bool usandoVideoCamara=false;
      int indiceCamara;

      int anchoMinimo=10;
      int altoMinimo=20;
      //QScopedPointer<cv::VideoCapture> videoCamara;
   private:
      void setImageCV(const cv::Mat &img);
      void setImageCV(const cv::Mat &img, bool procesar);
      void timerEvent(QTimerEvent * ev);
      bool conRejilla=false;
      bool conFiltro=false;
      bool conPartes=false;
      bool conInfo=false;
      bool conAcotacion=false;
      bool conIoU=false;
      cv::Mat imagenCVOriginal;
      std::vector<cv::Mat *> imagenesResultados;
      std::vector<vision::metodos::RestClasificacion> zonasInteres;
      bool conImagen=false;
      static void borrarMat(void *mat);
      void cambiarEstadoEncendido(bool);

   public:
      explicit PanelWidget(QWidget *parent = 0);
      ~PanelWidget();
      void cargarImagen(QString);
   signals:
      void cambioEstado(bool activo);
      void imagenAbierta(QString);
      void imgFileNameSignal(QString filename);
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
      void openFileDialog();
      //void ponerImg(QString nombre);
      void activarVideo(bool activar);

      void ponerRejilla(int);
      void ponerFiltro(int);
      void ponerAcotacion(int);
      void ponerconPartes(int);
      void ponerconInfo(int);
      void ponerconIoU(int);
};

#endif // PANELWIDGET_H
