#include "imgviewer.h"


void ImgViewer::paintEvent(QPaintEvent *){

    //qDebug()<< this->width();
    double ancho = this->width();
    double alto = this->height();
    QRectF limite(0, 0, ancho, alto);

    //QImage tempQImage = *image;
    //QImage i2 = image.scaled(ancho, alto, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QPainter fondo(this);
    fondo.fillRect(0,0,ancho,alto,Qt::white);
    QPainter p(this);
    qreal escala=this->escala*this->zoom;
    p.scale(escala, escala);
    double anchoImagen;
    double altoImagen;
    if(image.isNull()){
    	anchoImagen = ancho;
    	altoImagen = alto;
    }else{
    	anchoImagen = static_cast<double>(image.width())*escala;
    	altoImagen = static_cast<double>(image.height())*escala;
    }
    //QRectF tamanyo(0.0, 0.0, anchoImagen, altoImagen);

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
    }
    //qDebug()<<"x:"<<(x+xDesplazado)<<" y:"<<(y+yDesplazado)<<" escala: "<<escala;
    //qDebug()<<"x Desp:"<<(xDesplazado)<<" y Desp:"<<(yDesplazado)<<" zoom: "<<zoom;

    //p.fillRect(0,0,ancho*escala,alto*escala,Qt::white);
    //p.drawRect(0,0,ancho*escala,alto*escala);
    p.drawImage(x+xDesplazado,y+yDesplazado, image);
    //image = QImage();
}

void ImgViewer::borrarMat(void *mat){
    delete static_cast<cv::Mat*>(mat);
}

