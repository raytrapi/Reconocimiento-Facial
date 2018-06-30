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

#include <vector>
#include <stdio.h>
namespace vision {
	namespace metodos {
		
		class Viola_Jones {
			private:
				/*cv::CascadeClassifier eyeCascade;
				cv::CascadeClassifier mouthCascade;
				cv::CascadeClassifier noseCascade;
				cv::CascadeClassifier profileCascade;/**/
				
			public:
				Viola_Jones();
				virtual ~Viola_Jones();
				static std::vector<std::vector<cv::Rect>> procesar(const cv::Mat &);
				static std::vector<std::vector<cv::Rect>> procesar(const cv::Mat &,const std::vector<int>);
				static void setClasificador(const char *);
				static void setDeteccionMinima(int, int);
				static std::vector<cv::CascadeClassifier> clasificadores;
				static int minWidth;
				static int minHeight; 
		};
		
		
	
	} /* namespace metodos */
} /* namespace vision */

#endif /* DETECCION_OPENCV_SRC_V_J_VIOLA_JONES_H_ */
