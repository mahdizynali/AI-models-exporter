### 🤯 Stop Struggling With AI Model DataTypes
If you would export or may convert a trained AI model type into other type of engine in order to inference on \
different backbone, this repo is you solution.

---

### 🚀 Current Features

- **ONNX → TensorRT**: Convert ONNX models to optimized TensorRT engines

### 📋 Prerequisites

- **CUDA Toolkit** (tested with CUDA 12.9)
- **TensorRT** (tested with TensorRT 10.8.0.43 but also support older versions)
- **CMake** ≥ 3.12
- **C++ Compiler** with C++17 support

---

### 🛠️ Build Instructions

### 1. Clone the Repository
```bash
git clone https://github.com/mahdizynali/AI-models-exporter.git
cd AI-models-exporter/cpp_api
```

### 2. Configure Build Directory
```bash
mkdir -p build && cd build
```

### 3. Build the Project
```bash
cmake -DTENSORRT_ROOT=/path/to/TensorRT ..
cmake --build .
```

### 🔧 Command Reference

```
./export <engine_type> <input_path> <output_path>
```

### Convert ONNX to TensorRT

```bash
./export 0 <input.onnx> <output_path_>
```

### Convert TensorRT to ONNX (Coming Soon)

```bash
./export 1 <input.engine> <output_path_>
```

### 📝 Build Options

Configure build with CMake options:

```bash
cmake -DALL_ENGINES=ON ..              # Enable all engines (default)
cmake -DENGINE_ONNX_TO_TRT=ON ..       # Enable only ONNX → TensorRT
cmake -DENGINE_TRT_TO_ONNX=ON ..       # Enable only TensorRT → ONNX
```

### ⚙️ Setting TensorRT Path Permanently

Add to your shell configuration file (`~/.bashrc` or `~/.zshrc`):

```bash
export TENSORRT_ROOT=/path/to/TensorRT
```

Then rebuild:
```bash
cmake .. && cmake --build .
```