void ImgViewer::setImage(const QImage &img){
    /*if (image.isNull()){
        qDebug() << "Vista sin imagen";
        return;
    }*/
    imageOriginal=img.copy(img.rect());

    qreal escalaTemporal=1;

	int w=this->width();
	int h=this->height();
	if(imageOriginal.size().width()>w){
		qDebug()<<w<<"/"<<imageOriginal.size().width();
		escalaTemporal=(qreal)w/(qreal)imageOriginal.size().width();
		qDebug()<<escalaTemporal;
	}
	if(imageOriginal.size().height()>h){
		qDebug()<<h<<"/"<<imageOriginal.size().height();
		qreal escalaTemporal2=(qreal)h/(qreal)imageOriginal.size().height();
		if(escalaTemporal2<escalaTemporal){
			escalaTemporal=escalaTemporal2;
		}
		qDebug()<<escalaTemporal2;
	}
	escala=escalaTemporal;


    image = img;//img.scaled(this->width(), this->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);;
    /*if (image.size() != size())
        setFixedSize(image.size());*/
    this->update();

}
void ImgViewer::setPreImageCV(const cv::Mat &img){
	//cv::Mat m
	zoom=1;
	xDesplazado=0;
	yDesplazado=0;
	posXRaton=0;
	posYRaton=0;
	imagenCVOriginal=img.clone();
	conImagen=true;
	setImageCV(img);
}
void ImgViewer::setImageCV(const cv::Mat &img){
	//img.copyTo();
	//bool conRejilla=true;
	//bool conMasInfo=true;
	//bool conFiltro=true;
	for(int i=0; i<imagenesResultados.size();i++){
		delete imagenesResultados[i];
	}
	imagenesResultados.clear();
	estaEjecutando=true;
	qDebug()<<"**************************************";
	qDebug()<<"    Comenzamos procesado de imagen    ";
	qDebug()<<"**************************************";
	qDebug()<<"**************************************\r\n\r\n";
	std::clock_t tiempoInicio = std::clock();
	std::clock_t tiempoParcial=tiempoInicio;
	std::clock_t tiempoFinal;


    cv::Mat *grey_image=new cv::Mat(img.size(),img.type());
    imagenesResultados.push_back(grey_image);
    qDebug()<<"Convertimos a gris";
    cv::cvtColor(img, *grey_image, CV_BGR2GRAY);
    cv::equalizeHist(*grey_image, *grey_image);

    tiempoFinal=std::clock();
    qDebug()<<"Tardo "<<(1000.0 * (tiempoFinal-tiempoParcial) / CLOCKS_PER_SEC)<<"ms";


    std::vector<cv::Rect> caras;
    //std::vector<cv::Rect> facesFrente;
    std::vector<cv::Rect> carasEnPerfil;
    std::vector<cv::Rect> ojos;
    std::vector<cv::Rect> bocas;
    std::vector<cv::Rect> narices;
    // Buscamos los rostros dentro de la imagen
    int proporcion=100;
    qDebug()<<"Busco caras";
    tiempoParcial=std::clock();
    faceCascade.detectMultiScale(*grey_image, caras, 1.1, 3,  0|CV_HAAR_SCALE_IMAGE,
                                 cv::Size(img.cols/proporcion, img.rows/proporcion));/**/

    tiempoFinal=std::clock();
    qDebug()<<"Se han encontrado "<<caras.size()<<" posibles caras";
    qDebug()<<"Tardo "<<(1000.0 * (tiempoFinal-tiempoParcial) / CLOCKS_PER_SEC)<<"ms";


    cv::Scalar colorCaraRejilla(128,128,128);
    cv::Scalar colorRejilla(128,128,128, 0.1);
    cv::Mat *imgCVtemp;
    for( size_t i = 0; i < caras.size(); i++){

    	if(conRejilla){
    		imgCVtemp=new cv::Mat(img.size(),img.type());
    		imagenesResultados.push_back(imgCVtemp);
    		cv::rectangle((cv::Mat)(*imgCVtemp), caras[i], colorCaraRejilla,1);
			//Representamos la rejilla de proporci�n
			cv::Point pEsquinaSuperior(caras[i].x,caras[i].y);
			cv::Point pEsquinaInferior(caras[i].x+caras[i].width-1,caras[i].y+caras[i].height-1);
			int aumento=caras[i].width/5;
			int aumentoActual=0;
			imgCVtemp=new cv::Mat(img.size(),img.type());
			imagenesResultados.push_back(imgCVtemp);
			for(int i=0;i<5;i++){
				cv::line((cv::Mat)(*imgCVtemp),
						cv::Point(pEsquinaSuperior.x+aumentoActual,pEsquinaSuperior.y),
						cv::Point(pEsquinaSuperior.x+aumentoActual,pEsquinaInferior.y),
						colorRejilla,1);
				aumentoActual+=aumento;
			}
			aumento=caras[i].height/16;
			aumentoActual=0;

			for(int i=0;i<16;i++){
				//cv::Point sup(pEsquinaSuperior.x+aumentoActual,pEsquinaSuperior.y);
				//cv::Point inf(pEsquinaSuperior.x+aumentoActual,pEsquinaInferior.y);
				cv::line((cv::Mat)(*imgCVtemp),
						cv::Point(pEsquinaSuperior.x,pEsquinaSuperior.y+aumentoActual),
						cv::Point(pEsquinaInferior.x,pEsquinaSuperior.y+aumentoActual),
						colorRejilla,1);
				aumentoActual+=aumento;
			}
    	}

    }/**/


    /*faceCascade.detectMultiScale(grey_image, carasEnPerfil, 1.1, 1,  0|CV_HAAR_SCALE_IMAGE,
                                 cv::Size(img.cols/proporcion, img.rows/proporcion));
    //Unimos los vectores
    caras.insert(caras.end(),carasEnPerfil.begin(),carasEnPerfil.end());/**/

    if(conMasInfo){
		cv::Scalar colorCara(255,0,255); // Azul + Rojo = Violeta
		cv::Scalar colorOjo(0, 255, 0);  // Verde
		cv::Scalar colorBoca(255,0, 0);  // Azul
		cv::Scalar colorNariz(0,0, 255); // Rojo
		int limiteCoincidenciaCara=3;
		int coincidencias=6;
		for( size_t i = 0; i < caras.size(); i++){
			coincidencias=0;

			cv::Mat faceROI=(*grey_image)(caras[i]);
			qDebug()<<"Busco Ojos";
			tiempoParcial=std::clock();
			/*eyeCascade.detectMultiScale(faceROI,ojos, 1.1,2,0|CV_HAAR_SCALE_IMAGE,
										cv::Size(caras[i].width/5, caras[i].height/8));/**/
			int porcion=faceROI.rows/16;
			int porcion4=porcion<<2;
			qDebug()<<porcion;
			qDebug()<<porcion4;
			qDebug()<<(porcion4+(porcion<<1)+porcion);
			qDebug()<<(porcion<<3);
			cv::Mat zonaOjos(faceROI, cv::Rect(0, porcion4, faceROI.cols, porcion4+porcion) );
			eyeCascade.detectMultiScale(zonaOjos,ojos, 1.1,2,0|CV_HAAR_SCALE_IMAGE,
													cv::Size(caras[i].width/5, caras[i].height/8));
			tiempoFinal=std::clock();
			qDebug()<<"Se han encontrado "<<ojos.size();
			qDebug()<<"Tardo "<<(1000.0 * (tiempoFinal-tiempoParcial) / CLOCKS_PER_SEC)<<"ms";

			qDebug()<<"Busco narices";
			//cv::Mat zonaNariz(faceROI, cv::Rect(0, porcion4+(porcion<<1)+porcion, faceROI.cols, porcion4) );
			cv::Mat zonaNariz(faceROI, cv::Rect(0, porcion4<<1, faceROI.cols, porcion4) );
			tiempoParcial=std::clock();
			noseCascade.detectMultiScale(zonaNariz,narices, 1.1,2,0|CV_HAAR_SCALE_IMAGE,
										cv::Size(caras[i].width/5, caras[i].height/8));
			tiempoFinal=std::clock();
			qDebug()<<"Se han encontrado "<<narices.size();
			qDebug()<<"Tardo "<<(1000.0 * (tiempoFinal-tiempoParcial) / CLOCKS_PER_SEC)<<"ms";

			qDebug()<<"Busco bocas";
			//cv::Mat zonaBoca(faceROI, cv::Rect(0, porcion<<3, faceROI.cols, porcion4) );
			cv::Mat zonaBoca(faceROI, cv::Rect(0, (porcion<<3)+(porcion<<1)+porcion, faceROI.cols, porcion4) );
			tiempoParcial=std::clock();
			mouthCascade.detectMultiScale(zonaBoca,bocas, 1.1,2,0|CV_HAAR_SCALE_IMAGE,
										cv::Size(caras[i].width*(3/5), caras[i].height/8));
			tiempoFinal=std::clock();
			qDebug()<<"Se han encontrado "<<bocas.size();
			qDebug()<<"Tardo "<<(1000.0 * (tiempoFinal-tiempoParcial) / CLOCKS_PER_SEC)<<"ms";





			if(ojos.size()>2){
				coincidencias+=4;
			}else{
				coincidencias+=(int)ojos.size()*2;
			}
			if(bocas.size()>1){
				coincidencias+=1;
			}else{
				coincidencias+=(int)bocas.size();
			}
			if(narices.size()>1){
				coincidencias+=1;
			}else{
				coincidencias+=(int)narices.size();
			}
			tiempoFinal=std::clock();
			qDebug()<<"Tardo "<<(1000.0 * (tiempoFinal-tiempoInicio) / CLOCKS_PER_SEC)<<"ms";
			qDebug()<<"Se han encontrado "<<coincidencias<< " coincidencias.";
			if(coincidencias>=limiteCoincidenciaCara || !conFiltro){
				int porcion=caras[i].height/16;
				int porcion4=porcion<<2;
				imgCVtemp=new cv::Mat(img.size(),img.type());
				imagenesResultados.push_back(imgCVtemp);

				cv::rectangle((cv::Mat)(*imgCVtemp), caras[i], colorCara);

				imgCVtemp=new cv::Mat(img.size(),img.type());
				imagenesResultados.push_back(imgCVtemp);

				for (size_t j = 0; j < ojos.size(); j++) {
					cv::rectangle((*imgCVtemp),
							cv::Rect(ojos[j].x+caras[i].x,(ojos[j].y+caras[i].y+porcion4),ojos[i].width,ojos[i].height),
							colorOjo,3);
				}
				imgCVtemp=new cv::Mat(img.size(),img.type());
				imagenesResultados.push_back(imgCVtemp);
				for (size_t j = 0; j < narices.size(); j++) {
					cv::rectangle((*imgCVtemp),
							cv::Rect(narices[j].x+caras[i].x,(narices[j].y+caras[i].y+(porcion4<<1)),narices[i].width,narices[i].height),
							colorNariz,3);
				}
				imgCVtemp=new cv::Mat(img.size(),img.type());
				imagenesResultados.push_back(imgCVtemp);
				for (size_t j = 0; j < bocas.size(); j++) {
					cv::rectangle((*imgCVtemp),
							cv::Rect(bocas[j].x+caras[i].x,(bocas[j].y+caras[i].y+((porcion<<3)+(porcion<<1)+porcion)),bocas[i].width,bocas[i].height),
							colorBoca,3);
				}

			}

		}/**/
    }
    //Generar Imagen
    cv::Mat imagenRes(img.size(),img.type());
    img.copyTo(imagenRes);
    for(int i=1; i<imagenesResultados.size();i++){
    	imagenRes+= *(imagenesResultados[i]);
	}
    cv::cvtColor(imagenRes, imagenRes, cv::COLOR_BGR2RGB);/**/
    const QImage imageTemp((const unsigned char*)imagenRes.data, imagenRes.cols, imagenRes.rows, imagenRes.step,
                       QImage::Format_RGB888, &borrarMat, new cv::Mat(imagenRes));
    imageTemp.rgbSwapped();
    //Q_ASSERT(image.constBits() == img.data);
    setImage(imageTemp);/**/
    estaEjecutando=false;
}

