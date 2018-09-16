/*
 * viola_jones.h
 *
 *  Created on: 29 abr. 2018
 *      Author: ray
 */

#ifndef DETECCION_OPENCV_SRC_V_J_VIOLA_JONES_H_
#define DETECCION_OPENCV_SRC_V_J_VIOLA_JONES_H_
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include "../../../../utilidades/utils/src/utils.h"
#include <QColor>


#include <vector>
#include <tuple>
#include <iostream>

namespace vision {
	namespace metodos {
		struct RestClasificacion{
		   public:
		      std::vector<std::pair<cv::Rect_<double>,bool>> clasificados;
		      const char * nombre;
		      QColor color;
		      bool activo;
		      RestClasificacion(std::vector<cv::Rect_<double>> r, const char *n, QColor c, bool a){
		         std::vector<std::pair<cv::Rect_<double>, bool>> v;
		         for(int i=0;i<r.size();i++){
		            v.push_back(std::pair<cv::Rect_<double>,bool>(r[i],true));
		         }
		         clasificados=v;
		         nombre=n;
		         color=c;
		         activo=a;
		      }
		      void uneZonas(std::vector<std::pair<cv::Rect_<double>,bool>>v){
		         for(int i=0;i<v.size();i++){
		            clasificados.push_back(v[i]);
		         }
		      }
		      void uneZonas(std::vector<cv::Rect_<double>>v){
              for(int i=0;i<v.size();i++){
                 clasificados.push_back(std::pair<cv::Rect_<double>,bool>(v[i],true));
              }
           }
		};
		class Viola_Jones {
			private:
				/*cv::CascadeClassifier eyeCascade;
				cv::CascadeClassifier mouthCascade;
				cv::CascadeClassifier noseCascade;
				cv::CascadeClassifier profileCascade;/**/
				
			public:
				Viola_Jones();
				virtual ~Viola_Jones();
				static std::vector<RestClasificacion> procesar(const cv::Mat &);
				static std::vector<RestClasificacion> procesar(const cv::Mat &,const std::vector<int>);
				static std::vector<RestClasificacion> procesar(const cv::Mat &,const std::vector<int>, bool);

				static void setClasificador(const char *, const char *, QColor);
				static void setDeteccionMinima(int, int);
				static std::vector<std::tuple<cv::CascadeClassifier,const char *, QColor>> clasificadores;
				static int minWidth;
				static int minHeight; 
		};
		
		
	
	} /* namespace metodos */
} /* namespace vision */

#endif /* DETECCION_OPENCV_SRC_V_J_VIOLA_JONES_H_ */
