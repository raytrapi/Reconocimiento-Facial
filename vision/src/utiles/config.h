/*
 * config.h
 *
 *  Created on: 3 ene. 2018
 *      Author: ray
 */

#ifndef SRC_UTILES_CONFIG_H_
#define SRC_UTILES_CONFIG_H_
#include "utilidades.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
namespace ray {
	namespace utiles {
		 class UTILIDADES_EXPORTS Config {
			private:
				char * fichero="config.cfg";
				struct datos: std::map <std::string, std::string>{
					/**
					 * Informa si la clave buscada existe en el fichero de configuraci�n
					 */
					bool existe(const std::string& s){
						return count(s)!=0;
					}
					/**
					 * Carga valores desde un fichero a la estructura de valores
					 */
					std::istream& operator >>( std::istream& entrada){
						std::string s, clave, valor;
						while (std::getline(entrada, s)){
							std::string::size_type inicio = s.find_first_not_of( " \f\t\v" );
							if ((inicio != std::string::npos) || (std::string( "#;" ).find( s[ inicio ] ) == std::string::npos)){
								std::string::size_type final = s.find( '=', inicio );
								clave = s.substr( inicio, final - inicio );
								clave.erase( clave.find_last_not_of( " \f\t\v" ) + 1 );
								if(!clave.empty()){
									inicio = s.find_first_not_of( " \f\n\r\t\v", final + 1 );
									final   = s.find_last_not_of(  " \f\n\r\t\v" ) + 1;
									valor = s.substr( inicio, final - inicio );
									this->operator [](clave)=valor;
								}
							}
						}
						return entrada;
					}
					std::ostream& operator << ( std::ostream& salida){
						datos::const_iterator iter;
						for (iter = this->begin(); iter != this->end(); iter++){
							salida << iter->first << " = " << iter->second << std::endl;
						}
						return salida;
					}
				};
				datos misDatos;
			public:
				Config();
				virtual ~Config();
				std::string cogerValor(const std::string & clave, const std::string &defecto="");
		};
	
	} /* namespace utiles */
} /* namespace vision */

#endif /* SRC_UTILES_CONFIG_H_ */
