/*
 * selector.h
 *
 *  Created on: 7 jul. 2018
 *      Author: ray
 */

#ifndef RECORTADOR_SRC_SELECTOR_H_
#define RECORTADOR_SRC_SELECTOR_H_

#include <QDir>
#include <QDebug>
#include <QFile>
#include <vector>


namespace vision {
   namespace recortador {
      struct __declspec(dllexport)  Seleccion{
            float clasificador;
            float x;
            float y;
            float w;
            float h;
      };
      class __declspec(dllexport) Selector {
         public:
            Selector();
            virtual ~Selector();
            static std::vector<Seleccion>  load( char *);
      };
      //typedef Seleccion VISORWIDGET Seleccion;
   } /* namespace recortador */
} /* namespace vision */

#endif /* RECORTADOR_SRC_SELECTOR_H_ */
