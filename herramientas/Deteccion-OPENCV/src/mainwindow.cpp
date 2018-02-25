
#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    escena= new QGraphicsScene(this);
    //ui->graphicsView->setScene(escena);
    //createDockWindows();
    panel=new PanelWidget(this);

    escena->addWidget(panel);
//    setCentralWidget(panel);
    panel->setFixedSize(800,600);
    //this->adjustSize();
    this->setFixedSize(800,600);

}


MainWindow::~MainWindow(){
    delete ui;

}

void MainWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);
    //this->adjustSize();
}
