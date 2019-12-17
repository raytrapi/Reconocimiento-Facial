cmake_minimum_required(VERSION 3.0.0)
find_package( OpenCV REQUIRED )


project(darknet LANGUAGES C CXX CUDA)
include_directories(
   src
   examples
   src/sys
   include
   pthreadW32/include  
   ${OpenCV_INCLUDE_DIRS}
   C:/Progra~1/NVIDIA~2/CUDA/v10.1/include
   
)
find_package(OpenMP REQUIRED) 

if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()



add_definitions(-DGPU)

if (OPENCV_FOUND)
#set (CMAKE_C_FLAGS "/DOPENCV")
#set (CMAKE_CXX_FLAGS "/DOPENCV")
endif()


#file(GLOB codigos src/*.c src/sys/*.c)
#add_library(darknet "STATIC"  ${codigos})
file(GLOB codigosLIB src/gemm.c src/utils.c src/cuda.c src/deconvolutional_layer.c 
	src/convolutional_layer.c src/list.c src/image.c src/activations.c src/im2col.c src/col2im.c src/blas.c src/crop_layer.c src/dropout_layer.c 
	src/maxpool_layer.c src/softmax_layer.c src/data.c src/matrix.c src/network.c src/connected_layer.c src/cost_layer.c 
	src/parser.c src/option_list.c src/detection_layer.c src/route_layer.c src/upsample_layer.c src/box.c src/normalization_layer.c 
	src/avgpool_layer.c src/layer.c src/local_layer.c src/shortcut_layer.c src/logistic_layer.c src/activation_layer.c src/rnn_layer.c 
	src/gru_layer.c src/crnn_layer.c src/demo.c src/batchnorm_layer.c src/region_layer.c src/reorg_layer.c src/tree.c src/lstm_layer.c 
	src/l2norm_layer.c src/yolo_layer.c src/cuda.h)
file(GLOB codigosLIBCUDA 
	src/convolutional_kernels.cu src/deconvolutional_kernels.cu src/activation_kernels.cu src/im2col_kernels.cu src/col2im_kernels.cu 
	src/blas_kernels.cu src/crop_layer_kernels.cu src/dropout_layer_kernels.cu src/maxpool_layer_kernels.cu src/avgpool_layer_kernels.cu
)


 
add_library(libdarknet "STATIC"  ${codigosLIB} ${codigosLIBCUDA})
                       
target_link_libraries( libdarknet ${OpenCV_LIBS} )
set_target_properties(libdarknet PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

file(GLOB codigosEXE examples/captcha.c examples/lsd.c examples/super.c examples/art.c examples/tag.c examples/cifar.c examples/go.c examples/rnn.c 
	examples/segmenter.c examples/regressor.c examples/classifier.c examples/coco.c examples/yolo.c examples/detector.c examples/nightmare.c 
	examples/darknet.c )
add_executable(darknet examples/darknet.c ${codigosEXE})
if(WIN32)
	target_link_libraries( darknet libdarknet  wsock32 ws2_32  ${CMAKE_HOME_DIRECTORY}/herramientas/yolo/pthreadW32/lib/x64/pthreadVC2.lib 
	C:/Desarrollo/pruebas/yolo/pthreadW32/lib/x64/pthreadVC2.lib 
	C:/Progra~1/NVIDIA~2/CUDA/v10.1/lib/x64/cuda.lib 
	C:/Progra~1/NVIDIA~2/CUDA/v10.1/lib/x64/cudart.lib 
	C:/Progra~1/NVIDIA~2/CUDA/v10.1/lib/x64/cublas.lib 
	C:/Progra~1/NVIDIA~2/CUDA/v10.1/lib/x64/curand.lib)
elseif(UNIX)
	target_link_libraries( darknet libdarknet.so)
endif()
target_link_libraries( darknet ${OpenCV_LIBS})
if(WIN32)
add_custom_command(
    TARGET darknet POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
       "${CMAKE_HOME_DIRECTORY}/herramientas/yolo/pthreadW32/dll/x64/pthreadVC2.dll"
        ${CMAKE_CURRENT_BINARY_DIR}/../../../bin
)

file(GLOB CFG ${CMAKE_HOME_DIRECTORY}/herramientas/yolo/recursos/cfg/*.*)
make_directory(${CMAKE_CURRENT_BINARY_DIR}/../../../bin/cfg)
add_custom_command(
    TARGET darknet POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
       ${CFG}
        ${CMAKE_CURRENT_BINARY_DIR}/../../../bin/cfg
)
file(GLOB DATA recursos/data/*.*)
make_directory(${CMAKE_CURRENT_BINARY_DIR}/../../bin/data)
make_directory(${CMAKE_CURRENT_BINARY_DIR}/../../../bin/data/labels)
add_custom_command(
    TARGET darknet POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
       ${DATA}
        ${CMAKE_CURRENT_BINARY_DIR}/../../bin/data
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		recursos/data/ 
		${CMAKE_CURRENT_BINARY_DIR}/../../bin/data
)
endif()
