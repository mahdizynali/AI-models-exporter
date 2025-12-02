#ifndef CONVERT_HPP
#define CONVERT_HPP

// ============================================

#if defined(ENGINE_ONNX_TO_TRT)
    #include <NvInfer.h>
    #include <NvOnnxParser.h>

#elif defined(ENGINE_TRT_TO_ONNX)
// #include <onnx/onnx_pb.h>

#else
    #include <NvInfer.h>
    #include <NvOnnxParser.h>
// #include <onnx/onnx_pb.h>
#endif

// ============================================

#include <iostream>
#include "dType.h"

class Converter{
    private:
        engine eng_allocator_; 
    public:
        ~Converter();
        explicit Converter(engine eng);
};

#endif // CONVERT_HPP