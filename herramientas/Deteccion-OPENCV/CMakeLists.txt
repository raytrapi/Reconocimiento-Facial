cmake_minimum_required(VERSION 3.0.0)
project(deteccionOpenCV)




find_package( OpenCV REQUIRED )
set(CMAKE_AUTOMOC ON)
find_package(Qt5Core REQUIRED)
find_package( Qt5Widgets )

set(Boost_USE_STATIC_LIBS        OFF)  
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.66.0 COMPONENTS filesystem system  REQUIRED)

include_directories(
   src
   ${OpenCV_INCLUDE_DIRS}
   ${Qt5Core_INCLUDE_DIRS}
   ${Boost_INCLUDE_DIR}
)
#qt5_add_resources()

if (WIN32)
  add_definitions( -DBOOST_ALL_NO_LIB )
  add_definitions( -DBOOST_ALL_DYN_LINK )
endif()

add_definitions(${Qt5Core_DEFINITIONS})
file(GLOB OTROSCPP src/eigenface/*.cpp src/GUI/*.cpp src/v&j/*.cpp)
add_executable(deteccionOpenCV src/main.cpp src/img.cpp src/mainwindow.cpp ${OTROSCPP})
target_link_libraries( deteccionOpenCV ${OpenCV_LIBS} ${Qt5Widgets_LIBRARIES} ${Boost_LIBRARIES})


set(destino ${CMAKE_CURRENT_BINARY_DIR}/../../bin)
file(GLOB CLASIFICADORES  recursos/clasificadores/*)
make_directory(${destino}/clasificadores)
file(GLOB IMAGENES  recursos/imagenes/*)
make_directory(${destino}/imagenes)
add_custom_command(
    TARGET deteccionOpenCV POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Core>
        $<TARGET_FILE:Qt5::Widgets>
        $<TARGET_FILE:Qt5::Gui>
        "${OpenCV_INSTALL_PATH}/x64/vc14/bin/opencv_world331.dll"
        "${OpenCV_INSTALL_PATH}/x64/vc14/bin/opencv_world331d.dll"
        "${Boost_LIBRARY_DIR_RELEASE}/boost_filesystem-vc141-mt-x64-1_66.dll"
        "${Boost_LIBRARY_DIR_RELEASE}/boost_system-vc141-mt-x64-1_66.dll"
        "${Boost_LIBRARY_DIR_RELEASE}/boost_regex-vc141-mt-x64-1_66.dll"
        "${Boost_LIBRARY_DIR_RELEASE}/boost_thread-vc141-mt-x64-1_66.dll"
        "${Boost_LIBRARY_DIR_RELEASE}/boost_chrono-vc141-mt-x64-1_66.dll"
        ${destino}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    	${CLASIFICADORES}
    	${destino}/clasificadores
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    	${IMAGENES}
    	${destino}/imagenes
    
)

#CopiarRecursos(recursos, ${destino}/recursos) 