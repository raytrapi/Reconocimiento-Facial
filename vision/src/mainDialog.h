#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <iostream>
#include <QStandardPaths>
#include <QDebug>
#include <QSettings>
#include <QDir>

#include <QDialog>
#include <QFrame>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QStatusBar>
#include <QToolBar>
#include <QHBoxLayout>
#include <QComboBox>
#include <QTextEdit>

#include <QImageReader>
#include <QImageWriter>
#include <QGuiApplication>
#include <QScreen>
#include <QPainter>

#include <boost/thread.hpp>

#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
#include "utiles/config.h"
#include "utiles/log.h"
#include "inicializar.h"
#include "plugin.h"
#include "dll/librerias.h"
#include "../../utilidades/controles/visor/src/visorwidget.h"

using namespace cv;
using namespace ray::utiles;
class MainDialog : public QMainWindow{
	Q_OBJECT
	const int PL=5;
	const int PT=5;
    const int PR=5;
	const int PB=5;
	const int W=600;
	const int H=600;
	const int WW=1024;
	const int WH=768;
	const int WP=600;
	const int HP=100;
	const int WTOTAL=W;
	const int HTOTAL=H+HP;
	const int HLOG=150;
	//ray::utiles::Config global;
	public:
		//MainDialog(QWidget *parent = 0);
		MainDialog();
		bool loadFile(const QString &);
	public slots:
	 	 void open();
	 	 void ejecutarMetodo();
	 	 void guardarImagen();
	 	 void seleccionarAlgoritmo(int indice);
	private:
	 	void ponerAcciones();
	 	void ponerToolBar();
	 	void updateActions();
	 	void ejecutarHilo(cv::Mat * img);
	 	void setImage(const QImage &newImage);
	 	void setImagenTratada(const QImage &newImage);
	 	QImage cv_qimage(const cv::Mat &);
	 	QImage cv_qimageGris(const cv::Mat &);
	 	static void borrarMat(void *mat);
	 	void paintEvent(QPaintEvent *);
		QImage imagen;
		QImage imagenTratada;
		QMainWindow *menuPrincipal;
		//QToolBar toolBar;

		Mat imagenCV;
		int iCVW[2];
		int iCVH[2];
		int iW[2];
		int iH[2];
		int posX[2];
		int posY[2];
		int top=0;
		bool procesado=false;
		ray::dll::Librerias<vision::Plugin> librerias;
		QComboBox *algoritmos;
		QTextEdit log;
		VisorWidget *imgViewer;
		QFrame *qParametros;
		//



};


#endif
