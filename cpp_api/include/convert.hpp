#ifndef CONVERT_HPP
#define CONVERT_HPP

// ============================================

#if defined(ALL_ENGINES)
    // #include <NvInfer.h>
    // #include <NvOnnxParser.h>
// #include <onnx/onnx_pb.h>

#elif defined(ENGINE_TRT_TO_ONNX)
// #include <onnx/onnx_pb.h>

#elif defined(ENGINE_ONNX_TO_TRT)
    // #include <NvInfer.h>
    // #include <NvOnnxParser.h>
#endif

// ============================================

#include <iostream>
#include "dType.h"

class Converter{
    private:
        engine eng_allocator_;
        std::string input_model_path_;
        std::string output_model_path_;
    public:
        void run();
        ~Converter();
        inline int onnx_To_tensorrt();
        inline int tensorrt_To_onnx();
        explicit Converter(engine, std::string, std::string);
};

#endif // CONVERT_HPP