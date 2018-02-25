/*
 * inicializar.cpp
 *
 *  Created on: 21 ene. 2018
 *      Author: ray
 */

#include "inicializar.h"
namespace vision {
	ray::utiles::Config configuracion;
	/**
	 * Este método se encarga de inicializar la aplicación
	 */
	void inicializar(){

		boost::filesystem::path rutaDllTemp(vision::configuracion.cogerValor("dlls_temp","dllTEMP"));
		boost::filesystem::create_directory(rutaDllTemp);
		std::string rutaDlls=configuracion.cogerValor("dlls");
		if(rutaDlls!=""){
			//Comprobamos si existe la carpeta.
			boost::filesystem::path p(rutaDlls);
			if (boost::filesystem::exists(p) && boost::filesystem::is_directory(p)){
				//Cogemos los ficheros
				#ifdef WIN32
				 boost::regex filtro(".*\\.dll$");
				#else
				 boost::regex filtro(".*\\.so$");
				#endif
				boost::smatch coincide;
				for(boost::filesystem::directory_entry& f:boost::filesystem::directory_iterator(p)){
					const std::string fichero=f.path().generic_string();
					if(boost::regex_match(fichero,coincide, filtro)){
						boost::filesystem::path final=rutaDllTemp/(f.path().filename().generic_string());
						try{
							//Comprobamos si el fichero original es más reciente que el actual

							if(!boost::filesystem::exists(final)){
								boost::filesystem::copy_file(f.path(),final);
							}else if(boost::filesystem::last_write_time(f.path())>boost::filesystem::last_write_time(final)){
								boost::filesystem::remove(final);
								boost::filesystem::copy_file(f.path(),final);
							}
						}catch(const boost::filesystem::filesystem_error& e){
							std::cout << "Error al copiar fichero " << fichero << " dentro de "<< final<<"\r\n\t "
											 << e.code().message() << '\n';
						}
					}
				}
				/*TODO: Eliminar los ficheros dll que no se encuentren en la carpeta original*/

			}
		}
	};
}
