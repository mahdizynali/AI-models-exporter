#include "convert.hpp"

#if defined(ALL_ENGINES) || defined(ENGINE_ONNX_TO_TRT)
    TRT_Logger trt_logger_;
#endif

Converter::Converter(EngineType eng, std::string inM, std::string outM) : eng_allocator_(eng), 
                                                                      input_model_path_(inM), 
                                                                      output_model_path_(outM) {

    #if defined(ENGINE_ONNX_TO_TRT)
        if (eng_allocator_ != EngineType::ONNX_to_TENSORRT) {
            std::cerr << "[Error] : " << "binary only supports ONNX -> TRT\n";
            std::cerr << "[How to Fix] : " << "Change Engine type while compiling or do not declare!\n";
        }
    #elif defined(ENGINE_TRT_TO_ONNX)
        if (eng_allocator_ != EngineType::TENSORRT_to_ONNX) {
            std::cerr << "[Error] : " << "binary only supports TRT -> ONNX\n";
            std::cerr << "[How to Fix] : " << "Change Engine type while compiling or do not declare!\n";
        }
    #endif
}

Converter::~Converter() = default;

#if defined(ALL_ENGINES) || defined(ENGINE_ONNX_TO_TRT)
    int Converter::onnx_To_tensorrt() {
        // if (model_path.find(".onnx") == std::string::npos) {
        //     std::cerr << "Failed To Find ONNX Model!\n";
        //     return false;
        // }

        IBuilder* builder = createInferBuilder(trt_logger_);

        #if NV_TENSORRT_MAJOR < 10
            const auto explicitBatch = 1U << static_cast<uint32_t>(NetworkDefinitionCreationFlag::kEXPLICIT_BATCH);
            INetworkDefinition* network = builder->createNetworkV2(explicitBatch);
        #else
            INetworkDefinition* network = builder->createNetworkV2(0);
        #endif

        IBuilderConfig* config = builder->createBuilderConfig();
        config->setFlag(BuilderFlag::kFP16);

        nvonnxparser::IParser* parser = nvonnxparser::createParser(*network, trt_logger_);
        bool parsed = parser->parseFromFile(input_model_path_.c_str(), static_cast<int>(ILogger::Severity::kINFO));
        if (!parsed) {
            std::cerr << "[Error] : " << "Engine Failed To Parse ONNX Model!\n";
        }

        IHostMemory* plan = builder->buildSerializedNetwork(*network, *config);

        TRT_runtime_ = createInferRuntime(trt_logger_);
        Cuda_engine_  = TRT_runtime_->deserializeCudaEngine(plan->data(), plan->size());
        TRT_context = Cuda_engine_->createExecutionContext();

        delete network;
        delete config;
        delete parser;
        delete plan;
        delete builder;

        size_t dotIndex = input_model_path_.find_last_of(".");
        if (dotIndex != std::string::npos)
            output_model_path_ = input_model_path_.substr(0, dotIndex) + ".engine";
        else
            return false;

        if (Cuda_engine_) {
            IHostMemory* data = Cuda_engine_->serialize();
            std::ofstream file(output_model_path_, std::ios::binary | std::ios::out);
            if (!file.is_open()) {
                std::cerr << "[Error] : " << "Saving .engine TRT model at " << output_model_path_ << " failed!\n";
                delete data;
                return false;
            }
            file.write(static_cast<const char*>(data->data()), data->size());
            file.close();
            delete data;
        }

        return true;
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
    case EngineType::ONNX_to_TRT:
        onnx_To_tensorrt();
        break;
    case EngineType::TRT_to_ONNX:
        tensorrt_To_onnx();
        break;
    }
}
