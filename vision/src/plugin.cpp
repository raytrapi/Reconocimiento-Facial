/*
 * plugin.cpp
 *
 *  Created on: 21 ene. 2018
 *      Author: ray
 */

#include "plugin.h"

namespace vision {
   std::vector<std::pair<std::string,Plugin::TIPO>> Plugin::getParametros() {
      std::vector<std::pair<std::string,Plugin::TIPO>> parametros;
      for(std::map<std::string,std::pair<TIPO,void *>>::iterator it = this->parametros.begin(); it != this->parametros.end(); ++it) {
        parametros.push_back(std::pair<std::string,TIPO>(it->first, std::get<0>(it->second)));
      }
      return parametros;
   }

   template<typename T>
   T Plugin::getValor(std::string nombre) {
      std::map<std::string,void *>::iterator it=this->valores.find(nombre);
      //if(it!=this->valores.end()){
         return (T)*((T*)it->second);
      //}else{
      //   return 0;
     // }
   }

   template<typename T>
   T Plugin::getParametro(std::string nombre) {
      std::map<std::string,std::pair<TIPO,void *>>::iterator it=this->parametros.find(nombre);
      if(it!=this->parametros.end()){
         //if(((std::get<0>(it->second)))!=TIPO::POINTER){

         if(std::get<1>(it->second)!=0){
            //std::cout<<"llego get parametro y tengo "<< ((std::string)(*((std::string *)std::get<1>(it->second)))).c_str()<< std::endl;
            return (T)*((T*)std::get<1>(it->second));
         }else{
            switch(std::get<0>(it->second)){
               case POINTER:
               case FUNCTION:
                  return NULL;
                  break;
               default:
                  return "";
                  break;
            }
         }
         //}else{
         //   return (const T)((T*)std::get<1>(it->second));
         //}
      }else{
         switch(std::get<0>(it->second)){
            case POINTER:
            case FUNCTION:
               return NULL;
               break;
            default:
               return "";
               break;
         }
      }
   }

  /* const std::string Plugin::getParametro(std::string nombre) {
      std::map<std::string,std::pair<TIPO,void *>>::iterator it=this->parametros.find(nombre);
      if(it!=this->parametros.end()){
         return (std::string)(*((std::string *)std::get<1>(it->second)));
      }else{
         return NULL;
      }
   }
   void * const Plugin::getParametro(std::string nombre) {
      std::map<std::string,std::pair<TIPO,void *>>::iterator it=this->parametros.find(nombre);
      if(it!=this->parametros.end()){
         return std::get<1>(it->second);
      }else{
         return NULL;
      }
   }
   /**/
   template<typename T>
   void Plugin::setParametro(std::string n,  T p) {
      std::get<1>(this->parametros[n])=new T(p);

   }
   /*void Plugin::setParametro(std::string n,void * v){

      //std::get<1>this->parametros[n] = *v;
   }*/

   template<typename T>
   void Plugin::setValor(std::string n, T v){
      this->valores[n]=new T(v);
   }


   /*{
      this->valores[n]=v.clone();
   }/**/
   Plugin::~Plugin(){
      for(std::map<std::string,std::pair<TIPO,void *>>::iterator it = this->parametros.begin(); it != this->parametros.end(); ++it) {
         delete (std::get<1>(it->second));
      }
      for(std::map<std::string,void *>::iterator it = this->valores.begin(); it != this->valores.end(); ++it) {
         delete it->second;
      }
      destroy();
   }
   void Plugin::crearParametro(std::string nombre,TIPO tipo){
      parametros[nombre]=std::pair<TIPO, void*>(tipo,0);
   }
} /* namespace vision */

