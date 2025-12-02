#pragma once

enum struct engine {
    ONNX_to_TRT, // use for converting onnx models into tensorrt
    TRT_to_ONNX, // use for converting tensorrt models into onnx
}; 