#ifndef INICIALIZAR_H
#define INICIALIZAR_H
#include <string>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include "utiles/config.h"
namespace vision{
	//Variable global
	extern ray::utiles::Config configuracion;
	void inicializar();
}
#endif
