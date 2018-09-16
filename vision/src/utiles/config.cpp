/*
 * config.cpp
 *
 *  Created on: 3 ene. 2018
 *      Author: ray
 */

#include "config.h"
#include "log.h"

namespace ray {
	namespace utiles {
		
		Config::Config() {
			/*std::ifstream f(fichero);
			f>>misDatos;
			f.close();*/
			std::filebuf file;
			boost::filesystem::path p(fichero);
			if (boost::filesystem::exists(p)){
				boost::filesystem::ifstream ifs;
				ifs.open(p, std::ios::in);
				if (ifs.is_open()) {
					misDatos.operator >>(ifs);
					ifs.close();
				}
			}else{
				Log::error("No se ha encontrado el fichero de configuración ["+p.string()+"]");
			}


		}
		
		Config::~Config() {

		}

		std::string Config::cogerValor(const std::string& clave, const std::string &defecto) {
			if(misDatos.existe(clave)){
				return misDatos[clave];
			}else{
				if(defecto!=""){
					misDatos[clave]=defecto;
				}
				return defecto;
			}
		}
	
	} /* namespace utiles */
} /* namespace vision */
