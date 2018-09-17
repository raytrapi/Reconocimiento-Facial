/*
 * algo.cpp
 *
 *  Created on: 18 Jul. 2018
 *      Author: ray
 */

#include "algo.h"

namespace vision {
	bool HOGDLIB::procesar(const cv::Mat& imgOriginal) {

	   bool enColor=false;
		//log("Llego");
		cv::Mat img(imgOriginal.rows,imgOriginal.cols,CV_8U);
		cv::Mat imgAngulo(imgOriginal.rows,imgOriginal.cols,CV_8U);
		cv::Mat imgGris(imgOriginal.rows,imgOriginal.cols,CV_8U);
		cv::Mat imgHistoC=imgOriginal.clone();
		cv::Mat imgHistoN(imgOriginal.rows,imgOriginal.cols,CV_8U, cv::Scalar(0));

		std::vector<std::array<double, 9>> histograma;
		int limiteX=imgOriginal.cols-1;
		int limiteY=imgOriginal.rows-1;
		int iHistograma=-1;
		//generarGraduacion();
		//double graduar=180/PI;//Valor para conversión de radian a grado
		int columnasHistograma=(imgOriginal.cols>>3)+(((imgOriginal.cols&7)!=0)?1:0);//En bloques de 8
		int filasHistograma=(imgOriginal.rows>>3)+(((imgOriginal.rows&7)!=0)?1:0);//En bloques de 8
		for (int i = 0; i < (columnasHistograma*filasHistograma); i++) {
		   histograma.push_back({0,0,0,0,0,0,0,0,0});
      }
		iHistograma=0;
		for(int y=0; y<imgOriginal.rows; y++){
		   //if((x&7)==0){

		   //}
		   /*if((y&7)==0 && y!=0){
            //Estamos en posiciones de 8 así que creamos un nuevo vector de histograma
            //std::cout<<"cargo para X="<<x<<" Y="<<y<<std::endl;
            iHistograma+=columnasHistograma;

         }/**/
		   iHistograma=((y>>3)*columnasHistograma);
		   for(int x=0; x<imgOriginal.cols; x++){
		      //imgHisto.at<uchar>(cv::Point(x,y))=0;
		      if((x&7)==0 && x!=0){
		         iHistograma++;
		      }


		      int gx=0;
		      int gy=0;
		      int color=0;
		      if(x>0 && x<limiteX){
		         //x-1 y
		         //gx-=(imgGris.at<uchar>(cv::Point(x-1,y))<<1);
		         gx-=(imgGris.at<uchar>(cv::Point(x-1,y)));
		      }
		      if(x<limiteX){
		         //x+1 y
		         uchar color=0;
		         if(y==0){
		            cv::Vec3b pixel = imgOriginal.at<cv::Vec3b>(cv::Point(x+1,y));
		            color=rint(0.21*pixel.val[2]+0.72*pixel.val[1]+0.07*pixel.val[0]);
		            imgGris.at<uchar>(cv::Point(x+1,y))=color;
		         }else{
		            color=imgGris.at<uchar>(cv::Point(x+1,y));
		         }
		         //gx+=(color<<1);
		         if(x>0){
		            gx+=(color);
		         }
		      }
		      if(x==0 && y==0){

		         cv::Vec3b pixel = imgOriginal.at<cv::Vec3b>(cv::Point(x,y));
		         uchar color=rint(0.21*pixel.val[2]+0.72*pixel.val[1]+0.07*pixel.val[0]);
		         imgGris.at<uchar>(cv::Point(x,y))=color;
		      }
		      if(y>0 && y<limiteY){
		         //if(x>0){
		         //x-1 y-1
		         //gx-=(imgGris.at<uchar>(cv::Point(x-1,y-1)));
		         //gy-=(imgGris.at<uchar>(cv::Point(x-1,y-1)));
		         //}
		         //if(x<limiteX){
		         //x+1 y-1
		         //   gx+=(imgGris.at<uchar>(cv::Point(x+1,y-1)));
		         //   gy-=(imgGris.at<uchar>(cv::Point(x+1,y-1)));
		         //}
		         //gy-=(imgGris.at<uchar>(cv::Point(x,y-1))<<1);
		            gy-=(imgGris.at<uchar>(cv::Point(x,y-1)));
		      }
		      if(y<limiteY){
		         //if(x>0){
		         //   //x-1 y+1
		         //   gx-=(imgGris.at<uchar>(cv::Point(x-1,y+1)));
		         //   gy+=(imgGris.at<uchar>(cv::Point(x-1,y+1)));
		         //}
		         uchar color;
		         if(x<limiteX){
		            //   //x+1 y+1
		            cv::Vec3b pixel = imgOriginal.at<cv::Vec3b>(cv::Point(x+1,y+1));
		            color=rint(0.21*pixel.val[2]+0.72*pixel.val[1]+0.07*pixel.val[0]);
		            imgGris.at<uchar>(cv::Point(x+1,y+1))=color;
		            //   gx+=(color);
		            //   gy+=(color);
		         }
		         if(x==0){
		            cv::Vec3b pixel = imgOriginal.at<cv::Vec3b>(cv::Point(x,y+1));
		            uchar color=rint(0.21*pixel.val[2]+0.72*pixel.val[1]+0.07*pixel.val[0]);
		            imgGris.at<uchar>(cv::Point(x,y+1))=color;

		         }else{
		            color=(imgGris.at<uchar>(cv::Point(x,y+1)));
		         }
		         if(y>0){
                  gy+=(color);
               }
		      }/**/


		      //	c=255;
		      //}
		      int a=0;
		      double at=0;
		      double aHisto=0;
		      if(gx!=0 || 1==1){
		         at= atan2((gy),(gx));//atan(gy/gx);
		         //at= atan(gy/gx);
		         if(at>PI){
		            at=PI-at;
		         }
		         if(at<0){
		            /*aHisto=(-1)*at;
		            at=(PI_2)+at;/**/
		            at=((-1)*at)-(PI/2);
		         }/*else{
		            aHisto=at;
		         }*/
		         aHisto=at;
		         //Pintar
		         a=graduar(at);
		         a=at*PI/180;
		      }

		      int c=sqrt(gx*gx+gy*gy);
		      if(c>100){
		         c=100;
		         img.at<uchar>(cv::Point(x,y))=100;
		      }else if(c<0){
		         img.at<uchar>(cv::Point(x,y))=0;
		         c=0;
		      }else{
		         img.at<uchar>(cv::Point(x,y))=c;
		      }


		      /*if(gx>255){
               gx=255;
            }else if(gx<0){
               gx=0;
            }
            if(gy>255){
               gy=255;
            }else if(gy<0){
               gy=0;
            }
		      img.at<uchar>(cv::Point(x,y))=gy;
		      /**/
		      //if(c>255){
		      /*if(at<0){
		         //std::cout<<at<<std::endl;
		         //at=180-at;
		      }/**/
		      //img.at<uchar>(cv::Point(x,y))=gx;
		      imgAngulo.at<uchar>(cv::Point(x,y))=a;

		      //(*img.ptr(x,y))=0;
		      //img.at<cv::Vec3b>(cv::Point(x,y)).val[2]=0;//0.21*pixel.val[2]+0.72*pixel.val[1]+0.07*pixel.val[1];

		      //Cargamos el Histograma;

		      /*if(aHisto==GRADO0){
		         histograma[iHistograma][0]+=c;
		      }else/**/
		         if(aHisto<=GRADO20){//0.34906585 = 20 grados
		         //De momento acumulamos en 20
		         //histograma[iHistograma][1]+=c;
		         /*histograma[iHistograma][0]+=c*((GRADO20-aHisto)/20);
		         histograma[iHistograma][1]+=c*((aHisto-GRADO0)/20);/**/
		         histograma[iHistograma][0]+=c*((aHisto-GRADO0)/20);
		         histograma[iHistograma][1]+=c*((GRADO20-aHisto)/20);
		      }else if(aHisto<=GRADO40){//0.6981317 = 40 grados
		         //De momento acumulamos en 20
		         //histograma[iHistograma][2]+=c;
		         /*histograma[iHistograma][1]+=c*((GRADO40-aHisto)/20);
		         histograma[iHistograma][2]+=c*((aHisto-GRADO20)/20);/***/
		         histograma[iHistograma][1]+=c*((aHisto-GRADO20)/20);
		         histograma[iHistograma][2]+=c*((GRADO40-aHisto)/20);
		      }else if(aHisto<=GRADO60){//1.047197551 = 60 grados
		         //De momento acumulamos en 20
		         //histograma[iHistograma][3]+=c;
		         /*histograma[iHistograma][2]+=c*((GRADO60-aHisto)/20);
		         histograma[iHistograma][3]+=c*((aHisto-GRADO40)/20);/**/
		         histograma[iHistograma][2]+=c*((aHisto-GRADO40)/20);
		         histograma[iHistograma][3]+=c*((GRADO60-aHisto)/20);
		      }else if(aHisto<=GRADO80){//1.396263402 = 80 grados
		         //De momento acumulamos en 20
		         //histograma[iHistograma][4]+=c;
		         /*histograma[iHistograma][3]+=c*((GRADO80-aHisto)/20);
		         histograma[iHistograma][4]+=c*((aHisto-GRADO60)/20);/**/
		         histograma[iHistograma][3]+=c*((aHisto-GRADO60)/20);
		         histograma[iHistograma][4]+=c*((GRADO80-aHisto)/20);
		      }else if(aHisto<=GRADO100){//1.745329252 = 100 grados
		         //De momento acumulamos en 20
		         //histograma[iHistograma][5]+=c;
		         /*histograma[iHistograma][4]+=c*((GRADO100-aHisto)/20);
		         histograma[iHistograma][5]+=c*((aHisto-GRADO80)/20);/**/
		         histograma[iHistograma][4]+=c*((aHisto-GRADO80)/20);
		         histograma[iHistograma][5]+=c*((GRADO100-aHisto)/20);
		      }else if(aHisto<=GRADO120){//2.094395102 = 120 grados
		         //De momento acumulamos en 20
		         //histograma[iHistograma][6]+=c;
		         /*histograma[iHistograma][5]+=c*((GRADO120-aHisto)/20);
		         histograma[iHistograma][6]+=c*((aHisto-GRADO100)/20);/**/
		         histograma[iHistograma][5]+=c*((aHisto-GRADO100)/20);
		         histograma[iHistograma][6]+=c*((GRADO120-aHisto)/20);
		      }else if(aHisto<=GRADO140){//2.443460953 = 140 grados
		         //De momento acumulamos en 20
		         //histograma[iHistograma][7]+=c;
		         /*histograma[iHistograma][6]+=c*((GRADO140-aHisto)/20);
		         histograma[iHistograma][7]+=c*((aHisto-GRADO120)/20);/**/
		         histograma[iHistograma][6]+=c*((aHisto-GRADO120)/20);
		         histograma[iHistograma][7]+=c*((GRADO140-aHisto)/20);
		      }else if(aHisto<=GRADO160){//2.792526803 = 160 grados
		         //De momento acumulamos en 20
		         //histograma[iHistograma][8]+=c;
		         /*histograma[iHistograma][7]+=c*((GRADO160-aHisto)/20);
		         histograma[iHistograma][8]+=c*((aHisto-GRADO140)/20);/**/
		         histograma[iHistograma][7]+=c*((aHisto-GRADO140)/20);
		         histograma[iHistograma][8]+=c*((GRADO160-aHisto)/20);
		      }else if(aHisto>GRADO160){//2.792526803 = 160 grados
		         //De momento acumulamos en 20
		         //histograma[iHistograma][0]+=c;
		         /*histograma[iHistograma][8]+=c*((PI-aHisto)/20);
		         histograma[iHistograma][0]+=c*((aHisto-GRADO160)/20);/**/
		         histograma[iHistograma][8]+=c*((aHisto-GRADO160)/20);
		         histograma[iHistograma][0]+=c*((PI-aHisto)/20);
		      }/**/

		   }
		}

		//Normalizamos el histograma en bloque de 16x16
		int iH1=0;
		int iH1_1=iH1+1;
		int iH1_1Div=1;
		int iH2=columnasHistograma;
		int iH2_1=iH2+1;
		int x=0;
		int y=0;
		//int jH2=0;
		//int jH2=columnasHistograma;
		std::vector<std::array<double, 9>> histogramaNormal;
		for(int i=0;i<filasHistograma;i++){
		   for (int j = 0; j <columnasHistograma ; j++) {
		      double normal=0;
		      /*if(iH1_1>=columnasHistograma){
		         iH1_1=iH1-1;
		      }/**/
          if(iH2>=histograma.size()){
            iH2=iH1-(columnasHistograma);
            iH2_1=iH1_1-(columnasHistograma);
          }else{
            if(iH2_1>=histograma.size()){
              iH2_1=iH1_1+(columnasHistograma);
            }
          }
		      for (int k = 0; k < 9; k++) {
		         normal+=histograma[iH1][k]*histograma[iH1][k];
		         normal+=histograma[iH1_1][k]*histograma[iH1_1][k];
		         normal+=histograma[iH2][k]*histograma[iH2][k];
		         normal+=histograma[iH2_1][k]*histograma[iH2_1][k];
		      }
		      normal=sqrt(normal);
		      std::array<double,9> aNormal={0,0,0,0,0,0,0,0,0};
		      std::array<int,9> aOrden={0,1,2,3,4,5,6,7,8};
		      double valTotal=0;
		      for (int k = 0; k < 9; k++) {
		         double valTemp=histograma[iH1][k]/normal;
		         valTotal+=valTemp;
		         aNormal[k]=valTemp;
		         bool ordenado=false;
		         for (int l = 0; l < k && !ordenado; l++) {
		            if(aNormal[aOrden[l]]<valTemp){
		               for (int m = k; m > l; m--) {
		                  aOrden[m]=aOrden[m-1];
		               }
		               aOrden[l]=k;
		               ordenado=true;
		            }
		         }

		      }
		      histogramaNormal.push_back(aNormal);
		      /*std::cout<<iH1<<": {";
		      for (int k = 0; k < 9; k++) {
               std::cout<<(k>0?", ":"")<<histograma[iH1][k];
            }
		      std::cout<<"} {";
            for (int k = 0; k < 9; k++) {
               std::cout<<(k>0?", ":"")<<aNormal[k];
            }
		      std::cout<<"} {";
            for (int k = 0; k < 9; k++) {
               std::cout<<(k>0?", ":"")<<aOrden[k];
            }
            std::cout<<"}"<<std::endl;/**/
		      //Ahora pintamos

		      for (int k = 0; k < 9; k++) {
		         //int longitud=(int)(8*aNormal[k]/valTotal);
		         //cv::Vec3b colorHisto(255*aNormal[k],0,0);
		         int proporColor=255*aNormal[k];
		         cv::Vec3b colorHisto(proporColor,0,0); //Rojo
		         double opacidad=1-aNormal[k];
		         if(opacidad!=1){
                  int xRel=x;
                  int yRel=y;
                  int xRel2=xRel;
                  int yRel2=yRel;
                  int xFin=xRel;
                  int yFin=yRel;

                  switch(k){
                     case 0: //0 grados
                     case 8: //160 grados
                        xFin=x+1;
                        yFin=y+4;
                        break;
                     case 1: // 20 grados
                        xFin=x+1;
                        yFin=y+6;
                        break;
                     case 2: // 40 grados
                        xFin=x+1;
                        yFin=y+7;
                        break;
                     case 3: //60 grados
                        xFin=x+3;
                        yFin=y+7;
                        break;
                     case 4: //80 grados
                        xFin=x+4;
                        yFin=y+7;
                        break;
                     case 5: //100 grados
                        xFin=x+5;
                        yFin=y+7;
                        break;
                     case 6: //120 grados
                        xFin=x+5;
                        yFin=y+7;
                        break;
                     case 7: //140 grados
                        xFin=x+5;
                        yFin=y+6;
                        break;
                  }
                  for (int l = 0; l < 4; l++) {
                     switch(k){
                        case 0: //0 grados
                        case 8:
                           xFin++;
                           break;
                        case 1: // 20 grados
                           xFin++;
                           yFin-=((l&1)==1?1:0);
                           break;
                        case 2: // 40 grados
                           xFin++;
                           yFin--;
                           break;
                        case 3: //60 grados
                           xFin+=((l&1)==1?1:0);
                           yFin--;
                           break;
                        case 4: //80 grados
                           yFin--;
                           break;
                        case 5: //100 grados
                           xFin-=((l&1)==1?1:0);
                           yFin--;
                           break;
                        case 6: //120 grados
                           xFin--;
                           yFin--;
                           break;
                        case 7: //140 grados
                           xFin--;
                           yFin-=((l&1)==1?1:0);
                           break;

                     }
                     if(xFin<img.cols && yFin<img.rows){
                        if(enColor){
                           cv::Vec3b color=imgHistoC.at<cv::Vec3b>(cv::Point(xFin,yFin));
                           //cv::Vec3b color(0,0,0);
                           for (int comp = 0; comp < 3; comp++) {
                              color[comp]=color[comp]*opacidad+colorHisto[comp];
                           }
                           imgHistoC.at<cv::Vec3b>(cv::Point(xFin,yFin))=color;
                        }else{
                           uchar color=imgHistoN.at<uchar>(cv::Point(xFin,yFin));
                           color=color*opacidad+proporColor;
                           imgHistoN.at<uchar>(cv::Point(xFin,yFin))=color;
                        }
                     }

                     /**/
                     //imgHisto.at<uchar>(cv::Point(xFin,yFin))=proporColor;

                  }
               }
		      }
		      iH1++;
		      iH1_1=iH1+1;
		      iH2=iH1+columnasHistograma;
		      iH2_1=iH2+1;
          iH1_1Div++;
          if(iH1_1Div==columnasHistograma){
            iH1_1Div=0;
            iH1_1=iH1-1;
          }
		      x+=8;
		   }
		   //iH1++;
		   //iH2++;
		   x=0;
		   y+=8;
		}

		/*std::cout<<"Imagen ["<<img.cols<<"x"<<img.rows<<"]\r\n";
		for (int y = 0; y < img.rows; y++) {
		   std::cout<<y<<":";
		   for (int x = 0; x < img.cols; x++) {
		      std::cout<<"\t"<< +img.at<uchar>(cv::Point(x,y));
		      if((x&7)==7 && x!=0){
		         std::cout<<"\t";
		      }
		   }
		   std::cout<<std::endl;
		   if((y&7)==7 && y!=0){
            std::cout<<"\r\n";
         }
		}
		for (int yH = 0; yH < filasHistograma; yH++) {
		   int iH=(yH);
		   std::cout<<"Histograma para fila "<<+iH<<std::endl;
		   iH*=columnasHistograma;
		   for (int xH = 0; xH < columnasHistograma; xH++) {
		      iH+=xH;
		      std::cout<<"{";
		      for (int j = 0; j < 9; j++) {
		         std::cout<<"\t"<<+histograma[iH][j];
		      }
		      std::cout<<"}"<<std::endl;
		   }
		   std::cout<<std::endl;
		}
		std::cout<<std::endl;
		for (int yH = 0; yH < filasHistograma; yH++) {
		   int iH=(yH);
		   std::cout<<"HistogramaN para fila "<<+iH<<std::endl;
		   iH*=columnasHistograma;
		   for (int xH = 0; xH < columnasHistograma; xH++) {
		      iH+=xH;
		      std::cout<<"{";
		      for (int j = 0; j < 9; j++) {
		         std::cout<<"\t"<<+histogramaNormal[iH][j];
		      }
		      std::cout<<"}"<<std::endl;
		   }
		   std::cout<<std::endl;
		}
		for (int y = 0; y < imgHistoN.rows; y++) {
		   for (int x = 0; x < imgHistoN.cols; x++) {
		      std::cout<<"\t"<< +imgHistoN.at<uchar>(cv::Point(x,y));
		      if((x&7)==7 && x!=0){
		         std::cout<<"\t";
		      }
		   }
		   std::cout<<std::endl;
		}
		/*cv::Mat copia=imgGris.clone();
      //copia.convertTo(copia, CV_32F,1/255.0);
      cv::Mat gx, gy;
      cv::Sobel(copia,gx, CV_32F, 1, 0 ,1);
      cv::Sobel(copia,gy, CV_32F, 0, 1 ,1);
      cv::Mat mag, angle;
      std::cout<<"X.size "<<gx.size<<" Y.size"<<gy.size<<" type "<<gy.type()<<std::endl;
      cv::cartToPolar(gx, gy, mag, angle, 1);
      for (int x = 0; x < 10 && x<gx.cols; x++) {
         for (int y = 0; y < 10 && y<gx.rows; y++) {
            std::cout<<"x: "<<x<<" y: "<<y<<" cv "<< +gx.at<uchar>(cv::Point(x,y))<<"  mio: "<< +img.at<uchar>(cv::Point(x,y)) <<std::endl;
            for (int y1 = -1; y1 < 2; y1++) {
               for (int x1 = -1; x1 < 2; x1++) {
                  if((x+x1)>=0 && (x+x1<imgGris.rows)){
                     if((y+y1)>=0 && (y+y1<imgGris.cols)){
                        std::cout<<"\t"<<"["<<(x1+x)<<","<<(y1+y)<<"]:"<<+imgGris.at<uchar>(cv::Point(x1+x,y1+y));
                     }else{
                        std::cout<<"\tX";
                     }
                  }else{
                     std::cout<<"\tX";
                  }
               }
               std::cout<<std::endl;
            }
         }
      }

		return mag;/**/
		//return img;
		if(enColor){
		   //return imgHistoC;
		   setValor<cv::Mat>("imagen",imgHistoC);
		}else{
		   //return imgHistoN;
		   setValor<cv::Mat>("imagen",imgHistoN);
		}
		setValor<cv::Mat>("imagen", imgGris);
		//return imgGris;
		return true;
	}
   
