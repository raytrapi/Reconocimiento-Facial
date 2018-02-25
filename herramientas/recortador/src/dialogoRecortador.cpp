#include "dialogoRecortador.h"

DialogoRecortador::DialogoRecortador(){
	QSettings configuracion;
	menuPrincipal=new QMainWindow(this, Qt::Widget);
	menuPrincipal->addToolBar(new QToolBar());
	anchoImagen=WW-PADDING[1]-PADDING[3];
	altoImagen=WH-PADDING[0]-PADDING[2];
	resize(WW,WH);
	if(configuracion.contains("rutaCarpeta")){
		cargarCarpeta(configuracion.value("rutaCarpeta").toString());
	}
	 //setFixedSize(WW,WH);
    ponerAcciones();
    ponerToolBar();
    /*librerias.leer((char *)vision::configuracion.cogerValor("dlls_temp").c_str());
    //librerias.ok();
    for(int i=0;i<librerias.numLibrerias;i++){
    	if(librerias.librerias[i]!=NULL){
    		if(strcmp(librerias.librerias[i]->getTipo(),"ALGORITMO")==0){
    			QString s(librerias.librerias[i]->getNombre());
    			algoritmos->addItem(s);
    		}

    	}
    }/**/
    int separadorAlto=5;
    QPalette p=log.palette();
    p.setColor(QPalette::Background, Qt::black);
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::white);

    //resize(width(),top+PT+HTOTAL+(separadorAlto<<1)+HLOG);
    /*std::string rutaDll=vision::configuracion.cogerValor("dlls_temp");
    if(rutaDll!=""){
    	//Tenemos la ruta de ficheros, buscamos si hay elementos nuevos.
    	Log::consola(rutaDll);
    }/**/


    //resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode){
    static bool firstDialog = true;
    if (firstDialog) {
        firstDialog = false;
        dialog.setDirectory( QDir::currentPath() );
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes){
        mimeTypeFilters.append(mimeTypeName);
    }
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    if (acceptMode == QFileDialog::AcceptSave){
        dialog.setDefaultSuffix("jpg");
    }
}

void DialogoRecortador::open(){
	QSettings configuracion;
	QString ruta=QDir::toNativeSeparators(configuracion.value("rutaFichero").toString());

    QFileDialog dialog(this, tr("Seleccionar fichero"),ruta);
    //initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);
    if (dialog.exec() == QDialog::Accepted){
    	posicion=0;
    	if(cargarCarpeta(dialog.selectedFiles().first())){
    		QDir directorio(dialog.selectedFiles().first());
			configuracion.setValue("rutaFichero",directorio.absolutePath());
			configuracion.sync();

    	}
    }
}
void DialogoRecortador::abrirCarpeta(){
	QSettings configuracion;
	QString ruta=QDir::toNativeSeparators(configuracion.value("rutaCarpeta").toString());

    QFileDialog dialog(this, tr("Seleccionar carpeta"),ruta);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
    dialog.setOption(QFileDialog::DontResolveSymlinks, true);
    dialog.setFileMode(QFileDialog::Directory);
    //initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);
    if (dialog.exec() == QDialog::Accepted){
    	if(cargarCarpeta(dialog.selectedFiles().first())){
    		QDir directorio(dialog.selectedFiles().first());
			configuracion.setValue("rutaCarpeta",directorio.absolutePath());
			configuracion.sync();

    	}
    }
}
void DialogoRecortador::borrarMat(void *mat){
    delete static_cast<cv::Mat*>(mat);
}

bool DialogoRecortador::cargarCarpeta(const QString &carpeta){
	ruta = carpeta;
	QDir dir(carpeta);
	QStringList nameFilters;
	nameFilters << "*.jpg" << "*.png";
	ficheros = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
	//qDebug()<<ficheros.size()<<"\r\n";
	posicion = 0;
	cogerImagen(posicion);
	update();
	//qDebug()<<"Carpeta cargada";
	return true;
	/*imagenCV = imread( carpeta.toStdString());
	if ( !imagenCV.data ){
		QMessageBox mensaje;
		mensaje.setText("La imagen seleccionada no es válida");
		mensaje.setIcon(QMessageBox::Warning);
		mensaje.exec();
		return false;
	}
	cvtColor(imagenCV, imagenCV, COLOR_BGR2RGB);
	procesado=false;
	setImage(cv_qimage(imagenCV));*/

	//setWindowFilePath(carpeta);

//	const QString message = tr("Abierto \"%1\", %2x%3, Depth: %4")
	//	.arg(QDir::toNativeSeparators(carpeta)).arg(image.width()).arg(image.height()).arg(image.depth());
	//statusBar()->showMessage(message);
	return true;
	/*namedWindow("Display Image", WINDOW_AUTOSIZE );
	imshow("Display Image", image);
	waitKey(0);




	QImageReader reader(carpeta);

    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(carpeta), reader.errorString()));
        return false;
    }
    setImage(newImage);

	setWindowFilePath(carpeta);

	const QString message = tr("Abierto \"%1\", %2x%3, Depth: %4")
		.arg(QDir::toNativeSeparators(carpeta)).arg(image.width()).arg(image.height()).arg(image.depth());
	statusBar()->showMessage(message);
	return true;*/
}
QImage DialogoRecortador::cargarImagen(const QString &fichero){
	QImageReader reader(fichero);
	if (!reader.canRead()) {
		return QImage();
	}

	QImage imagen;
	if (!reader.read(&imagen)) {
		return QImage();
	}
	//Calculamos la escala
	qreal escalaTemporal=1;
	int w=anchoImagen-PADDING[3]-PADDING[1];
	int h=altoImagen-PADDING[0]-PADDING[2];
	if(imagen.size().width()>w){
		qDebug()<<w<<"/"<<imagen.size().width();
		escalaTemporal=(qreal)w/(qreal)imagen.size().width();
		qDebug()<<escalaTemporal;
	}
	if(imagen.size().height()>h){
		qDebug()<<h<<"/"<<imagen.size().height();
		qreal escalaTemporal2=(qreal)h/(qreal)imagen.size().height();
		if(escalaTemporal2<escalaTemporal){
			escalaTemporal=escalaTemporal2;
		}
		qDebug()<<escalaTemporal2;
	}
	escala=escalaTemporal;
	/*const QSize maximumSize(2000, 2000); // Reduce in case someone has large photo images.
	if (imagen.size().width() > maximumSize.width() || imagen.height() > maximumSize.height())
		imagen = imagen.scaled(maximumSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);*/
	return imagen;
}
void DialogoRecortador::siguienteImagen(){
	if (ficheros.isEmpty())
	        return;

	    if (posicion < ficheros.size()-1) {
	        ++posicion;
	        if (posicion < ficheros.size())
	            imagen = cargarImagen(ruta+QLatin1String("/")+ficheros.at(posicion));
	        else
	            imagen = QImage();
	    }
	    update();
}
void DialogoRecortador::cogerImagen(int indice){
	if (ficheros.isEmpty())
		return;

	if (indice < 0 || indice >= ficheros.size()) {
        return;
    }
	posicion = indice;
    imagen = cargarImagen(ruta+QLatin1String("/")+ficheros.at(posicion));
	update();
}


