/*
 * algo.h
 *
 *  Created on: 18 Jul. 2018
 *      Author: ray
 */

#ifndef ALGORITMOS_SRC_H_
#define ALGORITMOS_SRC_H_
#include <string>
#include <vector>
#include <array>
#include "../../../herramientas/dlib-master/dlib/image_io.h"
#include "../../../herramientas/dlib-master/dlib/image_transforms.h"
#include "../../../herramientas/dlib-master/dlib/gui_widgets.h"
#include "../../../herramientas/dlib-master/dlib/opencv/cv_image.h"
#include "../../../herramientas/dlib-master/dlib/opencv/to_open_cv.h"
#include "../../../vision/src/algoritmoPlugin.h"
#define PI 3.141592653589793238462643383279502884L
#define PI_2 PI*2
#define GRADO0 0
#define GRADO20 0.34906585
#define GRADO40 0.6981317
#define GRADO60 1.047197551
#define GRADO80 1.396263402
#define GRADO100 1.745329252
#define GRADO120 2.094395102
#define GRADO140 2.443460953
#define GRADO160 2.792526803

namespace vision {
	
	class HOGDLIB: public Algoritmo_plugin {
		public:
			~HOGDLIB(){};
			const char * getNombre()const{return "HOG con DLIB";};
			bool procesar(const cv::Mat & imgOriginal);
		private:
			//void gradiente(const cv::Mat & imgOriginal);
			int graduar(double);
	};


} /* namespace vision */

#endif /* ALGORITMOS_SRC_H_ */
