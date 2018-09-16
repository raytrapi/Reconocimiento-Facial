cmake_minimum_required(VERSION 3.0.0)

project(recortador)

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
add_executable(recortador src/main.cpp  src/dialogoRecortador.cpp src/recursos.rc)
target_link_libraries( recortador ${OpenCV_LIBS} ${Qt5Widgets_LIBRARIES})
target_link_libraries( recortador ${CONAN_LIBS})
target_link_libraries( recortador visor)

add_custom_command(
    TARGET recortador POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Core>
        $<TARGET_FILE:Qt5::Widgets>
        $<TARGET_FILE:Qt5::Gui>
        "${OpenCV_INSTALL_PATH}/x64/vc14/bin/opencv_world331.dll"
        "${OpenCV_INSTALL_PATH}/x64/vc14/bin/opencv_world331d.dll"
        ${CMAKE_CURRENT_BINARY_DIR}/../../bin
)
