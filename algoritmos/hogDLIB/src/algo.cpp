/*
 * algo.cpp
 *
 *  Created on: 18 Jul. 2018
 *      Author: ray
 */

#include "algo.h"

namespace vision {
	bool HOGDLIB::procesar(const cv::Mat& imgOriginal) {

	   dlib::array2d<dlib::rgb_pixel> imgDLIB;
	   dlib::assign_image(imgDLIB, dlib::cv_image<dlib::bgr_pixel>(imgOriginal));

	   dlib::array2d<dlib::matrix<float, 31,1>> hog;
	   dlib::extract_fhog_features(imgDLIB, hog);
	   std::cout<<"la imagen HOG tiene "<<hog.nr()<<" filas y "<< hog.nc()<<" columnas."<<std::endl;

	   dlib::image_window win(imgDLIB);
	   dlib::image_window winhog(dlib::draw_fhog(hog));
	   cv::Mat imgHOG=dlib::toMat(dlib::draw_fhog(hog));

	   /*        // Another thing you might want to do is map between the pixels in img and the
	           // cells in the hog image.  dlib provides the image_to_fhog() and fhog_to_image()
	           // routines for this.  Their use is demonstrated in the following loop which
	           // responds to the user clicking on pixels in the image img.
	   dlib::point p;  // A 2D point, used to represent pixel locations.
	   while (win.get_next_double_click(p))
	   {
	      dlib::point hp = dlib::image_to_fhog(p);
	      std::cout << "The point " << p << " in the input image corresponds to " << hp << " in hog space." << std::endl;
	      std::cout << "FHOG features at this point: " << trans(hog[hp.y()][hp.x()]) << std::endl;
	   }

	   // Finally, sometimes you want to get a planar representation of the HOG features
	   // rather than the explicit vector (i.e. interlaced) representation used above.
	   dlib::array<dlib::array2d<float> > planar_hog;
	   dlib::extract_fhog_features(imgDLIB, planar_hog);
/**/
	   setValor<cv::Mat>("imagen",imgHOG);
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


