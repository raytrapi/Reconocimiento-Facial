/*
 * prewitt.h
 *
 *  Created on: 7 abril 2018
 *      Author: ray
 */

#ifndef ALGORITMOS_SRC_PREWITT_H_
#define ALGORITMOS_SRC_PREWITT_H_
#include <string>

#include "../../../vision/src/algoritmoPlugin.h"
namespace vision {
	
	class Prewitt: public Algoritmo_plugin {
		public:
			~Prewitt(){};
			const char * getNombre()const{return "Prewitt";};
			bool procesar(const cv::Mat & imgOriginal);

	};


} /* namespace vision */

#endif /* ALGORITMOS_SRC_PREWITT_H_ */
