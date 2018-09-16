cmake_minimum_required(VERSION 3.0.0)

project(vision2)
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


option(VISION "Habilitar construcción de visión" ON)
option(HERRAMIENTAS "Habilitar construcción de herramientas" ON)
option(YOLO "Habilitamos la librería YOLO" ON) 
option(RECORTADOR "Habilitamos la aplicación de recortes" ON)
option(DETECTOPENCV "Habilitamos la aplicación de detección con OPENCV" OFF)
add_subdirectory(utilidades) 
if(VISION)
    add_subdirectory(vision)
endif()
if(HERRAMIENTAS)
    add_subdirectory(herramientas)
endif()

