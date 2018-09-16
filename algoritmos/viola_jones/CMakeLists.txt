find_package( OpenCV REQUIRED )
find_package(Qt5Core REQUIRED)
include_directories(
   src
   ${OpenCV_INCLUDE_DIRS}
   ${Qt5Core_INCLUDE_DIRS}
   ../../src
)
include_directories(../../herramientas/herramientas/Deteccion-OPENCV/src/v&j/)

add_library(viola_jones "SHARED" src/viola-jones.cpp ../../herramientas/Deteccion-OPENCV/src/v&j/viola_jones.cpp)
if(WIN32)
	target_link_libraries( viola_jones ${OpenCV_LIBS} plugin)
elseif(UNIX)
	target_link_libraries( viola_jones ${OpenCV_LIBS} libplugin.so)
endif()
target_link_libraries(viola_jones ${CONAN_LIBS})
target_link_libraries(viola_jones utils)
target_link_libraries(viola_jones ${Qt5Widgets_LIBRARIES}) 










file(GLOB CLASIFICADORES  ../../herramientas/Deteccion-OPENCV/recursos/clasificadores/*)
set(destino ${CMAKE_CURRENT_BINARY_DIR}/../../bin)
make_directory(${destino}/clasificadores)
add_custom_command(
    TARGET viola_jones POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_BINARY_DIR}/../../../bin/viola_jones.dll
        ${CMAKE_SOURCE_DIR}/dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
         ${CLASIFICADORES}
         ${destino}/clasificadores
)