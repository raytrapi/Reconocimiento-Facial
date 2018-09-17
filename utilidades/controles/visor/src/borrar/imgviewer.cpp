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
	setImageCV(img, true);
}
void ImgViewer::setImageCV(const cv::Mat &img, bool procesar){
	//img.copyTo();
	//bool conPartes=true;
	//bool conFiltro=true;
	
	if(procesar || zonasInteres.size()==0){
		vision::metodos::Viola_Jones::setDeteccionMinima(10,20);	
		if(conRejilla || conPartes){
			zonasInteres=vision::metodos::Viola_Jones::procesar(img,{0});
		}else{
			zonasInteres=vision::metodos::Viola_Jones::procesar(img);
		}
	}
	//cv::cvtColor(res, res, cv::COLOR_BGR2RGB);/**/
	/*const QImage imageTemp((const unsigned char*)res.data, res.cols, res.rows, res.step,
					   ((res.channels()>1)?QImage::Format_RGB888:QImage::Format_Grayscale8), &borrarMat, new cv::Mat(res));
	imageTemp.rgbSwapped();/**/
	
	
	//Q_ASSERT(image.constBits() == img.data);
	std::vector<cv::Scalar> colores;
	colores.push_back(cv::Scalar(255,0,255)); // Azul + Rojo = Violeta
	colores.push_back(cv::Scalar(255,255,0)); // Verde + Azul = 
	colores.push_back(cv::Scalar(0,0,255));
	colores.push_back(cv::Scalar(255,0,0));
	colores.push_back(cv::Scalar(0,255,0));
	
	cv::Mat * temp=new cv::Mat(img);
	int numRois=0;
	for(int i = 0;i < zonasInteres.size();i++){
		for(int j = 0;j < zonasInteres[i].size();j++){
			cv::Rect roi=zonasInteres[i][j];
			std::vector<std::pair<cv::Rect,cv::Scalar>> rois;
			rois.push_back(std::pair<cv::Rect,cv::Scalar>(roi,colores[i]));
			bool esCara=true;
			if(conPartes){
				//Buscamos los ojos
				
				int porcion[2];
				porcion[0]=roi.width/5;
				porcion[1]=roi.height/8;
				std::vector<std::vector<cv::Rect>> partes;
				partes=vision::metodos::Viola_Jones::procesar(
					cv::Mat(img, cv::Rect(roi.x, roi.y+porcion[1], roi.width, porcion[1]<<2)),{2});
				esCara=(partes[0].size()>0 && partes[0].size()<=2);
				for(int j=0;j<partes[0].size();j++){
					partes[0][j].x+=roi.x;
					partes[0][j].y+=roi.y+porcion[1];
					rois.push_back(std::pair<cv::Rect,cv::Scalar>(partes[0][j],colores[2]));
				}/**/
				bool tieneNariz=false;
				partes=vision::metodos::Viola_Jones::procesar(
					cv::Mat(img, cv::Rect(roi.x+porcion[0], roi.y+(porcion[1]<<1)+porcion[1], (porcion[0]<<1)+porcion[0], (porcion[1]<<1)+porcion[1])),{3});
				tieneNariz=(partes[0].size()==1);
				for(int j=0;j<partes[0].size();j++){
					partes[0][j].x+=roi.x+porcion[0];
					partes[0][j].y+=roi.y+(porcion[1]<<1)+porcion[1];
					rois.push_back(std::pair<cv::Rect,cv::Scalar>(partes[0][j],colores[3]));
				}
				partes=vision::metodos::Viola_Jones::procesar(
					cv::Mat(img, cv::Rect(roi.x, roi.y+(porcion[1]<<2)+porcion[1], roi.width, (porcion[1]<<1)+porcion[1])),{4});
				esCara=esCara && tieneNariz&&(partes[0].size()==1);
				for(int j=0;j<partes[0].size();j++){
					partes[0][j].x+=roi.x;
					partes[0][j].y+=roi.y+(porcion[1]<<2)+porcion[1];
					rois.push_back(std::pair<cv::Rect,cv::Scalar>(partes[0][j],colores[4]));
				}
				/*partes=vision::metodos::Viola_Jones::procesar(
					cv::Mat(img, cv::Rect(roi.x+(porcion[0]<<1)+porcion[0], roi.y+(porcion[1]<<1), porcion[0]<<1, porcion[1]<<1)),{2});
				for(int j=0;j<partes[0].size();j++){
					partes[0][j].x+=roi.x+(porcion[0]<<1)+porcion[0];
					partes[0][j].y+=roi.y+(porcion[1]<<1);
					cv::rectangle((cv::Mat)(*temp), partes[0][j], colores[2],1);
				}*/

				//cv::rectangle((cv::Mat)(*temp), cv::Rect(roi.x+porcion[0], roi.y+(porcion[1]<<1)+porcion[1], (porcion[0]<<1)+porcion[0], (porcion[1]<<1)+porcion[1]), colores[1],1);
			}
			if(esCara){
				for(int k=0;k<rois.size();k++){
					cv::rectangle(*temp, rois[k].first, rois[k].second);
				}
			}
			if(conRejilla){
				int rejillasAncho=5;
				int rejillasAlto=8;

				cv::Scalar colorCaraRejilla(128,128,128);
				cv::Scalar colorRejilla(128,128,128, 0.1);
				//temp=new cv::Mat(img.size(),img.type());
				//imagenesResultados.push_back(temp);
				cv::rectangle((cv::Mat)(*temp), roi, colorCaraRejilla,1);
				//Representamos la rejilla de proporci�n
				cv::Point pEsquinaSuperior(roi.x,roi.y);
				cv::Point pEsquinaInferior(roi.x+roi.width-1,roi.y+roi.height-1);
				int aumento=roi.width/rejillasAncho;
				int aumentoActual=0;
				//temp=new cv::Mat(img.size(),img.type());
				//imagenesResultados.push_back(temp);
				for(int i=0;i<rejillasAncho;i++){
					cv::line((cv::Mat)(*temp),
							cv::Point(pEsquinaSuperior.x+aumentoActual,pEsquinaSuperior.y),
							cv::Point(pEsquinaSuperior.x+aumentoActual,pEsquinaInferior.y),
							colorRejilla,1);
					aumentoActual+=aumento;
				}
				aumento=roi.height/rejillasAlto;
				aumentoActual=0;

				for(int i=0;i<rejillasAlto;i++){
					//cv::Point sup(pEsquinaSuperior.x+aumentoActual,pEsquinaSuperior.y);
					//cv::Point inf(pEsquinaSuperior.x+aumentoActual,pEsquinaInferior.y);
					cv::line((cv::Mat)(*temp),
							cv::Point(pEsquinaSuperior.x,pEsquinaSuperior.y+aumentoActual),
							cv::Point(pEsquinaInferior.x,pEsquinaSuperior.y+aumentoActual),
							colorRejilla,1);
					aumentoActual+=aumento;
				}
			}
			
			if(conInfo)	{
				std::string numero=std::to_string(++numRois)+" - "+std::to_string(roi.width)+"x"+std::to_string(roi.height);
				int fontFace = cv::FONT_HERSHEY_COMPLEX_SMALL;
				double fontScale = 1;
				int thickness = 1;
				int baseLine=0;
				const char * numeroStr=numero.c_str();
				int padding= 4;
				qDebug()<<"baseLine: "<<baseLine;
				cv::Size lengthTexto=cv::getTextSize(numeroStr,fontFace,fontScale,thickness,&baseLine);
				cv::rectangle(*temp, cv::Rect(roi.x,roi.y-(lengthTexto.height+padding),lengthTexto.width+4,(lengthTexto.height+padding)), cv::Scalar(255,255,255,0.7),-1);
				cv::putText(*temp, numeroStr ,cv::Point((roi.x+(padding>>1)),(roi.y-(padding>>1))),fontFace,fontScale,cv::Scalar(0,0,0),thickness,8,false);
			}
		}
	}
	//if(temp->)
	cv::cvtColor(*temp,*temp, cv::COLOR_BGR2RGB);
	const QImage imageTemp((const unsigned char*)temp->data, temp->cols, temp->rows, temp->step,
					   ((temp->channels()>1)?QImage::Format_RGB888:QImage::Format_Grayscale8), &borrarMat, new cv::Mat(*temp));
	imageTemp.rgbSwapped();
	
	setImage(imageTemp);
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
    QString filename = QFileDialog::getSaveFileName(this, tr("Guardar imagen"),"untitled.jpg",
                           tr("Images (*.jpg *.png *.xpm)"));
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
void ImgViewer::ponerconPartes(int valor) {
	conPartes=(valor==2);
	if(conImagen){
		setImageCV(imagenCVOriginal);
	}
}
void ImgViewer::ponerconInfo(int valor) {
	conInfo=(valor==2);
	if(conImagen){
		setImageCV(imagenCVOriginal,false);
	}
}
void ImgViewer::resizeEvent(QResizeEvent* event) {
}
