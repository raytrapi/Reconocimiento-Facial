#set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/bin)
find_package( OpenCV REQUIRED )
include_directories(
   src
   ${OpenCV_INCLUDE_DIRS}
   ../../src
)
#link_directories(${CMAKE_BINARY_DIR}/bin/)

add_library(sobel "SHARED" src/sobel.cpp)
if(WIN32)
	target_link_libraries( sobel ${OpenCV_LIBS} plugin)
elseif(UNIX)
	target_link_libraries( sobel ${OpenCV_LIBS} libplugin.so)
endif()
add_custom_command(
    TARGET sobel POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_BINARY_DIR}/../../bin/sobel.dll
        ${CMAKE_SOURCE_DIR}/dll
)