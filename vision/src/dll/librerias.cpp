/*
 * librerias.cpp
 *
 *  Created on: 8 ene. 2018
 *      Author: ray
 */

#include "librerias.h"

namespace ray {
	namespace dll {
		//ray::dll::Librerias<Plu> librerias;

		template<class T>
		inline void * Librerias<T>::cargarDLL(const char * fichero){
			#ifdef WIN32
				HINSTANCE hDLL = LoadLibrary(fichero);
				if(hDLL==NULL){
				   LPVOID lpMsgBuf;
				   LPVOID lpDisplayBuf;
				   DWORD dw = GetLastError();

				   FormatMessage(
				         FORMAT_MESSAGE_ALLOCATE_BUFFER |
				         FORMAT_MESSAGE_FROM_SYSTEM |
				         FORMAT_MESSAGE_IGNORE_INSERTS,
				         NULL,
				         dw,
				         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				         (LPTSTR) &lpMsgBuf,
				         0, NULL );

				   lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
				         (lstrlen((LPCTSTR)lpMsgBuf)  + 40) * sizeof(TCHAR));
				   StringCchPrintf((LPTSTR)lpDisplayBuf,
				         LocalSize(lpDisplayBuf) / sizeof(TCHAR),
				         TEXT("(err %d) %s"),
				         dw, lpMsgBuf);
               std::cerr << "Error al cargar librería [LoadLibrary: "<<(LPCTSTR)lpDisplayBuf<<"]"<<std::endl;
				   //MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

				   LocalFree(lpMsgBuf);
				   LocalFree(lpDisplayBuf);

				}
				return hDLL;
			#elif __linux__
				void * manejador;
				//std::cout<<"intento\r\n";
				manejador=dlopen(fichero, RTLD_LAZY);
				if (manejador==NULL) {
					std::cerr << "No ha podido cargar la librería [dlopen: err " << dlerror() << "]"<<std::endl;
            }
				return manejador;
			#endif
			return NULL;
		}
		template<class T>
		inline T * Librerias<T>::cargarClase(void * &hDLL, const char * clase){
			#ifdef WIN32
				PCTOR instancia= (PCTOR)GetProcAddress((HINSTANCE)hDLL,clase);
				if(instancia!=NULL){
					return instancia();
				}
			#elif __linux__
				T * (*instancia)();
				*(void **) (&instancia)=dlsym(hDLL, clase);
				if(instancia!=NULL){
					return (*instancia)();
				}
			#endif
			return NULL;
		}
		
		template<class T>
		inline void ray::dll::Librerias<T>::ok() {
			std::cout<<"llegue\r\n";
		}
		
		template<class T>
		inline ray::dll::Librerias<T>::~Librerias() {
			/*for(int i=0;i<numLibrerias;i++){
				if(librerias[i]!=NULL){
					delete librerias[i];
				}
			}*/
		}

		/**
		 * Localizamos las librer�as
		 */
		template<class T>
		inline void Librerias<T>::leer(const char * ruta) {
				//char * clase="una";
			ray::utiles::Log::consola("Comenzamos la comprobación");
			boost::filesystem::path p(ruta);
			if (boost::filesystem::exists(p) && boost::filesystem::is_directory(p)){
				//Cogemos los ficheros
				#ifdef WIN32
					boost::regex filtro(".*\\.dll$");
				#else
					boost::regex filtro(".*\\.so$");
				#endif
				boost::smatch coincide;
				numLibrerias=0;
				for(boost::filesystem::directory_entry& f:boost::filesystem::directory_iterator(p)){
					const std::string fichero=f.path().generic_string();
					if(boost::regex_match(fichero,coincide, filtro)){
						numLibrerias++;

					}
				}
				std::string log="Se han encontrado ";
				log+=numLibrerias;
				log+=" librerias";
				librerias=new boost::shared_ptr<T>[numLibrerias];
				int iPlugin=0;
				for(boost::filesystem::directory_entry& f:boost::filesystem::directory_iterator(p)){
					const std::string fichero=f.path().generic_string();
					if(boost::regex_match(fichero,coincide, filtro)){
						try{
							void *hDLL=cargarDLL((char *)f.path().generic_string().c_str());
							if(hDLL!=NULL){
								T *p=cargarClase(hDLL, "crearInstancia");
								if(p!=NULL){
									boost::shared_ptr<T> plugin(p);
									librerias[iPlugin++]=plugin;
								}else{
									std::cout<<"Fallo\r\n";
								}
							}else{
								std::cout<<"No se ha podido cargar librería ["<<(char *)f.path().generic_string().c_str()<<"]\r\n";
							}
						}catch (int e) {
							ray::utiles::Log::consola(e);
						}
					}
				}

			}
			//ray::utiles::Log::consola("Terminamos");
		}
		/*template<class T, class K>
		inline void cargar(const boost::filesystem::path &ruta,boost::shared_ptr<K> clase,bool recargar=false) {
		}*/
	
	} /* namespace dll */
} /* namespace ray */


