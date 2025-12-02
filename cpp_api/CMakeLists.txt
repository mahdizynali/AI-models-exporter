cmake_minimum_required(VERSION 3.12)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

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
    include(TRT/TensorRT)
    target_compile_definitions(export PRIVATE ALL_ENGINES)
    target_link_libraries(export PRIVATE ${ISF_TENSORRT_LIBRARIES})
    message(STATUS "Building with ALL_ENGINES support")
elseif (ENGINE_ONNX_TO_TRT)
    include(TRT/TensorRT)
    target_compile_definitions(export PRIVATE ENGINE_ONNX_TO_TRT)
    target_link_libraries(export PRIVATE ${ISF_TENSORRT_LIBRARIES})
    message(STATUS "Building with ENGINE_ONNX_TO_TRT support")
elseif (ENGINE_TRT_TO_ONNX)
    include(TRT/TensorRT)
    target_compile_definitions(export PRIVATE ENGINE_TRT_TO_ONNX)
    target_link_libraries(export PRIVATE ${ISF_TENSORRT_LIBRARIES})
    message(STATUS "Building with ENGINE_TRT_TO_ONNX support")
endif()