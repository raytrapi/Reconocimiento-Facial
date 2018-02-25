/*
 * sobel.cpp
 *
 *  Created on: 21 ene. 2018
 *      Author: ray
 */

#include "../../viola_jones/src/viola-jones.h"

namespace vision {
	/**
	 * Se encarga de generar la matriz con la suma integral
	 * @param img es una Matriz en escala de grises
	 */
	unsigned long long int* ViolaJones::sumaIntegral(
			const cv::Mat& img) {
		unsigned long long int *integral=new unsigned long long int[img.rows*img.cols];
		for(int x=0; x<img.cols; x++){
			for(int y=0; y<img.rows; y++){

			}
		}
		return integral;
	}
	/**
	 * Se encarga de generar la matriz con la suma integral
	 * @param img es un cv::Mat en color RGB
	 * @param imgGris es un cv::Mat en Gris calculado en este método
	 *
	 * @return un array de UINT64 con los valores integrados según la especificación del documento de Viola & Jones
	 */
	unsigned long long int* ViolaJones::sumaIntegral(
			const cv::Mat& img, cv::Mat& imgGris) {
		unsigned long long int *integral=new unsigned long long int[img.rows*img.cols];
		int pos=0;
		for(int y=0; y<img.rows; y++){
			for(int x=0; x<img.cols; x++){
				cv::Vec3b pixel = img.at<cv::Vec3b>(cv::Point(x,y));
				uchar color=rint(0.21*pixel.val[0]+0.72*pixel.val[1]+0.07*pixel.val[2]);
				imgGris.at<uchar>(cv::Point(x,y))=color;
				integral[pos]=color+(y>0?integral[pos-img.cols]:0)+(x>0?(integral[pos-1]-(y>0?integral[pos-1-img.cols]:0)):0);
				pos++;
			}
		}
		return integral;
	}

	unsigned long long int ViolaJones::valorIntegral(
			const unsigned long long int* integral,
			const int x, const int y,
			const int desplazarX, const int desplazarY,
			const int width, const int height) const {
		//Ahora comprobamos pero la idea es que el algoritmo, por eficacia no compruebe nada
		if(x>width-desplazarX || y>height-desplazarY){
			return 0;
		}

		//TODO: Intentar rascar algo de rendimiento
		return integral[(x+desplazarX-1)+width*(y+desplazarY-1)]+(x>0&&y>0?integral[(x-1)+width*(y-1)]:0)-(x>0?integral[(x-1)+width*(y+desplazarY-1)]:0)-(y>0?integral[(x+desplazarX-1)+width*(y-1)]:0);
	}

