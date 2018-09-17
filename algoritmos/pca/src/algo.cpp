/*
 * algo.cpp
 *
 *  Created on: 18 Jul. 2018
 *      Author: ray
 */

#include "algo.h"

namespace vision {
   PCA::PCA(){
      crearParametro("Carpeta destino", TIPO::STRING);
      pathDestino="PCA/destino/salida.txt";
      setParametro("Destino", pathDestino);
      crearParametro("Carpeta origen", TIPO::STRING);
      pathOrigen="imagenes/PCA/";
      setParametro("Carpeta origen", pathOrigen);

   }/**/
	bool PCA::procesar(const cv::Mat& imgOriginal) {
	   //Utilizamos la dll de viuolajones creada en el algoritmo para centralizar el código
	   //std::string s;
      //s=getParametro<std::string>("Carpeta origen");
	   pathOrigen=getParametro<std::string>("Carpeta origen");
      pathDestino=getParametro<std::string>("Destino");

      debug("Cargando imágenes");
      QDir dir(pathOrigen.c_str());
      QStringList filtro;
      filtro << "*.jpg" << "*.png";
      QStringList ficheros = dir.entryList(filtro, QDir::Files|QDir::Readable, QDir::Name);
      std::string salida="Tenemos ";
      std::vector<cv::Mat> imagenes;
      cv::Mat *datos;
      cv::Size size;
      int canales;
      for (int i = 0; i < ficheros.size(); i++) {
         std::string fichero=pathOrigen;
         fichero.append(ficheros[0].toUtf8().constData());
         cv::Mat img=cv::imread(fichero.c_str());//,CV_LOAD_IMAGE_ANYDEPTH);
         imagenes.push_back(img.clone());


         if(i==0){

            //Redimensionamos datos
            size=img.size();
            canales=img.channels();
            //altoImagen=imagenes[i].rows;
            datos=new cv::Mat(ficheros.size(),img.rows*img.cols*img.channels(), CV_32F);
         }
         if(img.size()!=size){
            std::string mensaje="La imagen [";
            mensaje.append((char*)ficheros[i].constData());
            mensaje.append("] es incorrecta ya que el tamaño a de ser de ");
            mensaje.append(std::to_string(size.width));
            mensaje.append("x");
            mensaje.append(std::to_string(size.height));
            debug(mensaje);
            return false;
         }
         //img.reshape(1,1); //pasamos toda la imagen a un solo canal y una sola fila
        /* std::cout<<"Channels img  "<<(img.reshape(1,1).channels())<<std::endl;
         std::cout<<"Type para img "<<(img.reshape(1,1).type())<<std::endl;
         std::cout<<"Dim para img "<<(img.reshape(1,1).dims)<<std::endl;
         std::cout<<"Size para img "<<(img.reshape(1,1).size().width)<<"x"<<img.reshape(1,1).size().height<<std::endl;
         std::cout<<"Type para row "<<((*datos).row(i).type())<<std::endl;
         std::cout<<"Dim para row "<<((*datos).row(i).dims)<<std::endl;
         std::cout<<"Size para row "<<((*datos).row(i).size().width)<<"x"<<(*datos).row(i).size().height<<std::endl;
         std::cout<<"TOTAL para "<<((((((*datos).row(i).type()) & ((512 - 1) << 3)) >> 3) + 1))<<std::endl;/**/
         /*for(int x=0;x<img.cols ;x++){
            for(int y=0;y<img.rows;y++){
               cv::Vec3b c=img.at<cv::Vec3b>(cv::Point(x,y));

               std::cout<<"0:"<<+c[0]<<","<<+c[1]<<","<<+c[2]<<std::endl<<std::endl;
            }
         }/**/
         cv::Mat iTemp=img.reshape(1,1);
         iTemp.copyTo((*datos).row(i));
         /*cv::Mat xi = (*datos).row(i);
         if(img.isContinuous()) {
            img.reshape(1, 1).convertTo(xi, CV_32F, 1, 0);
         } else {
            img.clone().reshape(1, 1).convertTo(xi, CV_32F, 1, 0);
         }*/
         //setValor("imagen",img.reshape(1, 1).reshape(canales,size.height));

         //img.reshape(1,1).convertTo((*datos).row(i),CV_32F,1,0);
      }
         std::cout<<"Tengo Datos"<<std::endl;
      debug("Calculamos el PCA de las imágenes");
      cv::PCA pca(*datos,cv::Mat(), cv::PCA::DATA_AS_ROW, 10);
         std::cout<<"Calculo media"<<std::endl;
      cv::Mat media=pca.mean.reshape(canales,size.height);
         std::cout<<"Cojo eigenVectors"<<std::endl;
      cv::Mat eigenVectors=pca.eigenvectors;
      cv::Mat eigenFaceCV=pca.eigenvalues;
      std::vector<cv::Mat> eigenFaces;
      for(int i=0; i<10 && i<ficheros.size(); i++){

         eigenFaces.push_back(eigenVectors.row(i).reshape(canales,size.height));
      }
      cv::Mat iT2=media.reshape(canales,size.height);
      cv::cvtColor(media,iT2,CV_BGR2RGB);
      /*for(int x=0;x<iT2.cols ;x++){
         for(int y=0;y<iT2.rows;y++){
            cv::Vec3f c=iT2.at<cv::Vec3f>(cv::Point(x,y));

            std::cout<<"0:"<<c[0]<<","<<c[1]<<","<<c[2]<<std::endl<<std::endl;
         }
      }/**/
      cv::Mat iT3;
      //media.convertTo(iT3,CV_32);


      setValor("imagen", iT3);
	   return true;

   }

} /* namespace vision */

REGISTRAR_PLUGIN(vision::PCA);



