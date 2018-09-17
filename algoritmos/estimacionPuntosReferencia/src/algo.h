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
#include "../../../vision/src/algoritmoPlugin.h"
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <dlib/image_processing/frontal_face_detector.h>

#include <tbb/tbb.h>

#include "../../../herramientas/CLM-framework-master/lib/local/FaceAnalyser/include/FaceAnalyser.h"
#include "../../../herramientas/CLM-framework-master/lib/local/FaceAnalyser/include/GazeEstimation.h"
#include "../../../herramientas/Deteccion-OPENCV/src/v&j/viola_jones.h"

#include "../../hogDetect/src/algo.h"
#include "../../viola_jones/src/viola-jones.h"
#include "../../../vision/src/dll/librerias.h"

namespace vision {
	
	class EPR: public Algoritmo_plugin {
		public:
	      EPR();
			~EPR(){};
			const char * getNombre()const{return "Estimación de Puntos de referencia";};
			bool procesar(const cv::Mat & imgOriginal);
		private:
			bool inicializado=false;
			CLMTracker::CLMParameters clm_parameters;
			CLMTracker::CLM clm_model;
			//void gradiente(const cv::Mat & imgOriginal);
			void convertirGris(const Mat& , Mat& );
			void create_display_image(const Mat& , Mat& , CLMTracker::CLM& );
			void inicializar();
			void cargarMascara();
			vector<cv::Point_<double>> mascaraPrincipal;
			cv::Point_<double> minMascaraPrincipal;
			cv::Point_<double> maxMascaraPrincipal;
			double proporcionAfin;
	};


} /* namespace vision */

#endif /* ALGORITMOS_SRC_H_ */
