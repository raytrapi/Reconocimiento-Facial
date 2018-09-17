/*
 * utils.h
 *
 *  Created on: 5 ago. 2018
 *      Author: ray
 */

#ifndef UTILIDADES_UTILS_SRC_UTILS_H_
#define UTILIDADES_UTILS_SRC_UTILS_H_
#ifdef WIN32
   #ifndef UTILS
      #define UTILS   __declspec(dllexport)
   #else
      #define UTILS   __declspec(dllimport)
   #endif
#else
   #define UTILS
#endif
namespace vision {
   
   class  Utils {
      public:
         static  double UTILS calcularIoU(int AX1,int AY1,int AX2,int AY2,int BX1,int BY1,int BX2,int BY2);
   };

} /* namespace vision */

#endif /* UTILIDADES_UTILS_SRC_UTILS_H_ */
