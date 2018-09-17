#set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/bin)
find_package( OpenCV REQUIRED )
find_package(Qt5Core REQUIRED)
include_directories(
   src
   ${OpenCV_INCLUDE_DIRS}
   ${Qt5Core_INCLUDE_DIRS}

)
include_directories(../../herramientas/CLM-framework-master/lib/local/CLM/include)
include_directories(../../herramientas/CLM-framework-master/lib/local/FaceAnalyser/include)
include_directories(../../herramientas/herramientas/Deteccion-OPENCV/src/v&j/)

file(GLOB codigos src/*.cpp)
add_library(cnn "SHARED" ${codigos} ../../herramientas/Deteccion-OPENCV/src/v&j/viola_jones.cpp)
if(WIN32)
	target_link_libraries( cnn ${OpenCV_LIBS} plugin)
elseif(UNIX)
	target_link_libraries( cnn ${OpenCV_LIBS} libplugin.so)
endif()
target_link_libraries( cnn ${CONAN_LIBS})
target_link_libraries( cnn dlib::dlib)
target_link_libraries(cnn CLM)
target_link_libraries(cnn FaceAnalyser)
target_link_libraries(cnn utils)
target_link_libraries(cnn ${Qt5Widgets_LIBRARIES}) 
file(GLOB CLASIFICADORES  ../../herramientas/Deteccion-OPENCV/recursos/clasificadores/*)
set(destino ${CMAKE_CURRENT_BINARY_DIR}/../../bin)
make_directory(${destino}/clasificadores)
make_directory(${destino}/model)
add_custom_command(
    TARGET cnn POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_BINARY_DIR}/../../../bin/cnn.dll
        ${CMAKE_SOURCE_DIR}/dll
     COMMAND ${CMAKE_COMMAND} -E copy_if_different
         ${CLASIFICADORES}
         ${destino}/clasificadores
     COMMAND ${CMAKE_COMMAND} -E copy_directory
         ../../herramientas/CLM-framework-master/lib/local/CLM/model 
         ${destino}/model
)
