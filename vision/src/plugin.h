/*
 * plugin.h
 *
 *  Created on: 21 ene. 2018
 *      Author: ray
 */

#ifndef SRC_PLUGIN_H_
#define SRC_PLUGIN_H_
#ifdef WIN32
	#ifdef PLUGIN_EXPORTS
	   #define PLUGIN_EXPORTS   __declspec(dllexport)
	#else
	  #define PLUGIN_EXPORTS   __declspec(dllimport)
	#endif
#else
	#define PLUGIN_EXPORTS
#endif


#include <opencv2/opencv.hpp>
#include <utility>
#include <string>
#include <ctime>
#include <math.h>
#include <map>
#include <vector>
#include <boost/thread.hpp>
namespace vision {
	class PLUGIN_EXPORTS Plugin {
	   public:
	      enum TIPO {NUMBER=0, STRING=1, BOOL=2, POINTER=3, MAT=100, FUNCTION=50};
		private:
			bool conLog=false;
			std::string *_log;
			std::map<std::string, std::pair<TIPO,void *>> parametros;
			std::map<std::string, void *> valores;
			//std::map<std::string,void *> _metodos;
		protected:
			void debug( std::string l){if(conLog){*_log+=l;*_log+="\r\n";};};
			void debug( char *l){if(conLog){*_log+=l;*_log+="\r\n";};};
			void debug( int l){if(conLog){*_log+=l;*_log+="\r\n";};};
			void crearParametro(std::string,TIPO);
			template<typename T> void setValor(std::string,T);
			//template void setValor<cv::Mat>(std::string,cv::Mat);


		public:
			~Plugin();
			virtual void destroy(){};
			virtual const char * getNombre() const=0;
			virtual const char * getTipo() const=0;
			virtual bool procesar(const cv::Mat &)=0;//TODO: Mejorar con rvalue
			template<typename T> T getValor(std::string nombre);
			std::vector<std::pair<std::string,TIPO>> getParametros();
			template<typename T> T getParametro(std::string );
			template<typename T> void setParametro(std::string campo,  T valor);

			//void setParametro(std::string n, void * v);
			//const std::string getParametro(std::string );
			//void * const getParametro(std::string );


			void setDebug(std::string *l){
				conLog=true;
				_log=l;};
			const char * getDebug(){

				return (*_log).c_str();
			};
	};

} /* namespace vision */


template inline void PLUGIN_EXPORTS vision::Plugin::setValor<cv::Mat>(std::string n,cv::Mat v);
template inline void PLUGIN_EXPORTS vision::Plugin::setValor<void *>(std::string n,void * v);
template PLUGIN_EXPORTS inline cv::Mat vision::Plugin::getValor<cv::Mat>(std::string n);
template PLUGIN_EXPORTS inline void * vision::Plugin::getValor<void *>(std::string n);

template inline PLUGIN_EXPORTS void vision::Plugin::setParametro<std::string>(std::string n,const std::string v);
template inline PLUGIN_EXPORTS void vision::Plugin::setParametro<void *>(std::string n,void * v);
template inline PLUGIN_EXPORTS  std::string vision::Plugin::getParametro<std::string>(std::string n);
template inline PLUGIN_EXPORTS void *  vision::Plugin::getParametro<void *>(std::string n);


#define REGISTRAR_PLUGIN(classname) \
	extern "C" vision::Plugin * crearInstancia() {\
			return (vision::Plugin *) new classname();\
	}\
	extern "C" void destroy(vision::Plugin* p) {\
	    delete p;\
	}
#ifdef _WIN32
	extern "C" __declspec(dllexport) vision::Plugin * crearInstancia();
	extern "C" __declspec(dllexport) void destroy(vision::Plugin *);
#endif
#endif /* SRC_PLUGIN_H_ */