void ImgViewer::setVideoCamara(bool activar){
    if(!activar && usandoVideoCamara && estaEjecutando){
        emit pararVideo();
    }
    usandoVideoCamara=false;
}



void ImgViewer::pararVideo(){
    timer.stop();
}

void ImgViewer::lanzarVideo(){
	if(!captura.isOpened()){
		//La intentmaos abrir
		setVideo(0);
		if(captura.isOpened()){
			timer.start(0,this);
			emit videoLanzado(true);
		}

	}else{
		usandoVideoCamara=false;
		captura.release();
		emit videoLanzado(false);
    }
}

void ImgViewer::guardarImagen(){
     QString filename = QFileDialog::getSaveFileName(this, tr("Imagen"));
    imageOriginal.save(filename);
}

void ImgViewer::timerEvent(QTimerEvent *ev){
    if (estaEjecutando || ev->timerId() != timer.timerId())
        return;
   // qDebug()<<"Tiempo "<<timer.timerId();
    cv::Mat frame;
    if (!captura.read(frame)){
        timer.stop();
        return;
    }
    estaEjecutando=true;
    setImageCV(frame);
    estaEjecutando=false;
}

void ImgViewer::setIndiceCamara(int indice){
    indiceCamara=indice;
    if(indice>=-1){
        usandoVideoCamara=true;
    }
}

