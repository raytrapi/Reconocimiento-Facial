cmake_minimum_required (VERSION 2.6)
project (CLM_framework)


# CLM library (ordering matters)
add_subdirectory(lib/local/CLM)
add_subdirectory(lib/local/FaceAnalyser)
# executables
add_subdirectory(exe/SimpleCLMImg)
#add_subdirectory(exe/SimpleCLM)
#add_subdirectory(exe/MultiTrackCLM)
#add_subdirectory(exe/FeatureExtraction)
