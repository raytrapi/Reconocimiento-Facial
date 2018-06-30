/*
 * viola_jones.cpp
 *
 *  Created on: 29 abr. 2018
 *      Author: ray
 */

#include "viola_jones.h"
int vision::metodos::Viola_Jones::minHeight=100;
int vision::metodos::Viola_Jones::minWidth=100;
std::vector<cv::CascadeClassifier> vision::metodos::Viola_Jones::clasificadores;
namespace vision {
	namespace metodos {
		
		Viola_Jones::Viola_Jones() {
			
			minHeight=100;
            
            /*cv::String sEyecascade = "E:/Desarrollo/Vision/build/bin/clasificadores/haarcascade_eye.xml";
            eyeCascade.load(sEyecascade.toStdString().c_str());
            QString s="E:/Desarrollo/Vision/build/bin/clasificadores/haarcascade_mcs_mouth.xml";
            mouthCascade.load(s.toStdString().c_str());
            s="E:/Desarrollo/Vision/build/bin/clasificadores/haarcascade_mcs_nose.xml";
            noseCascade.load(s.toStdString().c_str());
            s="E:/Desarrollo/Vision/build/bin/clasificadores/haarcascade_profileface.xml";
            profileCascade.load(s.toStdString().c_str());*/
            
		}
		
		Viola_Jones::~Viola_Jones() {
			// TODO Auto-generated destructor stub
		}
		std::vector<std::vector<cv::Rect>> Viola_Jones::procesar(const cv::Mat& img) {
			int longitud=clasificadores.size();
			std::vector<int> clasificadoresValidos;
			for(int i=0;i<clasificadores.size();i++){
				clasificadoresValidos.push_back(i);
			}
			std::vector<std::vector<cv::Rect>> res =procesar(img, clasificadoresValidos);
			//delete [] clasificadoresValidos;
			return res;
		}
		std::vector<std::vector<cv::Rect>> Viola_Jones::procesar(const cv::Mat& img, const std::vector<int> clasificadoresValidos) {
			std::vector<std::vector<cv::Rect>> res;
			//cv::CascadeClassifier faceCascade;
			//faceCascade.load("E:/Desarrollo/Vision/build/bin/clasificadores/haarcascade_frontalface_default.xml");
			//std::vector<cv::Mat *> imagenesResultados;
			bool estaEjecutando=true;
			std::cout<<"**************************************"<<std::endl;
			std::cout<<"    Comenzamos procesado de imagen    "<<std::endl;
			std::cout<<"**************************************"<<std::endl;
			std::cout<<"**************************************"<<std::endl<<std::endl;/**/
			std::clock_t tiempoInicio = std::clock();
			std::clock_t tiempoParcial=tiempoInicio;
			std::clock_t tiempoFinal;

		    cv::Mat *imagenGris=new cv::Mat(img.size(),img.type());
		    //imagenesResultados.push_back(imagenGris);
		    std::cout<<"Convertimos a gris"<<std::endl;
		    cv::cvtColor(img, *imagenGris, CV_BGR2GRAY);
		    cv::equalizeHist(*imagenGris, *imagenGris);

		    tiempoFinal=std::clock();
		    std::cout<<"Tardo "<<(1000.0 * (tiempoFinal-tiempoParcial) / CLOCKS_PER_SEC)<<"ms"<<std::endl;

			//int minimoW=100;
			//int minimoH=100;
			
			std::cout<<"minWidth: "<<Viola_Jones::minWidth<<" minHeight: "<< Viola_Jones::minHeight<<std::endl;

			tiempoParcial=std::clock();
			for(int i=0;i<clasificadoresValidos.size();i++){
				std::cout<<"Busco caras clasificador "<<(i+1)<<std::endl;
				std::vector<cv::Rect> elementosDetectados;
				Viola_Jones::clasificadores[clasificadoresValidos[i]].detectMultiScale(*imagenGris, elementosDetectados, 1.1, 3,  0|CV_HAAR_SCALE_IMAGE,
			                              	cv::Size(Viola_Jones::minWidth, Viola_Jones::minHeight));
				tiempoFinal=std::clock();
				std::cout<<"Se han encontrado "<<elementosDetectados.size()<<" posibles caras"<<std::endl;
				std::cout<<"Tardo "<<(1000.0 * (tiempoFinal-tiempoParcial) / CLOCKS_PER_SEC)<<"ms"<<std::endl;
				res.push_back(elementosDetectados);
			}/**/
			

		    return res;
		    /*

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
			faceCascade.detectMultiScale(*imagenGris, caras, 1.1, 3,  0|CV_HAAR_SCALE_IMAGE,
			                              cv::Size(img.cols/proporcion, img.rows/proporcion));

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

			}




			if(conMasInfo){
				cv::Scalar colorCara(255,0,255); // Azul + Rojo = Violeta
				cv::Scalar colorOjo(0, 255, 0);  // Verde
				cv::Scalar colorBoca(255,0, 0);  // Azul
				cv::Scalar colorNariz(0,0, 255); // Rojo
				int limiteCoincidenciaCara=3;
				int coincidencias=6;
				for( size_t i = 0; i < caras.size(); i++){
					coincidencias=0;

					cv::Mat faceROI=(*imagenGris)(caras[i]);
					qDebug()<<"Busco Ojos";
					tiempoParcial=std::clock();

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

				}
			}
			//Generar Imagen
			cv::Mat imagenRes(img.size(),img.type());
			img.copyTo(imagenRes);
			for(int i=1; i<imagenesResultados.size();i++){
				imagenRes+= *(imagenesResultados[i]);
			}
			cv::cvtColor(imagenRes, imagenRes, cv::COLOR_BGR2RGB);
			const QImage imageTemp((const unsigned char*)imagenRes.data, imagenRes.cols, imagenRes.rows, imagenRes.step,
							   QImage::Format_RGB888, &borrarMat, new cv::Mat(imagenRes));
			imageTemp.rgbSwapped();
			//Q_ASSERT(image.constBits() == img.data);
			setImage(imageTemp);
			estaEjecutando=false;/**/
		}
		void Viola_Jones::setClasificador(const char * clasificador){
			cv::CascadeClassifier cascadeClasificador;
			cascadeClasificador.load(clasificador);
			clasificadores.push_back(cascadeClasificador);
		};
		void Viola_Jones::setDeteccionMinima(int ancho, int alto){
			minWidth=ancho;
			minHeight=alto;
		}
	
	} /* namespace vj */
} /* namespace vision */
