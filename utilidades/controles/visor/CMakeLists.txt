cmake_minimum_required(VERSION 3.0.0)
project(visor)


find_package( OpenCV REQUIRED )
set(CMAKE_AUTOMOC ON)
find_package(Qt5Core REQUIRED)
find_package( Qt5Widgets )


include_directories(
   src
   ${OpenCV_INCLUDE_DIRS}
   ${Qt5Core_INCLUDE_DIRS}
)

add_definitions(${Qt5Core_DEFINITIONS})

file(GLOB CODIGOS src/*.cpp)
add_library(visor "SHARED" ${CODIGOS})
#target_link_libraries(visor ${OpenCV_LIBS} ${Qt5Widgets_LIBRARIES} ${Boost_LIBRARIES})
target_link_libraries(visor ${OpenCV_LIBS} ${Qt5Widgets_LIBRARIES})
target_link_libraries(visor ${CONAN_LIBS})
set_target_properties(visor PROPERTIES
   COMPILE_DEFINITIONS VISORWIDGET
    PUBLIC_HEADER visor.h ) 