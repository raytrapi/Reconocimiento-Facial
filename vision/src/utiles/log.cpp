/*
 * log.cpp
 *
 *  Created on: 3 ene. 2018
 *      Author: ray
 */

#include "log.h"

namespace ray {
	namespace utiles {
		void Log::consola(int i) {
			std::cout<<i<<std::endl;
		}
		void Log::consola(char* s) {
			std::cout<<s<<std::endl;
		}
		
		void Log::consola(std::string s) {
			//if (s!=0){
				std::cout<<s<<std::endl;
			/*}else{
				std::cout<<"es nulo y por eso fallava"<<std::endl;
			}/**/

		}
		
		void Log::error(char* s) {
			consola(s);
		}
		
		void Log::error(std::string s) {
			consola(s);
		}
	
	} /* namespace utiles */
} /* namespace vision */
