/*
 * utils.cpp
 *
 *  Created on: 5 ago. 2018
 *      Author: ray
 */

#include "utils.h"
#include <iostream>
double  vision::Utils::calcularIoU(int AX1,int AY1,int AX2,int AY2,int BX1,int BY1,int BX2,int BY2) {
   int X1=(AX1>BX1)?AX1:BX1;
   int X2=(AX2<BX2)?AX2:BX2;
   int Y1=(AY1>BY1)?AY1:BY1;
   int Y2=(AY2<BY2)?AY2:BY2;

   if(X2<X1 || Y2<Y1){
      return 0;
   }
   double areaInterna=(X2-X1)*(Y2-Y1);
   double areaUnion=((AX2-AX1)*(AY2-AY1))+((BX2-BX1)*(BY2-BY1))-areaInterna;
   return areaInterna/areaUnion;
}
