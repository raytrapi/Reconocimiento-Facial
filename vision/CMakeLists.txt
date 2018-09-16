cmake_minimum_required(VERSION 3.0.0)

project(vision)


#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup()

find_package( OpenCV REQUIRED )
set(CMAKE_AUTOMOC ON)
find_package(Qt5Core REQUIRED)
find_package( Qt5Widgets )

#set(Boost_USE_STATIC_LIBS        OFF)  
#set(Boost_USE_MULTITHREADED      ON)
#set(Boost_USE_STATIC_RUNTIME    OFF)
#find_package(Boost 1.66.0 COMPONENTS filesystem system regex thread REQUIRED)

include_directories(
   src
   src/dll
   ${OpenCV_INCLUDE_DIRS}
   ${Qt5Core_INCLUDE_DIRS}
#   ${Boost_INCLUDE_DIR}
   
)

#if (WIN32)
#  # disable autolinking in boost
#  add_definitions( -DBOOST_ALL_NO_LIB )
#
#  # force all boost libraries to dynamic link (we already disabled
#  # autolinking, so I don't know why we need this, but we do!)
#  #add_definitions( -DBOOST_ALL_DYN_LINK )
#  #ADD_DEFINITIONS( "-DHAS_BOOST" )
#endif()
file(GLOB OTROS src/utiles/*.cpp)
add_definitions(${Qt5Core_DEFINITIONS})
add_executable(vision src/vision.cpp src/inicializar.cpp  src/mainDialog.cpp )
#target_link_libraries( vision ${OpenCV_LIBS} ${Qt5Widgets_LIBRARIES} ${Boost_LIBRARIES} ${CONAN_LIBS})
target_link_libraries( vision ${OpenCV_LIBS} ${Qt5Widgets_LIBRARIES})
target_link_libraries( vision  ${CONAN_LIBS})
target_link_libraries( vision  visor)
if(WIN32)
	target_link_libraries( vision plugin utilidades)
elseif(UNIX)
	target_link_libraries( vision libplugin.so libutilidades.so)
endif()

add_library(utilidades "SHARED"  src/utiles/log.cpp src/utiles/config.cpp)
set_target_properties(utilidades PROPERTIES
	COMPILE_DEFINITIONS UTILIDADES_EXPORTS
    PUBLIC_HEADER utilidades.h )
#target_link_libraries( utilidades  ${Boost_LIBRARIES})
target_link_libraries( utilidades  ${CONAN_LIBS})

add_library(plugin "SHARED"  src/plugin.cpp src/algoritmoPlugin.cpp)
set_target_properties(plugin PROPERTIES
	COMPILE_DEFINITIONS PLUGIN_EXPORTS
    PUBLIC_HEADER src/plugin.h )

target_link_libraries( plugin  ${OpenCV_LIBS} ${CONAN_LIBS})

add_subdirectory( ${CMAKE_HOME_DIRECTORY}/algoritmos algoritmos)



file(GLOB EXTRAS extra/*.*)
add_custom_command(
    TARGET vision POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Core>
        $<TARGET_FILE:Qt5::Widgets>
        $<TARGET_FILE:Qt5::Gui>
        "${OpenCV_INSTALL_PATH}/x64/vc14/bin/opencv_world331.dll"
        "${OpenCV_INSTALL_PATH}/x64/vc14/bin/opencv_world331d.dll"
        #"${Boost_LIBRARY_DIR_RELEASE}/boost_filesystem-vc141-mt-x64-1_66.dll"
        #"${Boost_LIBRARY_DIR_RELEASE}/boost_system-vc141-mt-x64-1_66.dll"
        #"${Boost_LIBRARY_DIR_RELEASE}/boost_regex-vc141-mt-x64-1_66.dll"
        #"${Boost_LIBRARY_DIR_RELEASE}/boost_thread-vc141-mt-x64-1_66.dll"
        #"${Boost_LIBRARY_DIR_RELEASE}/boost_chrono-vc141-mt-x64-1_66.dll"
        #"${Boost_LIBRARY_DIR_RELEASE}/boost_filesystem-vc141-mt-gd-x64-1_66.dll"
        #"${Boost_LIBRARY_DIR_RELEASE}/boost_system-vc141-mt-gd-x64-1_66.dll"
        #"${Boost_LIBRARY_DIR_RELEASE}/boost_regex-vc141-mt-gd-x64-1_66.dll"
        ${EXTRAS}
        ${CMAKE_CURRENT_BINARY_DIR}/../bin
)

install(TARGETS vision DESTINATION .
	LIBRARY DESTINATION .
	PUBLIC_HEADER DESTINATION include
    )
install(FILES ${OpenCV_INSTALL_PATH}/x64/vc14/bin/opencv_world331.dll DESTINATION .)
install(FILES ${libs_files} DESTINATION .)