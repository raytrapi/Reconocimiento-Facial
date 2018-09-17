cmake_minimum_required(VERSION 3.0.0)
project(utils)

include_directories(
   src
)



file(GLOB CODIGOS src/*.cpp)
add_library(utils "SHARED" ${CODIGOS})
set_target_properties(utils PROPERTIES
   COMPILE_DEFINITIONS UTILS
    PUBLIC_HEADER utils.h )