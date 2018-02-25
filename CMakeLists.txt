cmake_minimum_required(VERSION 3.0.0)

project(vision2)
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


option(VISION "Habilitar construcción de visión" OFF)
option(HERRAMIENTAS "Habilitar construcción de herramientas" ON)
option(RECORTADOR "Habilitamos la aplicación de recortes" OFF)
option(DETECTOPENCV "Habilitamos la aplicación de detección con OPENCV" ON)
if(VISION)
    add_subdirectory(vision)
endif()
if(HERRAMIENTAS)
    add_subdirectory(herramientas)
endif()

