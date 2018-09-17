/*
 * selector.cpp
 *
 *  Created on: 7 jul. 2018
 *      Author: ray
 */

#include "selector.h"

namespace vision {
	namespace recortador {
		
		Selector::Selector() {
			// TODO Auto-generated constructor stub
			
		}
		
		Selector::~Selector() {
			// TODO Auto-generated destructor stub
		}
		
		std::vector<Seleccion>  Selector::load(char* nombre) {

			if(QFileInfo::exists(nombre)){
			   std::vector<Seleccion> selecciones;
			   //Lo cargamos
			   QFile fichero(nombre);
			   fichero.open(QIODevice::ReadOnly);
			   QTextStream entrada(&fichero);
			   while(!entrada.atEnd()){
			      QString linea=entrada.readLine();
			      QStringList campos = linea.split(" ");
			      Seleccion s;
			      s.clasificador=campos[0].toFloat();
			      s.x=campos[1].toFloat();
			      s.y=campos[2].toFloat();
			      s.w=campos[3].toFloat();
			      s.h=campos[4].toFloat();
			      selecciones.push_back(s);
			   }
			   fichero.close();
				return selecciones;
			}

			return {};
		}/**/
	
	} /* namespace recortador */
} /* namespace vision */

