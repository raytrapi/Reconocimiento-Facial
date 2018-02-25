#include <iostream>

#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#ifdef WIN32
#include <windows.h>
#endif
#include "dialogoRecortador.h"
//#include "inicializar.h"
QCoreApplication* createApplication(int &argc, char *argv[]){
	QCoreApplication::setOrganizationName("ray");
	QCoreApplication::setOrganizationDomain("programacionextrema.es");
	QCoreApplication::setApplicationName(QString::fromLatin1("Recortador de imágenes"));
    for (int i = 1; i < argc; ++i)
        if (!qstrcmp(argv[i], "-no-gui"))
            return new QCoreApplication(argc, argv);
    return new QApplication(argc, argv);
}
#ifdef WIN32
void Stealth(bool ocultar){
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth,(ocultar?0:1));
}
#endif

int main(int argc, char* argv[]){
#ifdef WIN32
    //SetConsoleOutputCP(65001);
#endif
	int res=0;
	/*if(argc>1){
		//std::cout << argv[1] << " " <<  boost::filesystem::file_size(argv[1]) << '\n';

		try{
			boost::filesystem::path p(argv[1]);  // avoid repeated path construction below
		  if (boost::filesystem::exists(p))    // does path p actually exist?
		  {
			if (boost::filesystem::is_regular_file(p))        // is path p a regular file?
				std::cout << p << " size is " << boost::filesystem::file_size(p) << '\n';

			else if (boost::filesystem::is_directory(p))      // is path p a directory?
				std::cout << p << " is a directory\n";

			else
				std:: cout << p << " exists, but is not a regular file or directory\n";
		  }
		  else
			  std::cout << p << " does not exist\n";

		}catch(const boost::filesystem::filesystem_error& e){
			 if(e.code() == boost::system::errc::permission_denied)
			           std::cout << "Search permission is denied for one of the directories "
			                     << "in the path prefix of " << argv[1] << "\n";
			       else
			           std::cout << "is_directory(" << argv[1] << ") failed with "
			                     << e.code().message() << '\n';

		}
	}
	return 0;/**/
	//vision::inicializar();
	QScopedPointer<QCoreApplication> app(createApplication(argc, argv));

    //QMainWindow w;
    DialogoRecortador * dialog = new DialogoRecortador();
    dialog->show();


	#ifdef WIN32

		//Stealth(true);
	#endif

	res=app->exec();

	#ifdef WIN32
		//Stealth(false);
	#endif



    return res;
}



