#ifndef EIGENFACES_H
#define EIGENFACES_H

#include "opencv2/core.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace std;

class eigenfaces{

    /* static void eigenfaces::leer_cvs(const string& nombreFichero, vector<Mat>& imagenes, vector<int>& etiquetas, char separador = ';') {
         std::ifstream fichero(nombreFichero.c_str(), ifstream::in);
         if (!fichero) {
             string error = "El fichero "+nombreFichero+" no es válido.";
             CV_Error(CV_StsBadArg, error);
         }
         string linea, ruta, claseEtiqueta;
         while (getline(fichero, linea)) {
             stringstream lineas(linea);
             getline(lineas, ruta, separador);
             getline(lineas, claseEtiqueta);
             if(!ruta.empty() && !claseEtiqueta.empty()) {
                 imagenes.push_back(imread(ruta, 0));
                 etiquetas.push_back(atoi(claseEtiqueta.c_str()));
             }
         }
     }
     static Mat eigenfaces::normalizar(InputArray src){
         Mat img = src.getMat();
         Mat salida;
         switch(img.channels()) {
             case 1:
                 cv::normalize(src, salida, 0, 255, NORM_MINMAX, CV_8UC1);
                 break;
             case 3:
                 cv::normalize(src, salida, 0, 255, NORM_MINMAX, CV_8UC3);
                 break;
             default:
                 img.copyTo(salida);
                 break;
         }
         return salida;
     }

     static void eigenfaces::evaluarImagen(const cv::Mat &img){
         vector<Mat> images;
         vector<int> labels;
         leer_cvs("bd/imagenes.ext", images, labels);

         int height = images[0].rows;

         Ptr<BasicFaceRecognizer> model = createEigenFaceRecognizer();
         model->train(images, labels);
         int predictedLabel = model->predict(img);

         string result_message = format("Clase encontrada = %d", predictedLabel);

     }
     static void eigenfaces::cogerEigenface(const cv::Mat &img){
         Ptr<BasicFaceRecognizer> model = createEigenFaceRecognizer();
         Mat eigenvalues = model->getEigenValues();
         Mat W = model->getEigenVectors();
         Mat mean = model->getMean();

         imshow("media", norm_0_255(mean.reshape(1, img.rows)));

         for (int i = 0; i < min(10, W.cols); i++) {
             string msg = format("Eigenvalue #%d = %.5f", i, eigenvalues.at<double>(i));
             qDebug() << msg << endl;
             Mat ev = W.col(i).clone();
             Mat grayscale = norm_0_255(ev.reshape(1, height));
             Mat cgrayscale;
             applyColorMap(grayscale, cgrayscale, COLORMAP_JET);

             imshow(format("eigenface_%d", i), cgrayscale);

         }
         for(int num_components = min(W.cols, 10); num_components < min(W.cols, 300); num_components+=15) {
             Mat evs = Mat(W, Range::all(), Range(0, num_components));
             Mat projection = LDA::subspaceProject(evs, mean, images[0].reshape(1,1));
             Mat reconstruction = LDA::subspaceReconstruct(evs, mean, projection);
             reconstruction = norm_0_255(reconstruction.reshape(1, images[0].rows));
             imshow(format("reconstrucción de eigenface %d", num_components), reconstruction);

         }
     }/**/

    public:
        eigenfaces();



    private:


};

#endif // EIGENFACES_H
