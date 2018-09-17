#set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/bin)
find_package( OpenCV REQUIRED )
find_package(Qt5Core REQUIRED)
include_directories(
   src
   ${OpenCV_INCLUDE_DIRS}
   ${Qt5Core_INCLUDE_DIRS}
)


file(GLOB codigos src/*.cpp)
add_library(pca "SHARED" ${codigos} )
if(WIN32)
	target_link_libraries( pca ${OpenCV_LIBS} plugin)
elseif(UNIX)
	target_link_libraries( pca ${OpenCV_LIBS} libplugin.so)
endif()
target_link_libraries(pca ${Qt5Widgets_LIBRARIES})
#target_link_libraries(pca ${CONAN_LIBS})
#target_link_libraries(pca utils)




  
set(destino ${CMAKE_CURRENT_BINARY_DIR}/../../bin)
add_custom_command(
    TARGET pca POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_BINARY_DIR}/../../../bin/pca.dll
        ${CMAKE_SOURCE_DIR}/dll
)
