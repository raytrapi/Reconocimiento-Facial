/*
 * sobel.cpp
 *
 *  Created on: 21 ene. 2018
 *      Author: ray
 */

#include "../../viola_jones/src/viola-jones.h"

namespace vision {

   ViolaJones::ViolaJones(){
      crearParametro("encontrados", TIPO::NUMBER);
   }
	/**
	 * Se encarga de generar la matriz con la suma integral
	 * @param img es una Matriz en escala de grises
	 */
	unsigned long long int* ViolaJones::sumaIntegral(
			const cv::Mat& img) {
		unsigned long long int *integral=new unsigned long long int[img.rows*img.cols];
		for(int x=0; x<img.cols; x++){
			for(int y=0; y<img.rows; y++){

			}
		}
		return integral;
	}
	/**
	 * Se encarga de generar la matriz con la suma integral
	 * @param img es un cv::Mat en color RGB
	 * @param imgGris es un cv::Mat en Gris calculado en este m�todo
	 *
	 * @return un array de UINT64 con los valores integrados seg�n la especificaci�n del documento de Viola & Jones
	 */
	unsigned long long int* ViolaJones::sumaIntegral(
			const cv::Mat& img, cv::Mat& imgGris) {
		unsigned long long int *integral=new unsigned long long int[img.rows*img.cols];
		int pos=0;
		for(int y=0; y<img.rows; y++){
			for(int x=0; x<img.cols; x++){
				cv::Vec3b pixel = img.at<cv::Vec3b>(cv::Point(x,y));
				uchar color=rint(0.21*pixel.val[0]+0.72*pixel.val[1]+0.07*pixel.val[2]);
				imgGris.at<uchar>(cv::Point(x,y))=color;
				integral[pos]=color+(y>0?integral[pos-img.cols]:0)+(x>0?(integral[pos-1]-(y>0?integral[pos-1-img.cols]:0)):0);
				pos++;
			}
		}
		return integral;
	}

	unsigned long long int ViolaJones::valorIntegral(
			const unsigned long long int* integral,
			const int x, const int y,
			const int desplazarX, const int desplazarY,
			const int width, const int height) const {
		//Ahora comprobamos pero la idea es que el algoritmo, por eficacia no compruebe nada
		if(x>width-desplazarX || y>height-desplazarY){
			return 0;
		}

		//TODO: Intentar rascar algo de rendimiento
		return integral[(x+desplazarX-1)+width*(y+desplazarY-1)]+(x>0&&y>0?integral[(x-1)+width*(y-1)]:0)-(x>0?integral[(x-1)+width*(y+desplazarY-1)]:0)-(y>0?integral[(x+desplazarX-1)+width*(y-1)]:0);
	}

	bool ViolaJones::procesar(const cv::Mat& imgOriginal) {
	   vision::metodos::Viola_Jones::setClasificador((const char *)(boost::filesystem::current_path().append("clasificadores/haarcascade_frontalface_default.xml").generic_string().c_str()),"Cara",QColor(255,0,255,0));
	   vision::metodos::Viola_Jones::setClasificador((const char *)(boost::filesystem::current_path().append("clasificadores/haarcascade_profileface.xml").generic_string().c_str()),"Perfil",QColor(255,255,0,0));

	   std::vector<vision::metodos::RestClasificacion> zonasInteres=vision::metodos::Viola_Jones::procesar(imgOriginal,{0,1},true);
	   cv::Mat  temp=imgOriginal.clone();
	   this->zonas.clear();
	   for(int i=0; i < zonasInteres.size(); i++){
	      cv::Scalar colorCV(0,0,255);
	      std::vector<std::pair<cv::Rect_<double>,bool>> zonas=(std::vector<std::pair<cv::Rect_<double>,bool>>)zonasInteres[i].clasificados;

	      for(int j = 0;j < zonas.size();j++){
	         if(zonas[j].second){
	            this->zonas.push_back(zonas[j].first);
	            cv::rectangle(temp, zonas[j].first, colorCV);
	         }
	      }
	   }
	   setValor<void*>("zonas",(void *)&this->zonas);
	   setValor<cv::Mat>("imagen",temp);
	   return true;
	}

} /* namespace vision */

REGISTRAR_PLUGIN(vision::ViolaJones);


