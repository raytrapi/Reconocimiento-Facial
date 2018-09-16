/*
 * sobel.cpp
 *
 *  Created on: 21 ene. 2018
 *      Author: ray
 */

#include "sobel.h"

namespace vision {
	bool Sobel::procesar(const cv::Mat& imgOriginal) {
      //MATRIZ SOBEL GX [-1  0 -1]  GY [-1 -2 -1]
	   //                [-2  0  2]     [ 0  0  0]
	   //                [-1  0  1]     [ 1  2  1]
		//log("Llego");
		cv::Mat img(imgOriginal.rows,imgOriginal.cols,CV_8U,cv::Scalar(0));
		cv::Mat imgGris(imgOriginal.rows,imgOriginal.cols,CV_8U);
		int limiteX=imgOriginal.cols-1;
		int limiteY=imgOriginal.rows-1;
		for(int y=0; y<imgOriginal.rows && y<10000; y++){
		   for(int x=0; x<imgOriginal.cols && x<10000; x++){


				int gx=0;
				int gy=0;
				int color=0;
				if(x>0){
				   //x-1 y
					gx-=(imgGris.at<uchar>(cv::Point(x-1,y))<<1);
					//std::cout<<"\t\t-para x: "<<x<<" e y: "<<y<<" calculo ("<<(x-1)<<","<<(y)<<") x 2"<<std::endl;
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
					//if(x<10 && y<10){
					//   std::cout<<"\tpinto gris para x: "<<(x+1)<<" e y: "<<(y)<<" c["<<+color<<"]"<<std::endl;
					//}

					gx+=(color<<1);
				}
				if(x==0 && y==0){

					cv::Vec3b pixel = imgOriginal.at<cv::Vec3b>(cv::Point(x,y));
					uchar color=rint(0.21*pixel.val[2]+0.72*pixel.val[1]+0.07*pixel.val[0]);
					imgGris.at<uchar>(cv::Point(x,y))=color;
					//if(x<10 && y<10){
					//   std::cout<<"\tpinto gris para x: "<<x<<" e y: "<<y<<" c["<<+color<<"]"<<std::endl;
					//}
				}
				if(y>0){
					if(x>0){
					   //x-1 y-1
						gx-=(imgGris.at<uchar>(cv::Point(x-1,y-1)));
						gy-=(imgGris.at<uchar>(cv::Point(x-1,y-1)));
						//if(x<10 && y<10){
                  //   std::cout<<"\t\t+para gris para x: "<<(x-1)<<" e y: "<<(y-1)<<"(c -"<<+imgGris.at<uchar>(cv::Point(x-1,y-1))<<")"<<std::endl;
                  //}
						//std::cout<<"\t\t+para x: "<<x<<" e y: "<<y<<" calculo ("<<(x-1)<<","<<(y-1)<<")"<<std::endl;
					}
					if(x<limiteX){
					   //x+1 y-1
						gx+=(imgGris.at<uchar>(cv::Point(x+1,y-1)));
						gy-=(imgGris.at<uchar>(cv::Point(x+1,y-1)));
						//std::cout<<"\t\t+para x: "<<x<<" e y: "<<y<<" calculo ("<<(x+1)<<","<<(y-1)<<")"<<std::endl;
						//if(x<10 && y<10){
                  //   std::cout<<"\t\t+para gris para x: "<<(x+1)<<" e y: "<<(y-1)<<"(c -"<<+imgGris.at<uchar>(cv::Point(x+1,y-1))<<")"<<std::endl;
                  //}
					}
					//if(x<10 && y<10){
               //   std::cout<<"\t\t+para gris para x: "<<(x)<<" e y: "<<(y-1)<<"(c -"<<+imgGris.at<uchar>(cv::Point(x,y-1))<<" x2)"<<std::endl;
               //}
					gy-=(imgGris.at<uchar>(cv::Point(x,y-1))<<1);
				}
				if(y<limiteY){
					if(x>0){
					   //x-1 y+1
						gx-=(imgGris.at<uchar>(cv::Point(x-1,y+1)));
						gy+=(imgGris.at<uchar>(cv::Point(x-1,y+1)));
						//if(x<10 && y<10){
                  //   std::cout<<"\t\t+para gris para x: "<<(x-1)<<" e y: "<<(y+1)<<"(c "<<+imgGris.at<uchar>(cv::Point(x-1,y+1))<<")"<<std::endl;
                  //}
						//std::cout<<"\t\t-para x: "<<x<<" e y: "<<y<<" calculo ("<<(x-1)<<","<<(y+1)<<")"<<std::endl;
					}
					if(x<limiteX){
					   //x+1 y+1
						cv::Vec3b pixel = imgOriginal.at<cv::Vec3b>(cv::Point(x+1,y+1));
						uchar color=rint(0.21*pixel.val[2]+0.72*pixel.val[1]+0.07*pixel.val[0]);
						imgGris.at<uchar>(cv::Point(x+1,y+1))=color;
						//if(x<10 && y<10){
						//   std::cout<<"\tpinto gris para x: "<<(x+1)<<" e y: "<<(y+1)<<" c["<<+color<<"]"<<std::endl;
                  //   std::cout<<"\t\t+para gris para x: "<<(x+1)<<" e y: "<<(y+1)<<"(c "<<+color<<")"<<std::endl;
                  //}
						gx+=(color);
						gy+=(color);

						//std::cout<<"\t\t+para x: "<<x<<" e y: "<<y<<" calculo ("<<(x+1)<<","<<(y+1)<<")"<<std::endl;
					}
					if(x==0){
						cv::Vec3b pixel = imgOriginal.at<cv::Vec3b>(cv::Point(x,y+1));
						uchar color=rint(0.21*pixel.val[2]+0.72*pixel.val[1]+0.07*pixel.val[0]);
						imgGris.at<uchar>(cv::Point(x,y+1))=color;
						//if(x<10 && y<10){
						//   std::cout<<"\tpinto gris para x: "<<x<<" e y: "<<(y+1)<<" c["<<+color<<"]"<<std::endl;
						//   std::cout<<"\t\t+para gris para x: "<<x<<" e y: "<<(y+1)<<"(c "<<+color<<" x2)"<<std::endl;
						//}
						gy+=(color<<1);
					}else{
					   gy+=(imgGris.at<uchar>(cv::Point(x,y+1))<<1);
                  //if(x<10 && y<10){
                  //   std::cout<<"\t\t+para gris para x: "<<(x)<<" e y: "<<(y+1)<<"(c "<<+imgGris.at<uchar>(cv::Point(x,y+1))<<" x2)"<<std::endl;
                  //}
					}
				}/**/
				//if(x<10 && y<10){
            //   std::cout<<"\t\t\tgy para x: "<<(x)<<" e y: "<<(y)<<"("<<+gy<<")"<<std::endl;
            //}
				if(gx>255){
				   gx=255;
				}else if(gx<0){
				   gx=0;
				}
				if(gy>255){
               gy=255;
            }else if(gy<0){
               gy=0;
            }
				int c=sqrt(gx*gx+gy*gy);
				if(c>255){
					c=255;
				}else{
				//	c=0;
				}
				img.at<uchar>(cv::Point(x,y))=c;
				//std::cout<<"Guardo gx x: "<<x<<" y: "<<y<<std::endl;
				//(*img.ptr(x,y))=0;
				//img.at<cv::Vec3b>(cv::Point(x,y)).val[2]=0;//0.21*pixel.val[2]+0.72*pixel.val[1]+0.07*pixel.val[1];
			}
		}

		cv::Mat copia=imgGris.clone();
		//copia.convertTo(copia, CV_32F,1/255.0);
		cv::Mat gx, gy;
		cv::Sobel(copia,gx, CV_8U, 1, 0 ,1);
		cv::Sobel(copia,gy, CV_8U, 0, 1 ,3);
		for (int x = 0; x < 10; x++) {
		   for (int y = 0; y < 10; y++) {
		      std::cout<<"x: "<<x<<" y: "<<y<<" cv "<< +gy.at<uchar>(cv::Point(x,y))<<"  mio: "<< +img.at<uchar>(cv::Point(x,y)) <<std::endl;
            for (int y1 = -1; y1 < 2; y1++) {
               for (int x1 = -1; x1 < 2; x1++) {
                  if((x+x1)>=0){
                     if((y+y1)>=0){
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
		setValor<cv::Mat>("imagen",img);
		return true;
		//return imgGris;
	}

} /* namespace vision */

REGISTRAR_PLUGIN(vision::Sobel);


