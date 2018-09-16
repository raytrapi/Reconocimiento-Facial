#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QtWidgets>
#include <QtCore>
#include <QtGui>

#include "GUI/panelwidget.h"
#include "ui_mainwindow.h"

#include "vector"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    public slots:
       void cambiarEstadoPanel(bool);
    private slots:
       void recordarImagen(QString);
       void seleccionarImagen(int index);
    protected:
        void resizeEvent(QResizeEvent *event);
    private:
        Ui::MainWindow *ui;
        QGraphicsScene *escena;
        PanelWidget *panel;
        QThread imgThread;
        QComboBox *ultimasImagenes;
        QSettings configuracion;

};

#endif // MAINWINDOW_H
