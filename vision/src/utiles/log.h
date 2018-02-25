/*
 * log.h
 *
 *  Created on: 3 ene. 2018
 *      Author: ray
 */

#ifndef SRC_UTILES_LOG_H_
#define SRC_UTILES_LOG_H_
#include "utilidades.h"

#include <iostream>
#include <string>
namespace ray {
	namespace utiles {
		
		 class UTILIDADES_EXPORTS Log {
			public:
				static void consola(int i);
				static void consola(char * s);
				static void consola(std::string s);
				static void error(char * s);
				static void error(std::string s);
		};
	
	} /* namespace utiles */
} /* namespace vision */

#endif /* SRC_UTILES_LOG_H_ */
