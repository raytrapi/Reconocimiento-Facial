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

#include <QtCore>


#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>



#include "../../../vision/src/dll/librerias.h"

namespace vision {
	
	class PCA: public Algoritmo_plugin {
		public:
	      PCA();
			~PCA(){};
			const char * getNombre()const{return "Cálculo de PCA";};
			bool procesar(const cv::Mat & imgOriginal);
		private:
			std::string pathOrigen;
			std::string pathDestino;
	};


} /* namespace vision */

#endif /* ALGORITMOS_SRC_H_ */
