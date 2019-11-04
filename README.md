# Arm NN

[caffe模型使用armnn](https://blog.csdn.net/liugan528/article/details/80430760)

[armnn_caffe](https://github.com/GarryLau/armnn_caffe)

[环境配置安装](https://blog.csdn.net/liugan528/article/details/80272763)

arm NN 的一个关键要求是 Compute Library，它包含一系列低级别机器学习和计算机视觉函数，面向 Arm Cortex-A CPU 和 Arm Mali GPU。我们的目标是让这个库汇集针对这些函数的一流优化，近期的优化已经展示了显著的性能提升 – 比同等 OpenCV 函数提高了 15 倍甚至更多。如果您是Cortex-M CPU 的用户，现在还有一个机器学习原语库 – 也就是近期发布的 CMSIS-NN。

CMSIS-NN 是一系列高效神经网络内核的集合，其开发目的是最大程度地提升神经网络的性能，减少神经网络在面向智能物联网边缘设备的 Arm Cortex-M 处理器内核上的内存占用。Arm开发这个库的目的是全力提升这些资源受限的 Cortex CPU 上的神经网络推理性能。借助基于 CMSIS-NN 内核的神经网络推理，运行时/吞吐量和能效可提升大约 5 倍。

> 主要优势

有了 Arm NN，开发人员可以即时获得一些关键优势：

更轻松地在嵌入式系统上运行 TensorFlow 和 Caffe

Compute Library 内部的一流优化函数，让用户轻松发挥底层平台的强大性能

无论面向何种内核类型，编程模式都是相同的

现有软件能够自动利用新硬件特性

与 Compute Library 相同，Arm NN 也是作为开源软件发布的，这意味着它能够相对简单地进行扩展，从而适应 Arm 合作伙伴的其他内核类型。

Arm NN is a key component of the [machine learning platform](https://mlplatform.org/), which is part of the [Linaro Machine Intelligence Initiative](https://www.linaro.org/news/linaro-announces-launch-of-machine-intelligence-initiative/). For more information on the machine learning platform and Arm NN, see: <https://mlplatform.org/>, also there is further Arm NN information available from <https://developer.arm.com/products/processors/machine-learning/arm-nn>

There is a getting started guide here using TensorFlow: <https://developer.arm.com/technologies/machine-learning-on-arm/developer-material/how-to-guides/configuring-the-arm-nn-sdk-build-environment-for-tensorflow>

There is a getting started guide here using TensorFlow Lite: <https://developer.arm.com/technologies/machine-learning-on-arm/developer-material/how-to-guides/configuring-the-arm-nn-sdk-build-environment-for-tensorflow-lite>

There is a getting started guide here using Caffe: <https://developer.arm.com/technologies/machine-learning-on-arm/developer-material/how-to-guides/configuring-the-arm-nn-sdk-build-environment-for-caffe>

There is a getting started guide here using ONNX: <https://developer.arm.com/technologies/machine-learning-on-arm/developer-material/how-to-guides/configuring-the-arm-nn-sdk-build-environment-for-onnx>

There is a guide for backend development: [Backend development guide](src/backends/README.md)

### Build Instructions

Arm tests the build system of Arm NN with the following build environments:

* Android NDK: [How to use Android NDK to build Arm NN](BuildGuideAndroidNDK.md)
* Cross compilation from x86_64 Ubuntu to arm64 Linux: [Arm NN Cross Compilation](BuildGuideCrossCompilation.md)
* Native compilation under aarch64 Debian 9

Arm NN is written using portable C++14 and the build system uses [CMake](https://cmake.org/), therefore it is possible to build for a wide variety of target platforms, from a wide variety of host environments.

The armnn/tests directory contains tests used during Arm NN development. Many of them depend on third-party IP, model protobufs and image files not distributed with Arm NN. The dependencies of some of the tests are available freely on the Internet, for those who wish to experiment.

The 'armnn/samples' directory contains SimpleSample.cpp, a very basic example of the ArmNN SDK API in use.

The 'ExecuteNetwork' program, in armnn/tests/ExecuteNetwork, has no additional dependencies beyond those required by Arm NN and the model parsers. It takes any model and any input tensor, and simply prints out the output tensor. Run it with no arguments to see command-line help.

The 'ArmnnConverter' program, in armnn/src/armnnConverter, has no additional dependencies beyond those required by Arm NN and the model parsers. It takes a model in TensorFlow format and produces a serialized model in Arm NN format. Run it with no arguments to see command-line help. Note that this program can only convert models for which all operations are supported by the serialization tool [src/armnnSerializer](src/armnnSerializer/README.md).

The 'ArmnnQuantizer' program, in armnn/src/armnnQuantizer, has no additional dependencies beyond those required by Arm NN and the model parsers. It takes a 32-bit float network and converts it into a quantized asymmetric 8-bit or quantized symmetric 16-bit network.
Static quantization is supported by default but dynamic quantization can be enabled if CSV file of raw input tensors is specified. Run it with no arguments to see command-line help.

Note that Arm NN needs to be built against a particular version of [ARM's Compute Library](https://github.com/ARM-software/ComputeLibrary). The get_compute_library.sh in the scripts subdirectory will clone the compute library from the review.mlplatform.org github repository into a directory alongside armnn named 'clframework' and checks out the correct revision.

### License

Arm NN is provided under the [MIT](https://spdx.org/licenses/MIT.html) license.
See [LICENSE](LICENSE) for more information. Contributions to this project are accepted under the same license.

Individual files contain the following tag instead of the full license text.

    SPDX-License-Identifier: MIT

This enables machine processing of license information based on the SPDX License Identifiers that are available here: http://spdx.org/licenses/

### Contributions

The Arm NN project welcomes contributions. For more details on contributing to Arm NN see the [Contributing page](https://mlplatform.org/contributing/) on the [MLPlatform.org](https://mlplatform.org/) website, or see the [Contributor Guide](ContributorGuide.md).
