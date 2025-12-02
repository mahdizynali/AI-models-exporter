#include "convert.hpp"

Converter::Converter(engine eng, std::string inM, std::string outM) : eng_allocator_(eng), 
                                                                      input_model_path_(inM), 
                                                                      output_model_path_(outM) {

    #if defined(ENGINE_ONNX_TO_TRT)
        if (eng_allocator_ != engine::ONNX_to_TENSORRT) {
            std::cerr << "[Error] : " << "binary only supports ONNX -> TRT\n";
            std::cerr << "[How to Fix] : " << "Change Engine type while compiling or do not declare!\n";
        }
    #elif defined(ENGINE_TRT_TO_ONNX)
        if (eng_allocator_ != engine::TENSORRT_to_ONNX) {
            std::cerr << "[Error] : " << "binary only supports TRT -> ONNX\n";
            std::cerr << "[How to Fix] : " << "Change Engine type while compiling or do not declare!\n";
        }
    #endif
}

Converter::~Converter() = default;

#if defined(ALL_ENGINES) || defined(ENGINE_ONNX_TO_TRT)
    int Converter::onnx_To_tensorrt() {
        std::cout << "[Info] Converting ONNX to TensorRT\n";
        return 0;
    }
#endif

#if defined(ALL_ENGINES) || defined(ENGINE_TRT_TO_ONNX)
    int Converter::tensorrt_To_onnx() {
        std::cout << "[Info] Converting TensorRT to ONNX\n";
        return 0;
    }
#endif

void Converter::run() {
    switch (eng_allocator_) {
    case engine::ONNX_to_TRT:
        onnx_To_tensorrt();
        break;
    case engine::TRT_to_ONNX:
        tensorrt_To_onnx();
        break;
    }
}
