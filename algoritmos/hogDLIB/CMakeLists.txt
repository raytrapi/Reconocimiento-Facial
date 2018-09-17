#set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/bin)
find_package( OpenCV REQUIRED )
include_directories(
   src
   ${OpenCV_INCLUDE_DIRS}
   #../../src
)
#link_directories(${CMAKE_BINARY_DIR}/bin/)
file(GLOB codigos src/*.cpp)
add_library(hog_dlib "SHARED" ${codigos})
if(WIN32)
	target_link_libraries( hog_dlib ${OpenCV_LIBS} plugin)
elseif(UNIX)
	target_link_libraries( hog_dlib ${OpenCV_LIBS} libplugin.so)
endif()
target_link_libraries( hog_dlib dlib::dlib)
add_custom_command(
    TARGET hog_dlib POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_BINARY_DIR}/../../../bin/hog_dlib.dll
        ${CMAKE_SOURCE_DIR}/dll
)