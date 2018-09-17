/*
 * algo.cpp
 *
 *  Created on: 18 Jul. 2018
 *      Author: ray
 */

#include "algo.h"

namespace vision {

	bool CNN::procesar(const cv::Mat& imgOriginal) {

	   vision::metodos::Viola_Jones::setClasificador((const char *)(boost::filesystem::current_path().append("clasificadores/haarcascade_frontalface_default.xml").generic_string().c_str()),"Cara",QColor(255,0,255,0));
	   vision::metodos::Viola_Jones::setClasificador((const char *)(boost::filesystem::current_path().append("clasificadores/haarcascade_profileface.xml").generic_string().c_str()),"Perfil",QColor(255,255,0,0));
	   CLMTracker::CLMParameters clm_parameters;
	   CLMTracker::CLM clm_model("model/main_ccnf_general.txt");
	   clm_parameters.multi_view=true;
	   Mat_<float> depth_image;
	   cv::Mat_<uchar> imgGris;

	   float fx = 0, fy = 0, cx = 0, cy = 0;

	   convertirGris(imgOriginal, imgGris);
	   std::vector<vision::metodos::RestClasificacion> zonasInteres=vision::metodos::Viola_Jones::procesar(imgOriginal,{0,1},true);
	   cv::Mat  temp=imgOriginal.clone();
	   //cv::Mat  temp(imgOriginal.rows,imgOriginal.cols,CV_8U,cv::Scalar(0));
	   for(int i=0; i < zonasInteres.size(); i++){
	      cv::Scalar colorCV(0,0,255);
	      std::vector<std::pair<cv::Rect_<double>,bool>> zonas=(std::vector<std::pair<cv::Rect_<double>,bool>>)zonasInteres[i].clasificados;
	      for(int j = 0;j < zonas.size();j++){
            if(zonas[j].second){

               bool success = CLMTracker::DetectLandmarksInImage(imgGris, depth_image, (zonas[j].first), clm_model, clm_parameters);
               Vec6d pose_estimate_to_draw = CLMTracker::GetCorrectedPoseWorld(clm_model, fx, fy, cx, cy);
               //std::cout<<"escala X: "<<escalaX<<std::endl;
               if(success){
                  int n = clm_model.detected_landmarks.rows>>1;
                  for (int i = 0; i < n; ++ i){
                     cv::circle(temp,cv::Point((clm_model.detected_landmarks.at<double>(i)), clm_model.detected_landmarks.at<double>(i+n)),2,cv::Scalar(255,0,0));
                  }
                  cv::rectangle(temp, zonas[j].first, colorCV);

               }


            }
         }
	   }
	   setValor("imagen", temp);
	   return true;
   }
	void CNN::convertirGris(const Mat& img, Mat& gris){
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
	void CNN::create_display_image(const Mat& orig, Mat& display_image, CLMTracker::CLM& clm_model){

	   // Draw head pose if present and draw eye gaze as well

	   // preparing the visualisation image
	   display_image = orig.clone();

	   // Creating a display image
	   Mat xs = clm_model.detected_landmarks(Rect(0, 0, 1, clm_model.detected_landmarks.rows/2));
	   Mat ys = clm_model.detected_landmarks(Rect(0, clm_model.detected_landmarks.rows/2, 1, clm_model.detected_landmarks.rows/2));
	   double min_x, max_x, min_y, max_y;

	   cv::minMaxLoc(xs, &min_x, &max_x);
	   cv::minMaxLoc(ys, &min_y, &max_y);

	   double width = max_x - min_x;
	   double height = max_y - min_y;

	   int minCropX = max((int)(min_x-width/3.0),0);
	   int minCropY = max((int)(min_y-height/3.0),0);

	   int widthCrop = min((int)(width*5.0/3.0), display_image.cols - minCropX - 1);
	   int heightCrop = min((int)(height*5.0/3.0), display_image.rows - minCropY - 1);

	   double scaling = 350.0/widthCrop;

	   // first crop the image
	   display_image = display_image(Rect((int)(minCropX), (int)(minCropY), (int)(widthCrop), (int)(heightCrop)));

	   // now scale it
	   cv::resize(display_image.clone(), display_image, Size(), scaling, scaling);

	   // Make the adjustments to points
	   xs = (xs - minCropX)*scaling;
	   ys = (ys - minCropY)*scaling;

	   Mat shape = clm_model.detected_landmarks.clone();

	   xs.copyTo(shape(Rect(0, 0, 1, clm_model.detected_landmarks.rows/2)));
	   ys.copyTo(shape(Rect(0, clm_model.detected_landmarks.rows/2, 1, clm_model.detected_landmarks.rows/2)));

	   // Do the shifting for the hierarchical models as well
	   for (size_t part = 0; part < clm_model.hierarchical_models.size(); ++part){
	      Mat xs = clm_model.hierarchical_models[part].detected_landmarks(Rect(0, 0, 1, clm_model.hierarchical_models[part].detected_landmarks.rows / 2));
	      Mat ys = clm_model.hierarchical_models[part].detected_landmarks(Rect(0, clm_model.hierarchical_models[part].detected_landmarks.rows / 2, 1, clm_model.hierarchical_models[part].detected_landmarks.rows / 2));

	      xs = (xs - minCropX)*scaling;
	      ys = (ys - minCropY)*scaling;

	      Mat shape = clm_model.hierarchical_models[part].detected_landmarks.clone();

	      xs.copyTo(shape(Rect(0, 0, 1, clm_model.hierarchical_models[part].detected_landmarks.rows / 2)));
	      ys.copyTo(shape(Rect(0, clm_model.hierarchical_models[part].detected_landmarks.rows / 2, 1, clm_model.hierarchical_models[part].detected_landmarks.rows / 2)));

	   }

	   CLMTracker::Draw(display_image, clm_model);

	}
} /* namespace vision */

REGISTRAR_PLUGIN(vision::CNN);


