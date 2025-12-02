cmake_minimum_required(VERSION 3.12)

project(AIModelsExporter
    VERSION 0.1.0
    LANGUAGES CXX
)

# ==============================

option(ALL_ENGINES            "Enable all exporting engines" ON)
option(ENGINE_ONNX_TO_TRT     "Enable only ONNX -> TensorRT engine" OFF)
option(ENGINE_TRT_TO_ONNX     "Enable only TensorRT -> ONNX engine" OFF)

# ==============================

set(SRC_FILES
    main.cpp
    src/convert.cpp
)

add_executable(export ${SRC_FILES})

# ==============================

target_compile_features(export PRIVATE cxx_std_17)

# ==============================

target_include_directories(export
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ==============================
if (ALL_ENGINES)
    target_compile_definitions(export PRIVATE ALL_ENGINES)
elseif (ENGINE_ONNX_TO_TRT)
    target_compile_definitions(export PRIVATE ENGINE_ONNX_TO_TRT)
elseif (ENGINE_TRT_TO_ONNX)
    target_compile_definitions(export PRIVATE ENGINE_TRT_TO_ONNX)
endif()

# ==============================
# TensorRT / ONNX libraries (optional, placeholder)
# ==============================
# If you have TensorRT installed, you can add something like:
#
# find_path(TENSORRT_INCLUDE_DIR NvInfer.h HINTS /usr/include /usr/local/include)
# find_library(TENSORRT_LIB nvinfer HINTS /usr/lib /usr/local/lib)
# find_library(TENSORRT_PARSER_LIB nvonnxparser HINTS /usr/lib /usr/local/lib)
#
# target_include_directories(export PRIVATE ${TENSORRT_INCLUDE_DIR})
# target_link_libraries(export PRIVATE ${TENSORRT_LIB} ${TENSORRT_PARSER_LIB})
#
# Adjust paths/names as needed for your system.
