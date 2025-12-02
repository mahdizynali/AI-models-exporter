#include<string>
#include "dType.h"
#include <iostream>
#include "convert.hpp"

int main(int argc, char* argv[]) {

    if (argc < 4) {
        std::cerr << "Usage:\n"
                  << "  " << argv[0] << " <engine_type> <model_input_path> <output_path>\n\n"
                  << "Where <engine_type> is one of:\n"
                  << "  0 = ONNX_to_TRT\n"
                  << "  1 = TRT_to_ONNX\n";
        return 1;
    }

    int engine_type = 0;
    try {
        engine_type = std::stoi(argv[1]);
    } catch (const std::exception& e) {
        std::cerr << "[Error] engine_type must be an integer !\n";
        return 0;
    }

    switch (engine_type) {
        case 0 : {
            Converter cvt(EngineType::ONNX_to_TRT, argv[2], argv[3]);
            cvt.run();
            break;
        }
        case 1 : {
            Converter cvt(EngineType::TRT_to_ONNX, argv[2], argv[3]);
            cvt.run();
            break;
        }
        default: {
            std::cerr << "[Error] Unknown engine_type: " << engine_type << "\n"
                      << "Allowed values:\n"
                      << "  0 = ONNX_to_TRT\n"
                      << "  1 = TRT_to_ONNX\n";
            return 0;
        }
    }

    return 1;
}