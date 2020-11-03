## Build

```bash
cd vehicle_detection/MNN
```

* Replace  **libMNN.so** under ./mnn/lib with your compiled libMNN.so and then :

```bash
#指定cuda路径,否则报路径错误
mkdir build && cd build && cmake -D CUDA_TOOLKIT_ROOT_DIR=/usr/local/cuda-9.0 ..
#这步本机编译报错,其解决方法:
make -j$(nproc)
```

