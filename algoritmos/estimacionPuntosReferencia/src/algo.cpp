/*
 * algo.cpp
 *
 *  Created on: 18 Jul. 2018
 *      Author: ray
 */

#include "algo.h"

namespace vision {
   EPR::EPR(){
      crearParametro("Ampliar region", TIPO::NUMBER);
      setParametro("Ampliar region", std::string("5"));
      crearParametro("Inicializar", TIPO::FUNCTION);
      crearParametro("encontrados", TIPO::NUMBER);
      crearParametro("Algoritmo detección", TIPO::STRING);
      #ifdef WIN32
         setParametro("Algoritmo detección",std::string("viola_jones.dll"));
      #else
         setParametro("Algoritmo detección",std::string("viola_jones.so"));
      #endif
      crearParametro("Mascara", TIPO::STRING);
      setParametro("Mascara",std::string("model/mean.csv"));
      crearParametro("Mostrar mascara", TIPO::BOOL);
      setParametro("Mostrar mascara",std::string("S"));
      crearParametro("Transformar a mascara", TIPO::BOOL);
      setParametro("Transformar a mascara",std::string("S"));
      crearParametro("Modo de transformación", TIPO::NUMBER);
      setParametro("Modo de transformación",std::string("0"));

      crearParametro("Ancho imagen afín", TIPO::NUMBER);
      setParametro("Ancho imagen afín",std::string("100"));


   }/**/
	bool EPR::procesar(const cv::Mat& imgOriginal) {
	   //Utilizamos la dll de viuolajones creada en el algoritmo para centralizar el código
	   std::string s;
      s=getParametro<std::string>("Mostrar mascara");
      bool mostrarMascara=(s=="s" || s=="S");
      s=getParametro<std::string>("Transformar a mascara");
      bool transformarAMascara=(s=="s" || s=="S");
      s=getParametro<std::string>("Modo de transformación");
      int modoTransformacionMascara=std::stoi(s); //0=Ojos-Labio,1=Ojos-Boca
      s=getParametro<std::string>("Ancho imagen afín");
      int anchoImagenAfin=std::stoi(s);

      std::string sF=getParametro<std::string>("Algoritmo detección");
      const char *fichero=sF.c_str();


      ray::dll::Librerias<vision::Plugin> libreria;
      void * dll=libreria.cargarDLL(fichero);
	   ViolaJones *vj=(ViolaJones*)libreria.cargarClase(dll, "crearInstancia");
	   vj->procesar(imgOriginal);
	   std::vector<cv::Rect_<double>> zonas=*((std::vector<cv::Rect_<double>> *)vj->getValor<void*>("zonas"));
	   std::cout<<"Se han encontrado "<<zonas.size()<<" zonas"<<std::endl;
	   //cv::Mat im=vj->getValor<cv::Mat>("imagen");
	   //setValor("imagen", im);
	   if(!inicializado){
	      inicializar();
	      //cargarMascara();
      }
      Mat_<float> depth_image;
      cv::Mat_<uchar> imgGris;

      float fx = 0, fy = 0, cx = 0, cy = 0;

      convertirGris(imgOriginal, imgGris);
      cv::Mat  temp=imgOriginal.clone();
      cv::Scalar colorCV(0,0,255);
      std::string p=getParametro<std::string>("Ampliar region");
      int ampliarRegion=std::stoi(p);
      for(int i = 0;i < zonas.size();i++){
         //Con el método de HOG la región detectada es más pequeña por lo que se ampliará un poco.
         cv::Rect_<double> zona=cv::Rect_<double>(zonas[i].x-ampliarRegion, zonas[i].y-ampliarRegion, zonas[i].width+(ampliarRegion<<1),zonas[i].height+(ampliarRegion<<1));
         bool success = CLMTracker::DetectLandmarksInImage(imgGris, depth_image,
               zona,
               clm_model, clm_parameters);
         Vec6d pose_estimate_to_draw = CLMTracker::GetCorrectedPoseWorld(clm_model, fx, fy, cx, cy);
         //std::cout<<"escala X: "<<escalaX<<std::endl;
         if(success){
            int n = clm_model.detected_landmarks.rows>>1;
            for (int j = 0; j < n; ++j ){
               cv::circle(temp,cv::Point((clm_model.detected_landmarks.at<double>(j)), clm_model.detected_landmarks.at<double>(j+n)),2,cv::Scalar(255,0,0));
            }

            //Pinto la máscara principal
            if(mostrarMascara){
               for (int j = 0; j < mascaraPrincipal.size(); ++j ){
                  cv::Point puntoMascara(mascaraPrincipal[j].x*zona.width+zona.x,mascaraPrincipal[j].y*zona.height+zona.y);
                  cv::circle(temp,puntoMascara,3,cv::Scalar(0,0,255));
               }
            }
            if(transformarAMascara){
               int puntosTransformacion[3];
               switch(modoTransformacionMascara){
                  case 0:
                     puntosTransformacion[0]=39;
                     puntosTransformacion[1]=42;
                     puntosTransformacion[2]=57;
                     break;
                  case 1:
                  default:
                     puntosTransformacion[0]=36;
                     puntosTransformacion[1]=45;
                     puntosTransformacion[2]=33;
                     break;

               }
               std::vector<cv::Point2f> origen;
               std::vector<cv::Point2f> destino;
               for(int iTrans=0;iTrans<3; iTrans++){
                  cv::Point2f pO(clm_model.detected_landmarks.at<double>(puntosTransformacion[iTrans]),clm_model.detected_landmarks.at<double>(puntosTransformacion[iTrans]+n));
                  origen.push_back(pO);
                  cv::Point2f pD((mascaraPrincipal[puntosTransformacion[iTrans]].x*zona.width),(mascaraPrincipal[puntosTransformacion[iTrans]].y*zona.height));
                  destino.push_back(pD);
               }


               //Calculamos la matríz de afinidad
               cv::Size size=cv::Size((maxMascaraPrincipal.x-minMascaraPrincipal.x)*zona.width,(maxMascaraPrincipal.y-minMascaraPrincipal.y)*zona.height);
               std::cout<<"W:"<<size.width<<", H:"<<size.height<<std::endl;
               cv::Mat_<double> T=cv::getAffineTransform(origen, destino);

               cv::Mat imgAfin;//=imgOriginal.clone();//(zona.width,zona.height,imgOriginal.type());
               //Aplicamos la afinidad a la imagen
               cv::warpAffine(imgOriginal,imgAfin, T,size);
               cv::Mat imgAfinEscalada;
               cv::resize(imgAfin,imgAfinEscalada,cv::Size(anchoImagenAfin,anchoImagenAfin/proporcionAfin));
               //imgAfin.resize((anchoImagenAfin/(proporcionAfin)));
               setValor("imagen", imgAfinEscalada);
               return true;
            }
            //Fin del pintado de la mácara principal
            cv::rectangle(temp, zona, colorCV);



         }else{
            cv::rectangle(temp, zona, cv::Scalar(0,255,0));
         }

      }
      setValor("imagen", temp);
	   return true;

   }
	void EPR::inicializar(){
	   clm_model.Read("model/main_ccnf_general.txt");
      clm_parameters.multi_view=true;


      cargarMascara();

	   inicializado=true;
	}
	void EPR::cargarMascara(){
      mascaraPrincipal.clear();
      std::string s=getParametro<std::string>("Mascara");
      double maxX=0,maxY=0,minX=0,minY=0;

      std::filebuf file;
      boost::filesystem::path p(s.c_str());
      if (boost::filesystem::exists(p)){
         boost::filesystem::ifstream ifs;
         ifs.open(p, std::ios::in);
         if (ifs.is_open()) {

            while (std::getline(ifs, s)){
               //std::cout<<s.c_str()<<std::endl;
               std::string::size_type inicio = s.find_first_not_of( " \f\t\v" );
               cv::Point_<double> punto;
               if ((inicio != std::string::npos) || (std::string( "#;" ).find( s[ inicio ] ) == std::string::npos)){
                  std::string::size_type final = s.find( ',', inicio );
                  punto.x=std::stod(s.substr( inicio, final - inicio ));
                  inicio = s.find_first_not_of( " \f\n\r\t\v", final + 1 );
                  final   = s.find_last_not_of(  " \f\n\r\t\v" ) + 1;
                  punto.y=std::stod(s.substr( inicio, final - inicio ));
                  if(punto.x<minX) minX=punto.x;
                  if(punto.x>maxX) maxX=punto.x;
                  if(punto.y<minY) minY=punto.y;
                  if(punto.y>maxY) maxY=punto.y;
                  mascaraPrincipal.push_back(punto);
               }/**/
            }
            ifs.close();
         }
      }else{
         std::cerr<<"No se ha encontrado el fichero de configuración ["<<p.string().c_str()<<"]"<<std::endl;
      }
      maxMascaraPrincipal=cv::Point_<double>(maxX,maxY);
      minMascaraPrincipal=cv::Point_<double>(minX,minY);
      proporcionAfin=(maxX-minX)/(maxY-minY);
	}
	void EPR::convertirGris(const Mat& img, Mat& gris){
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
	void EPR::create_display_image(const Mat& orig, Mat& display_image, CLMTracker::CLM& clm_model){

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

REGISTRAR_PLUGIN(vision::EPR);


