#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <iostream>
#include <QtCore/QStandardPaths>
#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <QtCore/QDir>

#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QAction>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QTextEdit>


#include <QtGui/QImageReader>
#include <QtGui/QImageWriter>
#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>
#include <QtGui/QPainter>
#include <QtGui/QWheelEvent>

#include <boost/thread.hpp>

#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
/*#include "utiles/config.h"
#include "utiles/log.h"
#include "inicializar.h"
#include "plugin.h"
#include "dll/librerias.h"
*/
using namespace cv;
//using namespace ray::utiles;
class DialogoRecortador : public QMainWindow{
	Q_OBJECT
	const int WW=1024;
	const int WH=768;
	const int PADDING[4]={5,5,5,5};
	/*const int PL=5;
	const int PT=5;
    const int PR=5;
	const int PB=5;
	const int W=600;
	const int H=600;

	const int WP=600;
	const int HP=100;
	const int WTOTAL=W;
	const int HTOTAL=H+HP;
	const int HLOG=150;*/
	//ray::utiles::Config global;
	public:
		//DialogoRecortador(QWidget *parent = 0);
		DialogoRecortador();
		QImage cargarImagen(const QString &fichero);
		void siguienteImagen();
		void cogerImagen(int indice);
		bool cargarCarpeta(const QString &);
	public slots:
	 	 void open();
	 	 void abrirCarpeta();
	private:



	 	void ponerAcciones();
	 	void ponerToolBar();
	 	void updateActions();
	 	static void borrarMat(void *mat);
	 	void paintEvent(QPaintEvent *);
	 	void mousePressEvent(QMouseEvent *event);
 	    void mouseMoveEvent(QMouseEvent *event);
 	    void mouseReleaseEvent(QMouseEvent *event);
 	    void wheelEvent(QWheelEvent *event);
 	    void resizeEvent(QResizeEvent *event);


		QImage imagen;
		QImage imagenTratada;
		QMainWindow *menuPrincipal;
		//QToolBar toolBar;
		int top=0;
		int anchoImagen=0;
		int altoImagen=0;
		/*Mat imagenCV;
		int iCVW[2];
		int iCVH[2];
		int iW[2];
		int iH[2];
		int posX[2];
		int posY[2];

		bool procesado=false;*/
		//ray::dll::Librerias<vision::Plugin> librerias;
		QComboBox *algoritmos;
		QTextEdit log;

		QString ruta;
		QStringList ficheros;
		int posicion;
		qreal escala=1;
		qreal zoom=1;
		//



};


#endif