void DialogoRecortador::paintEvent(QPaintEvent *){
	int top=this->top+PADDING[0];
	int left=PADDING[3];
	QPainter p(this);
	/*
	 const qreal iw = currentImage.width();
    const qreal ih = currentImage.height();
    const qreal wh = height();
    const qreal ww = width();

    p.translate(ww/2, wh/2);
    p.translate(horizontalOffset, verticalOffset);
    p.rotate(rotationAngle);

    p.translate(-iw/2, -ih/2);
    p.drawImage(0, 0, currentImage);
	 /**/
	//
	qreal escala=this->escala*this->zoom;
	p.scale(escala, escala);
	//qDebug()<<escala;
	p.fillRect(left,top,anchoImagen-PADDING[1],altoImagen-PADDING[2],Qt::darkGray);
	p.drawRect(left,top,anchoImagen-PADDING[0],altoImagen-PADDING[2]);
	//Ahora tenemos que centrar
	//TODO: Acelarar guardando en variables y solo cambiandolas cuando se cambie la imagen

	//p.drawImage(PL+2+posX[0],top+2+posY[0], imagen); //Movemos dos tanto arriba como abajo para el borde + el padding
	//if(imagenTratada!=NULL){

//	}else{
	p.drawImage(left, top, imagen);
	//p.drawImage(0, 0, imagen);
	qDebug()<<escala;
	qDebug()<<this->escala;


	//}
}
void DialogoRecortador::mousePressEvent(QMouseEvent *event){
	qDebug()<<"Presiono";
}
void DialogoRecortador::mouseMoveEvent(QMouseEvent *event){
	qDebug()<<"Muevo";
}
void DialogoRecortador::mouseReleaseEvent(QMouseEvent *event){
	qDebug()<<"Suelto";
}
void DialogoRecortador::resizeEvent(QResizeEvent *event){
	anchoImagen=this->width()-PADDING[1]-PADDING[3];
	altoImagen=this->height()-PADDING[0]-PADDING[2];
}
void DialogoRecortador::wheelEvent(QWheelEvent *event){
	//qDebug()<<"Muevo rueda ["<<((event->delta()>>3)/15)<<"]";
	zoom+=(0.01)*((event->delta()>>3)/15);
	update();
}

void DialogoRecortador::ponerAcciones(){
    /*QMenu *fileMenu = menuBar()->addMenu(tr("&Abrir"));

    QAction *openAct = fileMenu->addAction(tr("&Abrir..."), this, &DialogoRecortador::open);
    openAct->setShortcut(QKeySequence::Open);

    fileMenu->addSeparator();

    QAction *exitAct = fileMenu->addAction(tr("&Salir"), this, &QWidget::close);
    exitAct->setShortcut(tr("Ctrl+Q"));
    top+=menuBar()->height();
/**/
}
void DialogoRecortador::ponerToolBar(){

	//QMainWindow * mainWindow = new QMainWindow();
	QToolBar * toolBar = new QToolBar(tr("ejecucion"));
	toolBar->setAllowedAreas(Qt::TopToolBarArea);
	toolBar->setMovable(false);

	/*algoritmos=new QComboBox();
	algoritmos->addItem("__ALGORITMOS__");
	toolBar->addWidget(algoritmos);/**/

	QPushButton *abrir=new QPushButton(QIcon(":/img/folder.png"),"Abrir");
	//ejecutar->setEnabled(false);
	connect(abrir, SIGNAL (released()),this, SLOT (abrirCarpeta()));
	toolBar->addWidget(abrir);/**/



	addToolBar(toolBar);
	top+=25;//toolBar->heightMM();

}
