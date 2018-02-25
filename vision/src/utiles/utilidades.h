/*
 * utilidades.h
 *
 *  Created on: 31 ene. 2018
 *      Author: ray
 */

#ifndef UTILIDADES
#define UTILIDADES
	#ifdef WIN32
		#ifdef UTILIDADES_EXPORTS
		   #define UTILIDADES_EXPORTS   __declspec(dllexport)
		#else
		  #define UTILIDADES_EXPORTS   __declspec(dllimport)
		#endif
	#else
		#define UTILIDADES_EXPORTS
	#endif
#endif
