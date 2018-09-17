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

#include <../../../herramientas/CLM-framework-master/lib/local/FaceAnalyser/include/FaceAnalyser.h>
#include <../../../herramientas/CLM-framework-master/lib/local/FaceAnalyser/include/GazeEstimation.h>

namespace vision {
	
	class HOGDETECT: public Algoritmo_plugin {
		public:
			~HOGDETECT(){};
			const char * getNombre()const{return "HOG Detect";};
			bool procesar(const cv::Mat & imgOriginal);
		private:
			//void gradiente(const cv::Mat & imgOriginal);
			vector<Rect_<double> > face_detections;
			void convertirGris(const Mat& , Mat& );
	};


} /* namespace vision */

#endif /* ALGORITMOS_SRC_H_ */