   int HOGDLIB::graduar(double v) {

      /*
      //Generación de código
      double g=PI/180;
      for(int i=0;i<256;i++){
         std::cout<<(i>0?"}else ":"")<<"if(v"<<(i==0?"==":"<")<<(i==0?0:atan(i*g))<<"){";
         std::cout<<"return "<<i<<";";
      }
      std::cout<<"}else{return 255;}"<<std::endl;/**/
      if(v==0){return 0;}
      if(v<1.72){
         if(v<0.0174515){return 1;} if(v<0.0348924){return 2;} if(v<0.0523121){return 3;}; if(v<0.0697001){return 4;}; if(v<0.0870459){return 5;}; if(v<0.104339){return 6;}; if(v<0.121571){return 7;}; if(v<0.138729){return 8;}; if(v<0.155806){return 9;}; if(v<0.172792){return 10;}; if(v<0.189678){return 11;}; if(v<0.206455){return 12;}; if(v<0.223115){return 13;}; if(v<0.23965){return 14;}; if(v<0.256053){return 15;}; if(v<0.272316){return 16;}; if(v<0.288432){return 17;}; if(v<0.304396){return 18;}; if(v<0.320201){return 19;}; if(v<0.335842){return 20;}; if(v<0.351315){return 21;}; if(v<0.366614){return 22;}; if(v<0.381735){return 23;}; if(v<0.396675){return 24;}; if(v<0.41143){return 25;}; if(v<0.425998){return 26;}; if(v<0.440375){return 27;}; if(v<0.454561){return 28;}; if(v<0.468552){return 29;}; if(v<0.482348){return 30;}; if(v<0.495947){return 31;}; if(v<0.50935){return 32;}; if(v<0.522554){return 33;}; if(v<0.535561){return 34;}; if(v<0.54837){return 35;}; if(v<0.560982){return 36;}; if(v<0.573397){return 37;}; if(v<0.585616){return 38;}; if(v<0.59764){return 39;}; if(v<0.609471){return 40;}; if(v<0.621109){return 41;}; if(v<0.632557){return 42;}; if(v<0.643816){return 43;}; if(v<0.654887){return 44;}; if(v<0.665774){return 45;}; if(v<0.676477){return 46;}; if(v<0.687){return 47;}; if(v<0.697344){return 48;}; if(v<0.707512){return 49;}; if(v<0.717506){return 50;};return 50;
      }
      if(v<1.054){
       if(v<0.727328){return 51;}; if(v<0.736982){return 52;}; if(v<0.74647){return 53;}; if(v<0.755794){return 54;}; if(v<0.764957){return 55;}; if(v<0.773962){return 56;}; if(v<0.78281){return 57;}; if(v<0.791506){return 58;}; if(v<0.800051){return 59;}; if(v<0.808449){return 60;}; if(v<0.816701){return 61;}; if(v<0.824811){return 62;}; if(v<0.832781){return 63;}; if(v<0.840614){return 64;}; if(v<0.848312){return 65;}; if(v<0.855877){return 66;}; if(v<0.863314){return 67;}; if(v<0.870623){return 68;}; if(v<0.877807){return 69;}; if(v<0.88487){return 70;}; if(v<0.891812){return 71;}; if(v<0.898637){return 72;}; if(v<0.905347){return 73;}; if(v<0.911944){return 74;}; if(v<0.918431){return 75;}; if(v<0.924809){return 76;}; if(v<0.931081){return 77;}; if(v<0.937249){return 78;}; if(v<0.943316){return 79;}; if(v<0.949282){return 80;}; if(v<0.955151){return 81;}; if(v<0.960924){return 82;}; if(v<0.966603){return 83;}; if(v<0.97219){return 84;}; if(v<0.977687){return 85;}; if(v<0.983096){return 86;}; if(v<0.988419){return 87;}; if(v<0.993656){return 88;}; if(v<0.998811){return 89;}; if(v<1.00388){return 90;}; if(v<1.00888){return 91;}; if(v<1.01379){return 92;}; if(v<1.01863){return 93;}; if(v<1.0234){return 94;}; if(v<1.02809){return 95;}; if(v<1.03271){return 96;}; if(v<1.03726){return 97;}; if(v<1.04174){return 98;}; if(v<1.04615){return 99;}; if(v<1.0505){return 100;};return 100;
      }
      if(v<1.20){
       if(v<1.05478){return 101;}; if(v<1.059){return 102;}; if(v<1.06315){return 103;}; if(v<1.06725){return 104;}; if(v<1.07128){return 105;}; if(v<1.07526){return 106;}; if(v<1.07917){return 107;}; if(v<1.08303){return 108;}; if(v<1.08684){return 109;}; if(v<1.09059){return 110;}; if(v<1.09429){return 111;}; if(v<1.09794){return 112;}; if(v<1.10153){return 113;}; if(v<1.10508){return 114;}; if(v<1.10857){return 115;}; if(v<1.11202){return 116;}; if(v<1.11542){return 117;}; if(v<1.11877){return 118;}; if(v<1.12208){return 119;}; if(v<1.12534){return 120;}; if(v<1.12856){return 121;}; if(v<1.13173){return 122;}; if(v<1.13487){return 123;}; if(v<1.13796){return 124;}; if(v<1.14101){return 125;}; if(v<1.14402){return 126;}; if(v<1.14699){return 127;}; if(v<1.14992){return 128;}; if(v<1.15282){return 129;}; if(v<1.15567){return 130;}; if(v<1.15849){return 131;}; if(v<1.16128){return 132;}; if(v<1.16403){return 133;}; if(v<1.16674){return 134;}; if(v<1.16942){return 135;}; if(v<1.17207){return 136;}; if(v<1.17468){return 137;}; if(v<1.17727){return 138;}; if(v<1.17982){return 139;}; if(v<1.18234){return 140;}; if(v<1.18483){return 141;}; if(v<1.18728){return 142;}; if(v<1.18971){return 143;}; if(v<1.19211){return 144;}; if(v<1.19448){return 145;}; if(v<1.19683){return 146;}; if(v<1.19914){return 147;}; if(v<1.20143){return 148;}; if(v<1.20369){return 149;}; if(v<1.20593){return 150;}; return 150;
      }
      if(v<1.29){
       if(v<1.20814){return 151;}; if(v<1.21032){return 152;}; if(v<1.21248){return 153;}; if(v<1.21461){return 154;}; if(v<1.21672){return 155;}; if(v<1.21881){return 156;}; if(v<1.22087){return 157;}; if(v<1.22291){return 158;}; if(v<1.22493){return 159;}; if(v<1.22692){return 160;}; if(v<1.2289){return 161;}; if(v<1.23085){return 162;}; if(v<1.23278){return 163;}; if(v<1.23469){return 164;}; if(v<1.23658){return 165;}; if(v<1.23844){return 166;}; if(v<1.24029){return 167;}; if(v<1.24212){return 168;}; if(v<1.24393){return 169;}; if(v<1.24572){return 170;}; if(v<1.24749){return 171;}; if(v<1.24924){return 172;}; if(v<1.25098){return 173;}; if(v<1.25269){return 174;}; if(v<1.25439){return 175;}; if(v<1.25607){return 176;}; if(v<1.25774){return 177;}; if(v<1.25938){return 178;}; if(v<1.26101){return 179;}; if(v<1.26263){return 180;}; if(v<1.26422){return 181;}; if(v<1.26581){return 182;}; if(v<1.26737){return 183;}; if(v<1.26892){return 184;}; if(v<1.27046){return 185;}; if(v<1.27198){return 186;}; if(v<1.27348){return 187;}; if(v<1.27497){return 188;}; if(v<1.27645){return 189;}; if(v<1.27791){return 190;}; if(v<1.27936){return 191;}; if(v<1.28079){return 192;}; if(v<1.28221){return 193;}; if(v<1.28362){return 194;}; if(v<1.28501){return 195;}; if(v<1.2864){return 196;}; if(v<1.28776){return 197;}; if(v<1.28912){return 198;}; if(v<1.29046){return 199;}; if(v<1.29179){return 200;};return 200;
      }

      if(v<1.29311){return 201;}; if(v<1.29441){return 202;}; if(v<1.29571){return 203;}; if(v<1.29699){return 204;}; if(v<1.29826){return 205;}; if(v<1.29952){return 206;}; if(v<1.30077){return 207;}; if(v<1.302){return 208;}; if(v<1.30323){return 209;}; if(v<1.30444){return 210;}; if(v<1.30565){return 211;}; if(v<1.30684){return 212;}; if(v<1.30802){return 213;}; if(v<1.30919){return 214;}; if(v<1.31036){return 215;}; if(v<1.31151){return 216;}; if(v<1.31265){return 217;}; if(v<1.31378){return 218;}; if(v<1.31491){return 219;}; if(v<1.31602){return 220;}; if(v<1.31712){return 221;}; if(v<1.31822){return 222;}; if(v<1.3193){return 223;}; if(v<1.32038){return 224;}; if(v<1.32145){return 225;}; if(v<1.32251){return 226;}; if(v<1.32356){return 227;}; if(v<1.3246){return 228;}; if(v<1.32563){return 229;}; if(v<1.32665){return 230;}; if(v<1.32767){return 231;}; if(v<1.32868){return 232;}; if(v<1.32968){return 233;}; if(v<1.33067){return 234;}; if(v<1.33165){return 235;}; if(v<1.33263){return 236;}; if(v<1.33359){return 237;}; if(v<1.33455){return 238;}; if(v<1.33551){return 239;}; if(v<1.33645){return 240;}; if(v<1.33739){return 241;}; if(v<1.33832){return 242;}; if(v<1.33924){return 243;}; if(v<1.34016){return 244;}; if(v<1.34106){return 245;}; if(v<1.34197){return 246;}; if(v<1.34286){return 247;}; if(v<1.34375){return 248;}; if(v<1.34463){return 249;}; if(v<1.3455){return 250;}; if(v<1.34637){return 251;}; if(v<1.34723){return 252;}; if(v<1.34809){return 253;}; if(v<1.34894){return 254;}; if(v<1.34978){return 255;};
      return 255;
   }

} /* namespace vision */

REGISTRAR_PLUGIN(vision::HOGDLIB);


