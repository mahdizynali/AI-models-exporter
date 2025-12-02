#pragma once

enum struct engine {
    ONNX_to_TRT = 0, // use for converting onnx models into tensorrt
    TRT_to_ONNX = 1, // use for converting tensorrt models into onnx
}; 