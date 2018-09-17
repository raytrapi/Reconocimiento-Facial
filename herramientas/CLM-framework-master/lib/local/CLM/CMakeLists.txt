cmake_minimum_required(VERSION 3.0.0)
find_package( OpenCV REQUIRED )

SET(SOURCE
    src/CCNF_patch_expert.cpp
	src/CLM.cpp
    src/CLM_utils.cpp
	src/CLMTracker.cpp
    src/DetectionValidator.cpp
	src/Patch_experts.cpp
	src/PAW.cpp
    src/PDM.cpp
	src/SVR_patch_expert.cpp
	src/stdafx.cpp
	
)

SET(HEADERS
    include/CCNF_patch_expert.h
	include/CLM.h
    include/CLM_utils.h
	include/CLMParameters.h
	include/CLMTracker.h
    include/DetectionValidator.h
	include/Patch_experts.h	
    include/PAW.h
	include/PDM.h
	include/SVR_patch_expert.h		
	include/stdafx.h
)

include_directories(./include)
include_directories(${CLM_SOURCE_DIR}/include)
include_directories(${OpenCV_INCLUDE_DIRS})

add_library( CLM ${SOURCE} ${HEADERS}   )

target_link_libraries(CLM ${CONAN_LIBS})
target_link_libraries(CLM ${OpenCV_LIBS})
target_link_libraries(CLM dlib::dlib)