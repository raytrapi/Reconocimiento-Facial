
#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent), ui(new Ui::MainWindow){
   ui->setupUi(this);
   escena= new QGraphicsScene(this);
   //ui->graphicsView->setScene(escena);
   //createDockWindows();
   QVBoxLayout *principal=new QVBoxLayout;
   panel=new PanelWidget();
   principal->addWidget(panel);
   //escena->addWidget(panel);
   //    setCentralWidget(panel);
   panel->resize(this->width(),this->height());

   QObject::connect(panel, SIGNAL(imagenAbierta(QString)),
         this, SLOT(recordarImagen(QString)));

   //panel->setFixedSize(800,600);
   //this->adjustSize();
   //this->setFixedSize(800,600);
   //imgThread.start();
   //panel->moveToThread(&imgThread);
   //panel->setEnabled(false);
   QWidget *widget = new QWidget();
   widget->setLayout(principal);
   setCentralWidget(widget);
   QObject::connect(panel, SIGNAL(cambioEstado(bool)),
         this, SLOT(cambiarEstadoPanel(bool)));

   //
   QToolBar * toolBar = new QToolBar(tr("Últimas Imágenes"));
   toolBar->setAllowedAreas(Qt::TopToolBarArea);
   toolBar->setMovable(false);

   toolBar->addWidget(new QLabel(tr("Últimas imágenes: ")));
   ultimasImagenes=new QComboBox();
   ultimasImagenes->addItem("");
   ultimasImagenes->setFixedWidth(150);
   toolBar->addWidget(ultimasImagenes);/**/
   addToolBar(toolBar);
   QObject::connect(ultimasImagenes, SIGNAL(currentIndexChanged(int)),
            this, SLOT(seleccionarImagen(int)));

   for(int i=1; i<=10; i++){
      QString n="ultima_imagen_"+QString::number(i);
      if(configuracion.contains(n)){
         ultimasImagenes->addItem(configuracion.value(n).toString());
      }
   }
}

void MainWindow::cambiarEstadoPanel(bool estado){
   qDebug()<<"Cambios estado panel a "<<(estado?" encendido":" apagado");
   panel->setEnabled(estado);
   update();
}
MainWindow::~MainWindow(){
    delete ui;
    //imgThread.quit();
    //imgThread.wait();
}

void MainWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);
    //this->adjustSize();
}

void MainWindow::recordarImagen(QString fichero){

   std::vector<QString> ficheros;
   ficheros.push_back(fichero);


   for(int i=1; i<=10; i++){
      QString n="ultima_imagen_"+QString::number(i);
      if(configuracion.contains(n)){
         QString f=configuracion.value(n).toString();
         if(f!=fichero){
            ficheros.push_back(f);
         }
      }
   }
   while(ultimasImagenes->count()){
      ultimasImagenes->removeItem(0);
   }
   ultimasImagenes->addItem("");
   for(int i=0;i<ficheros.size();i++){
      configuracion.setValue("ultima_imagen_"+QString::number(i+1),ficheros[i]);
      ultimasImagenes->addItem(ficheros[i]);
   }

}
void MainWindow::seleccionarImagen(int indice){

   if(indice!=0){
      //qDebug()<<configuracion.value("ultima_imagen"+QString::number(indice));
      panel->cargarImagen(configuracion.value("ultima_imagen_"+QString::number(indice)).toString());
   }
}
