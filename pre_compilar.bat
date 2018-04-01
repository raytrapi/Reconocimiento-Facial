@echo off
call "e:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64     
cd build
del /S /Q ..\build\*.*

@set QT5_PATH=E:\Program Files\QT\5.7\msvc2015_64
@set QT5_BIN_DIR=%QT5_PATH%\bin

@set OpenCV_PATH=E:\Vision\opencv\opencv3.3.1\build
@set OpenCV_BIN_DIR=%OpenCV_PATH%\x64\vc14\bin

@set BOOST_PATH=C:\boost\include\boost-1_66
@set BOOST_LIBRARY_DIRS=C:\boost\lib

set PATH=%OpenCV_BIN_DIR%;%QT5_BIN_DIR%;%BOOST_LIBRARY_DIRS%;%PATH%

conan install ..
cmake -G "NMake Makefiles"^
   -DCMAKE_BUILD_TYPE=Release^
   -DCMAKE_INSTALL_PREFIX=../install^
   -DOpenCV_DIR=%OpenCV_PATH%\x64\vc14\lib^
   -DBOOST_ROOT:STRING="%BOOST_PATH%"^
   -DBOOST_LIBRARYDIR:STRING="%BOOST_LIBRARY_DIRS%"^
   -DBoost_ADDITIONAL_VERSIONS=1.66.0^
   ..