@echo off
echo "pre"
rem del /S /Q ..\build\*.*

rem @set QT5_PATH=E:\Program Files\QT\5.7\msvc2015_64
rem @set QT5_BIN_DIR=%QT5_PATH%\bin

rem @set OpenCV_PATH=E:\Vision\opencv\opencv3.3.1\build
rem @set OpenCV_BIN_DIR=%OpenCV_PATH%\x64\vc14\bin

rem @set BOOST_PATH=C:\boost\include\boost-1_66
rem @set BOOST_LIBRARY_DIRS=C:\boost\lib

rem set PATH=%OpenCV_BIN_DIR%;%QT5_BIN_DIR%;%BOOST_LIBRARY_DIRS%;%PATH%

rem conan install ..
rem cmake -G "NMake Makefiles"^
rem    -DCMAKE_BUILD_TYPE=Release^
rem    -DCMAKE_INSTALL_PREFIX=../install^
rem    -DOpenCV_DIR=%OpenCV_PATH%\x64\vc14\lib^
rem    -DBOOST_ROOT:STRING="%BOOST_PATH%"^
rem    -DBOOST_LIBRARYDIR:STRING="%BOOST_LIBRARY_DIRS%"^
rem    -DBoost_ADDITIONAL_VERSIONS=1.66.0^
rem    ..