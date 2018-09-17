cmake_minimum_required(VERSION 3.0.0)




find_package( OpenCV REQUIRED )
set(CMAKE_AUTOMOC ON)
include_directories(
   src
   ${OpenCV_INCLUDE_DIRS}
)
add_executable(hogTest src/hog.cpp)
target_link_libraries( hogTest ${OpenCV_LIBS} )
add_executable(hogFace src/peopledetect.cpp)
target_link_libraries( hogFace ${OpenCV_LIBS} )
