cmake_minimum_required(VERSION 3.0.0)

project(vision2)
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


option(VISION "Habilitar construcción de visión" ON)
option(HERRAMIENTAS "Habilitar construcción de herramientas" OFF)
option(RECORTADOR "Habilitamos la aplicación de recortes" OFF)
option(DETECTOPENCV "Habilitamos la aplicación de detección con OPENCV" OFF)
if(VISION)
    add_subdirectory(vision)
endif()
if(HERRAMIENTAS)
    add_subdirectory(herramientas)
endif()

