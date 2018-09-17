/*
 * algo.cpp
 *
 *  Created on: 18 Jul. 2018
 *      Author: ray
 */

#include "algo.h"

namespace vision {
	bool HOGDETECT::procesar(const cv::Mat& imgOriginal) {
	   Mat_<uchar> imgGris;
	   convertirGris(imgOriginal, imgGris);

	   //vector<Rect_<double> > face_detections;
	   dlib::frontal_face_detector face_detector_hog = dlib::get_frontal_face_detector();

	   vector<double> confidences;
	   CLMTracker::DetectFacesHOG(face_detections, imgGris, face_detector_hog, confidences);


	   // Detect landmarks around detected faces
	   int face_det = 0;
	   cv::Mat  temp=imgOriginal.clone();

	   for(size_t face=0; face < face_detections.size(); ++face){
	      cv::Scalar colorCV(0,0,255);
	      cv::rectangle(temp, face_detections[face], colorCV);
	   }
	   setValor<cv::Mat>("imagen",temp);
	   setValor<void *>("zonas", (void*)&(face_detections));
	   return true;
   }
	void HOGDETECT::convertirGris(const Mat& img, Mat& gris){
	   if(img.channels() == 3){
	      if(img.depth() != CV_8U){
	         if(img.depth() == CV_16U){
	            Mat tmp = img / 256;
	            tmp.convertTo(tmp, CV_8U);
	            cvtColor(tmp, gris, CV_BGR2GRAY);
	         }
	      }else{
	         cvtColor(img, gris, CV_BGR2GRAY);
	      }
	   }else if(img.channels() == 4){
	      cvtColor(img, gris, CV_BGRA2GRAY);
	   }else{
	      if(img.depth() == CV_16U){
	         Mat tmp = img / 256;
	         gris = tmp.clone();
	      }else if(img.depth() != CV_8U){
	         img.convertTo(gris, CV_8U);
	      } else{
	         gris = img.clone();
	      }
	   }
	}
} /* namespace vision */

REGISTRAR_PLUGIN(vision::HOGDETECT);


