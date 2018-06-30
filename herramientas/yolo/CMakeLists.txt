cmake_minimum_required(VERSION 3.0.0)

project(darknet)
include_directories(
   src
   src/sys
   include
   pthreadW32/include  
)

#file(GLOB codigos src/*.c src/sys/*.c)
#add_library(darknet "STATIC"  ${codigos})
file(GLOB codigosLIB src/gemm.c src/utils.c src/cuda.c src/deconvolutional_layer.c 
	src/convolutional_layer.c src/list.c src/image.c src/activations.c src/im2col.c src/col2im.c src/blas.c src/crop_layer.c src/dropout_layer.c 
	src/maxpool_layer.c src/softmax_layer.c src/data.c src/matrix.c src/network.c src/connected_layer.c src/cost_layer.c 
	src/parser.c src/option_list.c src/detection_layer.c src/route_layer.c src/upsample_layer.c src/box.c src/normalization_layer.c 
	src/avgpool_layer.c src/layer.c src/local_layer.c src/shortcut_layer.c src/logistic_layer.c src/activation_layer.c src/rnn_layer.c 
	src/gru_layer.c src/crnn_layer.c src/demo.c src/batchnorm_layer.c src/region_layer.c src/reorg_layer.c src/tree.c src/lstm_layer.c 
	src/l2norm_layer.c src/yolo_layer.c src/sys/*.c)
add_library(darknet "STATIC"  ${codigosLIB})