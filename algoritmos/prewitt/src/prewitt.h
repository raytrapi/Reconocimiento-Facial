/*
 * prewitt.h
 *
 *  Created on: 21 ene. 2018
 *      Author: ray
 */

#ifndef ALGORITMOS_SRC_PREWITT_H_
#define ALGORITMOS_SRC_PREWITT_H_
#include <string>

#include "../../src/algoritmoPlugin.h"
namespace vision {
	
	class Prewitt: public Algoritmo_plugin {
		public:
			~Prewitt(){};
			const char * getNombre()const{return "Prewitt";};
			cv::Mat procesar(const cv::Mat & imgOriginal);

	};


} /* namespace vision */

#endif /* ALGORITMOS_SRC_PREWITT_H_ */