	cv::Mat ViolaJones::procesar(const cv::Mat& imgOriginal) {


		//log("Llego");
		cv::Mat img(imgOriginal.rows,imgOriginal.cols,CV_8U);
		cv::Mat imgGris(imgOriginal.rows,imgOriginal.cols,CV_8U);
		unsigned long long int *integral=sumaIntegral(imgOriginal,imgGris);

		unsigned long long int v;
		for(int y=0;y<imgOriginal.rows-100;y++){
			for(int x=0;x<imgOriginal.cols-100;x++){

				v=0;
				/*for(int i=0;i<100;i++){
					for(int j=0;j<100;j++){
						v+=imgGris.at<uchar>(cv::Point(x+i,y+j));

					}
				}/**/
				v=valorIntegral(integral, x, y, 100,100,imgOriginal.cols, imgOriginal.rows);
			}
			std::cout<<v<<"\r\n";
		}
		/*unsigned long long int vR[3]={0,0,0};
		unsigned long long int vI[3]={0,0,0};
		int pruebasX[3]={0,imgGris.cols-100,150};
		int pruebasY[3]={0,imgGris.rows-100,150};
		for(int x=0;x<100;x++){
			for(int y=0;y<100;y++){
				vR[0]+=imgGris.at<uchar>(cv::Point(x+pruebasX[0],y+pruebasY[0]));
				vR[1]+=imgGris.at<uchar>(cv::Point(x+pruebasX[1],y+pruebasY[1]));
				vR[2]+=imgGris.at<uchar>(cv::Point(x+pruebasX[2],y+pruebasY[2]));
			}
		}/**/
		/*vI[0]=valorIntegral(integral, pruebasX[0], pruebasY[0], 100,100,imgOriginal.cols, imgOriginal.rows);
		vI[1]=valorIntegral(integral, pruebasX[1], pruebasY[1], 100,100,imgOriginal.cols, imgOriginal.rows);
		vI[2]=valorIntegral(integral, pruebasX[2], pruebasY[2], 100,100,imgOriginal.cols, imgOriginal.rows);
		/*std::cout<<"VR[0]"<<vR[0]<<"\r\n";
		std::cout<<"VR[1]"<<vR[1]<<"\r\n";
		std::cout<<"VR[2]"<<vR[2]<<"\r\n";
		std::cout<<"VI[0]"<<valorIntegral(integral, pruebasX[0], pruebasY[0], 100,100,imgOriginal.cols, imgOriginal.rows)<<"\r\n";
		std::cout<<"VI[1]"<<valorIntegral(integral, pruebasX[1], pruebasY[1], 100,100,imgOriginal.cols, imgOriginal.rows)<<"\r\n";
		std::cout<<"VI[2]"<<valorIntegral(integral, pruebasX[2], pruebasY[2], 100,100,imgOriginal.cols, imgOriginal.rows)<<"\r\n";*/
		delete integral;
		return imgGris;
		int limiteX=imgOriginal.cols-1;
		int limiteY=imgOriginal.rows-1;
		for(int x=0; x<imgOriginal.cols; x++){
			for(int y=0; y<imgOriginal.rows; y++){

				int gx=0;
				int gy=0;
				int color=0;
				if(x>0){
					gx-=(imgGris.at<uchar>(cv::Point(x-1,y))<<1);

				}
				if(x<limiteX){
					uchar color=0;
					if(y==0){
						cv::Vec3b pixel = imgOriginal.at<cv::Vec3b>(cv::Point(x+1,y));
						color=rint(0.21*pixel.val[0]+0.72*pixel.val[1]+0.07*pixel.val[2]);
						imgGris.at<uchar>(cv::Point(x+1,y))=color;
					}else{
						color=imgGris.at<uchar>(cv::Point(x+1,y));
					}
					gx+=(color<<1);
				}
				if(x==0 && y==0){

					cv::Vec3b pixel = imgOriginal.at<cv::Vec3b>(cv::Point(x,y));
					uchar color=rint(0.21*pixel.val[0]+0.72*pixel.val[1]+0.07*pixel.val[2]);
					imgGris.at<uchar>(cv::Point(x,y))=color;
				}
				if(y>0){
					if(x>0){
						gx-=(imgGris.at<uchar>(cv::Point(x-1,y-1)));
						gy-=(imgGris.at<uchar>(cv::Point(x-1,y-1)));
					}
					if(x<limiteX){
						gx+=(imgGris.at<uchar>(cv::Point(x+1,y-1)));
						gy-=(imgGris.at<uchar>(cv::Point(x+1,y-1)));
					}
					gy-=(imgGris.at<uchar>(cv::Point(x,y-1))<<1);
				}
				if(y<limiteY){
					if(x>0){
						gx-=(imgGris.at<uchar>(cv::Point(x-1,y+1))<<1);
						gy+=(imgGris.at<uchar>(cv::Point(x-1,y+1)));
					}
					if(x<limiteX){
						cv::Vec3b pixel = imgOriginal.at<cv::Vec3b>(cv::Point(x+1,y+1));
						uchar color=rint(0.21*pixel.val[0]+0.72*pixel.val[1]+0.07*pixel.val[2]);
						imgGris.at<uchar>(cv::Point(x+1,y+1))=color;
						gx+=(color);
						gy+=(color);
					}
					if(x==0){
						cv::Vec3b pixel = imgOriginal.at<cv::Vec3b>(cv::Point(x,y+1));
						uchar color=rint(0.21*pixel.val[0]+0.72*pixel.val[1]+0.07*pixel.val[2]);
						imgGris.at<uchar>(cv::Point(x,y+1))=color;
						gy+=(color<<1);
					}
				}/**/
				int c=sqrt(gx*gx-gy*gy);
				if(c>200){
					c=255;
				}else{
					c=0;
				}
				img.at<uchar>(cv::Point(x,y))=c;
				//(*img.ptr(x,y))=0;
				//img.at<cv::Vec3b>(cv::Point(x,y)).val[0]=0;//0.21*pixel.val[0]+0.72*pixel.val[1]+0.07*pixel.val[2];
			}
		}
		return img;
		//return imgGris;
	}

} /* namespace vision */

REGISTRAR_PLUGIN(vision::ViolaJones);


