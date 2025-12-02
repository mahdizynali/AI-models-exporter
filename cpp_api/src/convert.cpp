#include "convert.hpp"

Converter::Converter(engine eng) : eng_allocator_(eng) {

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

void Converter::run() {
    switch (eng_allocator_) {
    case engine::ONNX_to_TENSORRT:
        
        break;
    case engine::TENSORRT_to_ONNX:
        
        break;
    }
}