void ImgViewer::setVideo(int indice){
	if(captura.isOpened()){
		captura.release();
	}
	captura.open(indice);
	usandoVideoCamara=true;
    //captura.reset(new cv::VideoCapture(indice));
    //qDebug()<<captura->isOpened();
}

/*void ImgViewer::setVideo(QString fichero){
    captura.reset(new cv::VideoCapture(fichero.toStdString().c_str()));


}/**/

void ImgViewer::mousePressEvent(QMouseEvent* event) {
	botonPulsado[event->button()]=true;
	posXRaton=event->globalX();
	posYRaton=event->globalY();
}

void ImgViewer::mouseMoveEvent(QMouseEvent* event) {
	if(botonPulsado[1]){
		xDesplazado+=event->globalX()-posXRaton;
		yDesplazado+=event->globalY()-posYRaton;
		posXRaton=event->globalX();
		posYRaton=event->globalY();
	}
	//qDebug()<<"x:"<<event->globalX()<<" y:"<<event->globalY();
	//qDebug()<<"x:"<<event->x()<<" y:"<<event->y();
	update();
}

void ImgViewer::mouseReleaseEvent(QMouseEvent* event) {
	botonPulsado[event->button()]=false;
}

void ImgViewer::wheelEvent(QWheelEvent* event) {
	double velocidad=0.1;
	if(tiempoZoomAnterior>0){
		if(event->timestamp()-tiempoZoomAnterior>0.05){
			velocidad=0.1;
		}

	}

	tiempoZoomAnterior=event->timestamp();

	zoom+=velocidad*((event->delta()>>3)/15);
	update();
}

void ImgViewer::ponerRejilla(int valor) {
	conRejilla=(valor==2);
	if(conImagen){
		setImageCV(imagenCVOriginal);
	}
}

void ImgViewer::ponerFiltro(int valor) {
	conFiltro=(valor==2);
	if(conImagen){
		setImageCV(imagenCVOriginal);
	}
}
void ImgViewer::ponerMasInfo(int valor) {
	conMasInfo=(valor==2);
	if(conImagen){
		setImageCV(imagenCVOriginal);
	}
}

void ImgViewer::resizeEvent(QResizeEvent* event) {
}
