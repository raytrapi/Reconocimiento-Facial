#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QtWidgets>
#include <QtCore>
#include <QtGui>

#include "GUI/panelwidget.h"
#include "ui_mainwindow.h"



namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();


    protected:
        void resizeEvent(QResizeEvent *event);
    private:
        Ui::MainWindow *ui;
        QGraphicsScene *escena;
        PanelWidget *panel;

};

#endif // MAINWINDOW_H
