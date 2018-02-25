#set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/bin)
find_package( OpenCV REQUIRED )
include_directories(
   src
   ${OpenCV_INCLUDE_DIRS}
   ../../src
)
#link_directories(${CMAKE_BINARY_DIR}/bin/)

add_library(viola_jones "SHARED" src/viola-jones.cpp)
if(WIN32)
	target_link_libraries( viola_jones ${OpenCV_LIBS} plugin)
elseif(UNIX)
	target_link_libraries( viola_jones ${OpenCV_LIBS} libplugin.so)
endif()
add_custom_command(
    TARGET viola_jones POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_BINARY_DIR}/../../bin/viola_jones.dll
        ${CMAKE_SOURCE_DIR}/dll
)