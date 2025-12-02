#ifndef CONVERT_HPP
#define CONVERT_HPP

#include "dType.h"
#include <fstream>
#include <iostream>

// ============================================

#if defined(ALL_ENGINES)
    #include <NvInfer.h>
    #include <NvOnnxParser.h>
    #include <cuda_runtime_api.h>
    using namespace nvinfer1;

    #ifndef NV_TENSORRT_MAJOR
    #  define NV_TENSORRT_MAJOR 0
    #endif

    #if NV_TENSORRT_MAJOR >= 8
    #  define TRT_NOEXCEPT noexcept
    #  define TRT_CONST_ENQUEUE const
    #else
    #  define TRT_NOEXCEPT
    #  define TRT_CONST_ENQUEUE
    #endif
    
    class TRT_Logger : public nvinfer1::ILogger {
        void log(Severity severity, const char* msg) noexcept override {
            if (severity <= Severity::kWARNING)
                std::cout << msg << std::endl;
        }
    };

    extern TRT_Logger trt_logger_;


#elif defined(ENGINE_TRT_TO_ONNX)
// #include <onnx/onnx_pb.h>

#elif defined(ENGINE_ONNX_TO_TRT)
    #include <NvInfer.h>
    #include <NvOnnxParser.h>
    #include <cuda_runtime_api.h>
    using namespace nvinfer1;

    #ifndef NV_TENSORRT_MAJOR
    #  define NV_TENSORRT_MAJOR 0
    #endif

    #if NV_TENSORRT_MAJOR >= 8
    #  define TRT_NOEXCEPT noexcept
    #  define TRT_CONST_ENQUEUE const
    #else
    #  define TRT_NOEXCEPT
    #  define TRT_CONST_ENQUEUE
    #endif

    class TRT_Logger : public nvinfer1::ILogger {
        void log(Severity severity, const char* msg) noexcept override {
            if (severity <= Severity::kWARNING)
                std::cout << msg << std::endl;
        }
    };

    extern TRT_Logger trt_logger_;

#endif

// ============================================

class Converter{
    private:
        EngineType eng_allocator_;
        std::string input_model_path_;
        std::string output_model_path_;

        #if defined(ALL_ENGINES) || defined(ENGINE_TRT_TO_ONNX)
            IRuntime* TRT_runtime_ = nullptr;
            ICudaEngine* Cuda_engine_ = nullptr;
            IExecutionContext* TRT_context = nullptr;
        #endif

    public:
        void run();
        ~Converter();
        inline int onnx_To_tensorrt();
        inline int tensorrt_To_onnx();
        explicit Converter(EngineType, std::string, std::string);
};

#endif // CONVERT_HPP