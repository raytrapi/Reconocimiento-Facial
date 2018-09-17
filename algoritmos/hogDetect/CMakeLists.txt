#set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/bin)
find_package( OpenCV REQUIRED )
include_directories(
   src
   ${OpenCV_INCLUDE_DIRS}
   #../../src
)
include_directories(../../herramientas/CLM-framework-master/lib/local/CLM/include)
include_directories(../../herramientas/CLM-framework-master/lib/local/FaceAnalyser/include)
#link_directories(${CMAKE_BINARY_DIR}/bin/)
file(GLOB codigos src/*.cpp)
add_library(hog_detect "SHARED" ${codigos})
if(WIN32)
	target_link_libraries( hog_detect ${OpenCV_LIBS} plugin)
elseif(UNIX)
	target_link_libraries( hog_detect ${OpenCV_LIBS} libplugin.so)
endif()
target_link_libraries( hog_detect dlib::dlib)
target_link_libraries(hog_detect CLM)
target_link_libraries(hog_detect FaceAnalyser)
add_custom_command(
    TARGET hog_detect POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_BINARY_DIR}/../../../bin/hog_detect.dll
        ${CMAKE_SOURCE_DIR}/dll
)