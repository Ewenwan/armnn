﻿//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#include "NeonWorkloadFactoryHelper.hpp"

#include <test/TensorHelpers.hpp>
#include <test/UnitTests.hpp>

#include <backendsCommon/CpuTensorHandle.hpp>
#include <neon/NeonLayerSupport.hpp>
#include <neon/NeonWorkloadFactory.hpp>
#include <reference/RefWorkloadFactory.hpp>
#include <backendsCommon/test/ActivationFixture.hpp>
#include <backendsCommon/test/LayerTests.hpp>
#include <backendsCommon/test/PermuteTestImpl.hpp>
#include <backendsCommon/test/TensorCopyUtils.hpp>
#include <backendsCommon/test/TransposeConvolution2dTestImpl.hpp>
#include <backendsCommon/test/WorkloadTestUtils.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Compute_ArmComputeNeon)

using namespace armnn;

using FactoryType = NeonWorkloadFactory;

// ============================================================================
// UNIT tests

// Convolution
ARMNN_AUTO_TEST_CASE(SimpleConvolution1d, Convolution1dTest, true)

ARMNN_AUTO_TEST_CASE(SimpleConvolution2d, SimpleConvolution2d3x5Test, true, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleConvolution2dNhwc, SimpleConvolution2d3x5Test, true, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(SimpleConvolution2d3x3Uint8, SimpleConvolution2d3x3Uint8Test, true, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleConvolution2d3x3Uint8Nhwc, SimpleConvolution2d3x3Uint8Test, true, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(UnbiasedConvolution2d, SimpleConvolution2d3x5Test, false, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(UnbiasedConvolution2dNhwc, SimpleConvolution2d3x5Test, false, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(UnbiasedConvolution2dStride2x2Nhwc,
                     SimpleConvolution2d3x3Stride2x2Test, false, DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(UnbiasedConvolution2dSquare, SimpleConvolution2d3x3Test, false, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleConvolution2dAsymmetricPadding, Convolution2dAsymmetricPaddingTest, DataLayout::NCHW)

ARMNN_AUTO_TEST_CASE(UnbiasedConvolution2dSquareNhwc, SimpleConvolution2d3x3Test, false, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(SimpleConvolution2dAsymmetricPaddingNhwc,
                     Convolution2dAsymmetricPaddingTest,
                     DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(SimpleConvolution2dSquareNhwc, SimpleConvolution2d3x3NhwcTest, false)

ARMNN_AUTO_TEST_CASE(Convolution2d3x3Dilation3x3,
                     Convolution2d3x3Dilation3x3Test<DataType::Float32, DataType::Float32>,
                     false,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(Convolution2d3x3Dilation3x3Nhwc,
                     Convolution2d3x3Dilation3x3Test<DataType::Float32, DataType::Float32>,
                     false,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(Convolution2d3x3Dilation3x3Uint8,
                     Convolution2d3x3Dilation3x3Test<DataType::QuantisedAsymm8, DataType::Signed32>,
                     false,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(Convolution2d3x3Dilation3x3NhwcUint8,
                     Convolution2d3x3Dilation3x3Test<DataType::QuantisedAsymm8, DataType::Signed32>,
                     false,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(Convolution2d2x3x3Dilation3x3,
                     Convolution2d2x3x3Dilation3x3Test<DataType::Float32, DataType::Float32>,
                     false,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(Convolution2d2x3x3Dilation3x3Nhwc,
                     Convolution2d2x3x3Dilation3x3Test<DataType::Float32, DataType::Float32>,
                     false,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(Convolution2d2x3x3Dilation3x3Uint8,
                     Convolution2d2x3x3Dilation3x3Test<DataType::QuantisedAsymm8, DataType::Signed32>,
                     false,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(Convolution2d2x3x3Dilation3x3NhwcUint8,
                     Convolution2d2x3x3Dilation3x3Test<DataType::QuantisedAsymm8, DataType::Signed32>,
                     false,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(Convolution2d2x2Dilation2x2Padding2x2Stride3x3,
                     Convolution2d2x2Dilation2x2Padding2x2Stride3x3Test
                             <DataType::Float32, DataType::Float32>,
                     false,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(Convolution2d2x2Dilation2x2Padding2x2Stride3x3Nhwc,
                     Convolution2d2x2Dilation2x2Padding2x2Stride3x3Test
                             <DataType::Float32, DataType::Float32>,
                     false,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(Convolution2d2x2Dilation2x2Padding2x2Stride3x3Uint8,
                     Convolution2d2x2Dilation2x2Padding2x2Stride3x3Test
                             <DataType::QuantisedAsymm8, DataType::Signed32>,
                     false,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(Convolution2d2x2Dilation2x2Padding2x2Stride3x3NhwcUint8,
                     Convolution2d2x2Dilation2x2Padding2x2Stride3x3Test
                             <DataType::QuantisedAsymm8, DataType::Signed32>,
                     false,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(DepthwiseConvolution2dMult4,
                     DepthwiseConvolution2dMult4Test<armnn::DataType::Float32, armnn::DataType::Float32>,
                     false,
                     armnn::DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(DepthwiseConvolution2dMult2,
                     DepthwiseConvolution2dMult2Test<armnn::DataType::Float32, armnn::DataType::Float32>,
                     false,
                     armnn::DataLayout::NCHW)

// Depthwise Convolution
ARMNN_AUTO_TEST_CASE(DepthwiseConvolution2dDepthMul1,
                     DepthwiseConvolution2dDepthMul1Test, true, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(UnbiasedDepthwiseConvolution2dDepthMul1,
                     DepthwiseConvolution2dDepthMul1Test, false, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(DepthwiseConvolution2dDepthMul1Uint8,
                     DepthwiseConvolution2dDepthMul1Uint8Test, true, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(UnbiasedDepthwiseConvolution2dDepthMul1Uint8,
                     DepthwiseConvolution2dDepthMul1Uint8Test, false, DataLayout::NCHW)

// NHWC Depthwise Convolution
ARMNN_AUTO_TEST_CASE(DepthwiseConvolution2dDepthMul1NHhwc,
                     DepthwiseConvolution2dDepthMul1Test, true, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(UnbiasedDepthwiseConvolution2dDepthMul1Nhwc,
                     DepthwiseConvolution2dDepthMul1Test, false, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(DepthwiseConvolution2dDepthMul1Uint8Nhwc,
                     DepthwiseConvolution2dDepthMul1Uint8Test, true, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(UnbiasedDepthwiseConvolution2dDepthMul1Uint8Nhwc,
                     DepthwiseConvolution2dDepthMul1Uint8Test, false, DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(DepthwiseConvolution2dDepthNhwc, DepthwiseConvolution2dDepthNhwcTest, false)
ARMNN_AUTO_TEST_CASE(SimpleDepthwiseConvolution2d3x3Dilation3x3Nhwc,
                     SimpleDepthwiseConvolution2d3x3Dilation3x3NhwcTest)


ARMNN_AUTO_TEST_CASE(DepthwiseConvolution2dAsymmetric,
                     DepthwiseConvolution2dAsymmetricTest, true, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(UnbiasedDepthwiseConvolution2dAsymmetric,
                     DepthwiseConvolution2dAsymmetricTest, false, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(DepthwiseConvolution2dAsymmetricNhwc,
                     DepthwiseConvolution2dAsymmetricTest, true, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(UnbiasedDepthwiseConvolution2dAsymmetricNhwc,
                     DepthwiseConvolution2dAsymmetricTest, false, DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(DepthwiseConvolution2dDepthMul64, DepthwiseConvolution2dDepthMul64Test);

namespace
{

DepthwiseConvolution2dDescriptor MakeDepthwiseConv2dDesc(uint32_t strideX, uint32_t strideY,
    uint32_t depthMultiplier = 1, uint32_t padLeft = 0, uint32_t padRight = 0,
    uint32_t padTop = 0, uint32_t padBottom = 0)
{
    boost::ignore_unused(depthMultiplier);

    DepthwiseConvolution2dDescriptor desc;

    desc.m_PadLeft = padLeft;
    desc.m_PadRight = padRight;

    desc.m_PadTop = padTop;
    desc.m_PadBottom = padBottom;
    desc.m_StrideX = strideX;
    desc.m_StrideY = strideY;
    desc.m_BiasEnabled = false;

    return desc;
}

TensorInfo CreateOutputTensorInfo(const TensorInfo& inputInfo,
                                         const TensorInfo& weightsInfo,
                                         const DepthwiseConvolution2dDescriptor& descriptor,
                                         DataType dataType)
{
    const TensorShape& inputShape  = inputInfo.GetShape();
    const TensorShape& filterShape = weightsInfo.GetShape();

    unsigned int inWidth = inputShape[3];
    unsigned int inHeight = inputShape[2];
    unsigned int inBatchSize = inputShape[0];

    unsigned int filterWidth = filterShape[3];
    unsigned int readWidth = (inWidth + descriptor.m_PadLeft + descriptor.m_PadRight) - (filterWidth);
    unsigned int outWidth =  1u + (readWidth / descriptor.m_StrideX);

    unsigned int filterHeight = filterShape[2];
    unsigned int readHeight = (inHeight + descriptor.m_PadTop + descriptor.m_PadBottom) - (filterHeight);
    unsigned int outHeight = 1u + (readHeight / descriptor.m_StrideY);
    unsigned int depthMultiplier = filterShape[0];

    unsigned int outChannels = filterShape[1] * depthMultiplier;
    unsigned int outBatchSize = inBatchSize;

    TensorShape outputShape({outBatchSize, outChannels, outHeight, outWidth});
    return TensorInfo(outputShape, dataType);
}
}

BOOST_AUTO_TEST_CASE(DepthwiseConv2dUtils)
{
    const DataType dataType = DataType::Float32;

    TensorInfo inputInfo({1, 1, 10, 10 }, dataType);
    TensorInfo outputInfo;
    TensorInfo weightsInfo3x3({ 1, 1, 3, 3 }, dataType);
    TensorInfo biasesInfo;

    DepthwiseConvolution2dDescriptor descriptor;
    NeonLayerSupport layerSupport;

    // Strides supported: 1,2,3
    descriptor = MakeDepthwiseConv2dDesc(1, 1);
    outputInfo = CreateOutputTensorInfo(inputInfo, weightsInfo3x3, descriptor, dataType);
    BOOST_TEST(layerSupport.IsDepthwiseConvolutionSupported(inputInfo, outputInfo, descriptor,
                                                            weightsInfo3x3, biasesInfo));

    descriptor = MakeDepthwiseConv2dDesc(1, 2);
    outputInfo = CreateOutputTensorInfo(inputInfo, weightsInfo3x3, descriptor, dataType);
    BOOST_TEST(layerSupport.IsDepthwiseConvolutionSupported(inputInfo, outputInfo, descriptor,
                                                            weightsInfo3x3, biasesInfo));

    descriptor = MakeDepthwiseConv2dDesc(1, 3);
    outputInfo = CreateOutputTensorInfo(inputInfo, weightsInfo3x3, descriptor, dataType);
    BOOST_TEST(layerSupport.IsDepthwiseConvolutionSupported(inputInfo, outputInfo, descriptor,
                                                            weightsInfo3x3, biasesInfo));

    descriptor = MakeDepthwiseConv2dDesc(2, 1);
    outputInfo = CreateOutputTensorInfo(inputInfo, weightsInfo3x3, descriptor, dataType);
    BOOST_TEST(layerSupport.IsDepthwiseConvolutionSupported(inputInfo, outputInfo, descriptor,
                                                            weightsInfo3x3, biasesInfo));

    descriptor = MakeDepthwiseConv2dDesc(2, 2);
    outputInfo = CreateOutputTensorInfo(inputInfo, weightsInfo3x3, descriptor, dataType);
    BOOST_TEST(layerSupport.IsDepthwiseConvolutionSupported(inputInfo, outputInfo, descriptor,
                                                            weightsInfo3x3, biasesInfo));

    descriptor = MakeDepthwiseConv2dDesc(2, 3);
    outputInfo = CreateOutputTensorInfo(inputInfo, weightsInfo3x3, descriptor, dataType);
    BOOST_TEST(layerSupport.IsDepthwiseConvolutionSupported(inputInfo, outputInfo, descriptor,
                                                            weightsInfo3x3, biasesInfo));

    descriptor = MakeDepthwiseConv2dDesc(3, 1);
    outputInfo = CreateOutputTensorInfo(inputInfo, weightsInfo3x3, descriptor, dataType);
    BOOST_TEST(layerSupport.IsDepthwiseConvolutionSupported(inputInfo, outputInfo, descriptor,
                                                            weightsInfo3x3, biasesInfo));

    descriptor = MakeDepthwiseConv2dDesc(3, 2);
    outputInfo = CreateOutputTensorInfo(inputInfo, weightsInfo3x3, descriptor, dataType);
    BOOST_TEST(layerSupport.IsDepthwiseConvolutionSupported(inputInfo, outputInfo, descriptor,
                                                            weightsInfo3x3, biasesInfo));

    descriptor = MakeDepthwiseConv2dDesc(3, 3);
    outputInfo = CreateOutputTensorInfo(inputInfo, weightsInfo3x3, descriptor, dataType);
    BOOST_TEST(layerSupport.IsDepthwiseConvolutionSupported(inputInfo, outputInfo, descriptor,
                                                            weightsInfo3x3, biasesInfo));

    // Supported stride 4
    descriptor = MakeDepthwiseConv2dDesc(4, 1);
    outputInfo = CreateOutputTensorInfo(inputInfo, weightsInfo3x3, descriptor, dataType);
    BOOST_TEST(layerSupport.IsDepthwiseConvolutionSupported(inputInfo, outputInfo, descriptor,
                                                            weightsInfo3x3, biasesInfo));

    // Supported weights shape 1x1
    TensorInfo weightsInfo1x1({ 1, 1, 1, 1 }, DataType::Float32);
    descriptor = MakeDepthwiseConv2dDesc(1, 1);
    outputInfo = CreateOutputTensorInfo(inputInfo, weightsInfo1x1, descriptor, dataType);
    BOOST_TEST(layerSupport.IsDepthwiseConvolutionSupported(inputInfo, outputInfo, descriptor,
                                                            weightsInfo1x1, biasesInfo));

    // Supported shape 2x2
    TensorInfo weightsInfo2x2({ 1, 1, 2, 2 }, DataType::Float32);
    descriptor = MakeDepthwiseConv2dDesc(1, 1);
    outputInfo = CreateOutputTensorInfo(inputInfo, weightsInfo2x2, descriptor, dataType);
    BOOST_TEST(layerSupport.IsDepthwiseConvolutionSupported(inputInfo, outputInfo, descriptor,
                                                            weightsInfo2x2, biasesInfo));

    // Asymmetric padding
    descriptor = MakeDepthwiseConv2dDesc(1, 1, 1, 1, 2, 1, 2);
    outputInfo = CreateOutputTensorInfo(inputInfo, weightsInfo3x3, descriptor, dataType);
    BOOST_TEST(layerSupport.IsDepthwiseConvolutionSupported(inputInfo, outputInfo, descriptor,
                                                            weightsInfo3x3, biasesInfo));
}

// Dequantize
ARMNN_AUTO_TEST_CASE(DequantizeSimpleUint8, DequantizeSimpleUint8Test)
ARMNN_AUTO_TEST_CASE(DequantizeOffsetUint8, DequantizeOffsetUint8Test)

// Pooling
ARMNN_AUTO_TEST_CASE(SimpleMaxPooling2dSize3x3Stride2x4, SimpleMaxPooling2dSize3x3Stride2x4Test, true)
ARMNN_AUTO_TEST_CASE(SimpleMaxPooling2dSize3x3Stride2x4Uint8, SimpleMaxPooling2dSize3x3Stride2x4Uint8Test, true)

ARMNN_AUTO_TEST_CASE(SimpleMaxPooling2d, SimpleMaxPooling2dTest, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleMaxPooling2dNhwc, SimpleMaxPooling2dTest, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(SimpleMaxPooling2dUint8, SimpleMaxPooling2dUint8Test, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleMaxPooling2dUint8Nhwc, SimpleMaxPooling2dUint8Test, DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(SimpleAveragePooling2d, SimpleAveragePooling2dTest, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleAveragePooling2dNhwc, SimpleAveragePooling2dTest, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleAveragePooling2dUint8, SimpleAveragePooling2dUint8Test, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleAveragePooling2dUint8Nhwc, SimpleAveragePooling2dUint8Test, DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(LargeTensorsAveragePooling2d, LargeTensorsAveragePooling2dTest)
ARMNN_AUTO_TEST_CASE(LargeTensorsAveragePooling2dUint8, LargeTensorsAveragePooling2dUint8Test)

ARMNN_AUTO_TEST_CASE(SimpleL2Pooling2d, SimpleL2Pooling2dTest, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleL2Pooling2dNeon, SimpleL2Pooling2dTest, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(UNSUPPORTED_SimpleL2Pooling2dUint8, SimpleL2Pooling2dUint8Test, DataLayout::NCHW)

ARMNN_AUTO_TEST_CASE(L2Pooling2dSize3Stride1, L2Pooling2dSize3Stride1Test)
ARMNN_AUTO_TEST_CASE(UNSUPPORTED_L2Pooling2dSize3Stride1Uint8, L2Pooling2dSize3Stride1Uint8Test)
ARMNN_AUTO_TEST_CASE(L2Pooling2dSize3Stride3, L2Pooling2dSize3Stride3Test)
ARMNN_AUTO_TEST_CASE(UNSUPPORTED_L2Pooling2dSize3Stride3Uint8, L2Pooling2dSize3Stride3Uint8Test)
ARMNN_AUTO_TEST_CASE(L2Pooling2dSize3Stride4, L2Pooling2dSize3Stride4Test)
ARMNN_AUTO_TEST_CASE(UNSUPPORTED_L2Pooling2dSize3Stride4Uint8, L2Pooling2dSize3Stride4Uint8Test)
ARMNN_AUTO_TEST_CASE(L2Pooling2dSize7, L2Pooling2dSize7Test)
ARMNN_AUTO_TEST_CASE(UNSUPPORTED_L2Pooling2dSize7Uint8, L2Pooling2dSize7Uint8Test)
ARMNN_AUTO_TEST_CASE(L2Pooling2dSize9, L2Pooling2dSize9Test)
ARMNN_AUTO_TEST_CASE(UNSUPPORTED_L2Pooling2dSize9Uint8, L2Pooling2dSize9Uint8Test)

// Ignore padding values for pooling but count padding fields into the divisor
ARMNN_AUTO_TEST_CASE(IgnorePaddingSimpleMaxPooling2d, IgnorePaddingSimpleMaxPooling2dTest)
ARMNN_AUTO_TEST_CASE(IgnorePaddingSimpleMaxPooling2dUint8, IgnorePaddingSimpleMaxPooling2dUint8Test)
ARMNN_AUTO_TEST_CASE(IgnorePaddingMaxPooling2dSize3, IgnorePaddingMaxPooling2dSize3Test)
ARMNN_AUTO_TEST_CASE(IgnorePaddingMaxPooling2dSize3Uint8, IgnorePaddingMaxPooling2dSize3Uint8Test)

ARMNN_AUTO_TEST_CASE(IgnorePaddingSimpleAveragePooling2d, IgnorePaddingSimpleAveragePooling2dTest)
ARMNN_AUTO_TEST_CASE(IgnorePaddingSimpleAveragePooling2dUint8, IgnorePaddingSimpleAveragePooling2dUint8Test)
ARMNN_AUTO_TEST_CASE(IgnorePaddingSimpleAveragePooling2dNoPadding, IgnorePaddingSimpleAveragePooling2dNoPaddingTest)
ARMNN_AUTO_TEST_CASE(IgnorePaddingSimpleAveragePooling2dNoPaddingUint8,
    IgnorePaddingSimpleAveragePooling2dNoPaddingUint8Test)
ARMNN_AUTO_TEST_CASE(IgnorePaddingAveragePooling2dSize3, IgnorePaddingAveragePooling2dSize3Test)
ARMNN_AUTO_TEST_CASE(IgnorePaddingAveragePooling2dSize3Uint8, IgnorePaddingAveragePooling2dSize3Uint8Test)
ARMNN_AUTO_TEST_CASE(IgnorePaddingAveragePooling2dSize3x2Stride2x2,
                             IgnorePaddingAveragePooling2dSize3x2Stride2x2Test, false)
ARMNN_AUTO_TEST_CASE(IgnorePaddingAveragePooling2dSize3x2Stride2x2NoPadding,
                             IgnorePaddingAveragePooling2dSize3x2Stride2x2Test,
                                          true)

ARMNN_AUTO_TEST_CASE(IgnorePaddingSimpleL2Pooling2d, IgnorePaddingSimpleL2Pooling2dTest)
ARMNN_AUTO_TEST_CASE(UNSUPPORTED_IgnorePaddingSimpleL2Pooling2dUint8, IgnorePaddingSimpleL2Pooling2dUint8Test)
ARMNN_AUTO_TEST_CASE(IgnorePaddingL2Pooling2dSize3, IgnorePaddingL2Pooling2dSize3Test)
ARMNN_AUTO_TEST_CASE(UNSUPPORTED_IgnorePaddingL2Pooling2dSize3Uint8, IgnorePaddingL2Pooling2dSize3Uint8Test)

// Activation
ARMNN_AUTO_TEST_CASE(ConstantLinearActivation, ConstantLinearActivationTest)

// ReLu
ARMNN_AUTO_TEST_CASE(ReLu1Uint8, BoundedReLuUint8UpperAndLowerBoundTest)
ARMNN_AUTO_TEST_CASE(ReLu6Uint8, BoundedReLuUint8UpperBoundOnlyTest)

// Sigmoid
ARMNN_AUTO_TEST_CASE(SimpleSigmoid, SimpleSigmoidTest)
ARMNN_AUTO_TEST_CASE(SimpleSigmoidUint8, SimpleSigmoidUint8Test)

// Softmax
ARMNN_AUTO_TEST_CASE(SimpleSoftmaxBeta1, SimpleSoftmaxTest, 1.0f)
ARMNN_AUTO_TEST_CASE(SimpleSoftmaxBeta2, SimpleSoftmaxTest, 2.0f)
ARMNN_AUTO_TEST_CASE(SimpleSoftmaxBeta1Uint8, SimpleSoftmaxUint8Test, 1.0f)
ARMNN_AUTO_TEST_CASE(SimpleSoftmaxBeta2Uint8, SimpleSoftmaxUint8Test, 2.0f)

ARMNN_AUTO_TEST_CASE(Simple3dSoftmaxBeta1, Simple3dSoftmaxTest, 1.0f)
ARMNN_AUTO_TEST_CASE(Simple3dSoftmaxBeta1Uint8, Simple3dSoftmaxUint8Test, 1.0f)

ARMNN_AUTO_TEST_CASE(Simple4dSoftmaxBeta1, Simple4dSoftmaxTest, 1.0f)
ARMNN_AUTO_TEST_CASE(Simple4dSoftmaxBeta1Uint8, Simple4dSoftmaxUint8Test, 1.0f)

// SpaceToDepth
ARMNN_AUTO_TEST_CASE(SpaceToDepthNCHWAsymmQ8, SpaceToDepthNCHWAsymmQ8Test)
ARMNN_AUTO_TEST_CASE(SpaceToDepthNHWCAsymmQ8, SpaceToDepthNHWCAsymmQ8Test)

ARMNN_AUTO_TEST_CASE(SpaceToDepthNHWC1Float32, SpaceToDepthNHWCFloat32Test1)
ARMNN_AUTO_TEST_CASE(SpaceToDepthNCHW1Float32, SpaceToDepthNCHWFloat32Test1)

ARMNN_AUTO_TEST_CASE(SpaceToDepthNHWC2Float32, SpaceToDepthNHWCFloat32Test2)
ARMNN_AUTO_TEST_CASE(SpaceToDepthNCHW2Float32, SpaceToDepthNCHWFloat32Test2)

ARMNN_AUTO_TEST_CASE(SpaceToDepthNHWCQSymm16, SpaceToDepthNHWCQSymm16Test)
ARMNN_AUTO_TEST_CASE(SpaceToDepthNCHWQSymm16, SpaceToDepthNCHWQSymm16Test)

// Splitter
ARMNN_AUTO_TEST_CASE(SimpleSplitter, SplitterTest)
ARMNN_AUTO_TEST_CASE(SimpleSplitterUint8, SplitterUint8Test)

ARMNN_AUTO_TEST_CASE(CopyViaSplitter, CopyViaSplitterTest)
ARMNN_AUTO_TEST_CASE(CopyViaSplitterUint8, CopyViaSplitterUint8Test)

// Concat
ARMNN_AUTO_TEST_CASE(SimpleConcat, ConcatTest)
ARMNN_AUTO_TEST_CASE(ConcatUint8, ConcatUint8Test)
ARMNN_AUTO_TEST_CASE(ConcatUint8DifferentInputOutputQParam,
                     ConcatDifferentInputOutputQParamTest<DataType::QuantisedAsymm8>, false)

// Fully Connected
ARMNN_AUTO_TEST_CASE(SimpleFullyConnected, FullyConnectedFloat32Test, false, false)
ARMNN_AUTO_TEST_CASE(SimpleFullyConnectedWithBias, FullyConnectedFloat32Test, true, false)
ARMNN_AUTO_TEST_CASE(SimpleFullyConnectedWithTranspose, FullyConnectedFloat32Test, false, true)
ARMNN_AUTO_TEST_CASE(FullyConnectedLarge, FullyConnectedLargeTest, false)
ARMNN_AUTO_TEST_CASE(FullyConnectedLargeTransposed, FullyConnectedLargeTest, true)
ARMNN_AUTO_TEST_CASE(FullyConnectedUint8, FullyConnectedTest<DataType::QuantisedAsymm8>, false)
ARMNN_AUTO_TEST_CASE(FullyConnectedBiasedUint8, FullyConnectedTest<DataType::QuantisedAsymm8>, true)

// Add
ARMNN_AUTO_TEST_CASE(SimpleAdd, AdditionTest)
ARMNN_AUTO_TEST_CASE(Add5d, Addition5dTest)
ARMNN_AUTO_TEST_CASE(AddBroadcast, AdditionBroadcastTest)
ARMNN_AUTO_TEST_CASE(AddBroadcast1Element, AdditionBroadcast1ElementTest)

// Sub
ARMNN_AUTO_TEST_CASE(SimpleSub, SubtractionTest)
ARMNN_AUTO_TEST_CASE(SubBroadcast1Element, SubtractionBroadcast1ElementTest)
ARMNN_AUTO_TEST_CASE(SubBroadcast, SubtractionBroadcastTest)
ARMNN_AUTO_TEST_CASE(SubtractionUint8, SubtractionUint8Test)
ARMNN_AUTO_TEST_CASE(SubBroadcastUint8, SubtractionBroadcastUint8Test)
ARMNN_AUTO_TEST_CASE(SubBroadcast1ElementUint8, SubtractionBroadcast1ElementUint8Test)

// Mul
ARMNN_AUTO_TEST_CASE(SimpleMultiplication, MultiplicationTest)
ARMNN_AUTO_TEST_CASE(MultiplicationBroadcast1Element, MultiplicationBroadcast1ElementTest)
ARMNN_AUTO_TEST_CASE(MultiplicationBroadcast1DVector, MultiplicationBroadcast1DVectorTest)
ARMNN_AUTO_TEST_CASE(MultiplicationUint8, MultiplicationUint8Test)
ARMNN_AUTO_TEST_CASE(MultiplicationBroadcast1ElementUint8, MultiplicationBroadcast1ElementUint8Test)
ARMNN_AUTO_TEST_CASE(MultiplicationBroadcast1DVectorUint8, MultiplicationBroadcast1DVectorUint8Test)
ARMNN_AUTO_TEST_CASE(Multiplication5d, Multiplication5dTest)

// Batch Norm
ARMNN_AUTO_TEST_CASE(BatchNorm, BatchNormTest)
ARMNN_AUTO_TEST_CASE(BatchNormNhwc, BatchNormNhwcTest)

// Constant
ARMNN_AUTO_TEST_CASE(Constant, ConstantTest)
ARMNN_AUTO_TEST_CASE(ConstantUint8, ConstantUint8SimpleQuantizationScaleNoOffsetTest)

// Concatenation
ARMNN_AUTO_TEST_CASE(Concatenation1d, Concatenation1dTest)
ARMNN_AUTO_TEST_CASE(Concatenation1dUint8, Concatenation1dUint8Test)

ARMNN_AUTO_TEST_CASE(Concatenation2dDim0, Concatenation2dDim0Test)
ARMNN_AUTO_TEST_CASE(Concatenation2dDim0Uint8, Concatenation2dDim0Uint8Test)
ARMNN_AUTO_TEST_CASE(Concatenation2dDim1, Concatenation2dDim1Test)
ARMNN_AUTO_TEST_CASE(Concatenation2dDim1Uint8, Concatenation2dDim1Uint8Test)

ARMNN_AUTO_TEST_CASE(Concatenation2dDim0DiffInputDims, Concatenation2dDim0DiffInputDimsTest)
ARMNN_AUTO_TEST_CASE(Concatenation2dDim0DiffInputDimsUint8, Concatenation2dDim0DiffInputDimsUint8Test)
ARMNN_AUTO_TEST_CASE(Concatenation2dDim1DiffInputDims, Concatenation2dDim1DiffInputDimsTest)
ARMNN_AUTO_TEST_CASE(Concatenation2dDim1DiffInputDimsUint8, Concatenation2dDim1DiffInputDimsUint8Test)

ARMNN_AUTO_TEST_CASE(Concatenation3dDim0, Concatenation3dDim0Test)
ARMNN_AUTO_TEST_CASE(Concatenation3dDim0Uint8, Concatenation3dDim0Uint8Test)
ARMNN_AUTO_TEST_CASE(Concatenation3dDim1, Concatenation3dDim1Test)
ARMNN_AUTO_TEST_CASE(Concatenation3dDim1Uint8, Concatenation3dDim1Uint8Test)
ARMNN_AUTO_TEST_CASE(Concatenation3dDim2, Concatenation3dDim2Test, false)
ARMNN_AUTO_TEST_CASE(Concatenation3dDim2Uint8, Concatenation3dDim2Uint8Test, false)

ARMNN_AUTO_TEST_CASE(Concatenation3dDim0DiffInputDims, Concatenation3dDim0DiffInputDimsTest)
ARMNN_AUTO_TEST_CASE(Concatenation3dDim0DiffInputDimsUint8, Concatenation3dDim0DiffInputDimsUint8Test)
ARMNN_AUTO_TEST_CASE(Concatenation3dDim1DiffInputDims, Concatenation3dDim1DiffInputDimsTest)
ARMNN_AUTO_TEST_CASE(Concatenation3dDim1DiffInputDimsUint8, Concatenation3dDim1DiffInputDimsUint8Test)
ARMNN_AUTO_TEST_CASE(Concatenation3dDim2DiffInputDims, Concatenation3dDim2DiffInputDimsTest, false)
ARMNN_AUTO_TEST_CASE(Concatenation3dDim2DiffInputDimsUint8, Concatenation3dDim2DiffInputDimsUint8Test, false)

ARMNN_AUTO_TEST_CASE(Concatenation4dDim0, Concatenation4dDim0Test)
ARMNN_AUTO_TEST_CASE(Concatenation4dDim1, Concatenation4dDim1Test)
ARMNN_AUTO_TEST_CASE(Concatenation4dDim3, Concatenation4dDim3Test, false)
ARMNN_AUTO_TEST_CASE(Concatenation4dDim0Uint8, Concatenation4dDim0Uint8Test)
ARMNN_AUTO_TEST_CASE(Concatenation4dDim1Uint8, Concatenation4dDim1Uint8Test)
ARMNN_AUTO_TEST_CASE(Concatenation4dDim3Uint8, Concatenation4dDim3Uint8Test, false)

ARMNN_AUTO_TEST_CASE(Concatenation4dDiffShapeDim0, Concatenation4dDiffShapeDim0Test)
ARMNN_AUTO_TEST_CASE(Concatenation4dDiffShapeDim1, Concatenation4dDiffShapeDim1Test)
ARMNN_AUTO_TEST_CASE(Concatenation4dDiffShapeDim3, Concatenation4dDiffShapeDim3Test, false)
ARMNN_AUTO_TEST_CASE(Concatenation4dDiffShapeDim0Uint8, Concatenation4dDiffShapeDim0Uint8Test)
ARMNN_AUTO_TEST_CASE(Concatenation4dDiffShapeDim1Uint8, Concatenation4dDiffShapeDim1Uint8Test)
ARMNN_AUTO_TEST_CASE(Concatenation4dDiffShapeDim3Uint8, Concatenation4dDiffShapeDim3Uint8Test, false)
// L2 Normalization
ARMNN_AUTO_TEST_CASE(L2Normalization1d, L2Normalization1dTest, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(L2Normalization2d, L2Normalization2dTest, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(L2Normalization3d, L2Normalization3dTest, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(L2Normalization4d, L2Normalization4dTest, DataLayout::NCHW)

ARMNN_AUTO_TEST_CASE(L2Normalization1dNhwc, L2Normalization1dTest, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(L2Normalization2dNhwc, L2Normalization2dTest, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(L2Normalization3dNhwc, L2Normalization3dTest, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(L2Normalization4dNhwc, L2Normalization4dTest, DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(L2Normalization2dShape, L2Normalization2dShapeTest);

ARMNN_AUTO_TEST_CASE(L2NormalizationDefaultEpsilon, L2NormalizationDefaultEpsilonTest, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(L2NormalizationNonDefaultEpsilon, L2NormalizationNonDefaultEpsilonTest, DataLayout::NCHW)

// Floor
ARMNN_AUTO_TEST_CASE(SimpleFloor, SimpleFloorTest<DataType::Float32>)

// Greater
ARMNN_AUTO_TEST_CASE(SimpleGreater, GreaterSimpleTest)
ARMNN_AUTO_TEST_CASE(GreaterBroadcast1Element, GreaterBroadcast1ElementTest)
ARMNN_AUTO_TEST_CASE(GreaterBroadcast1DVector, GreaterBroadcast1DVectorTest)
ARMNN_AUTO_TEST_CASE(GreaterUint8, GreaterUint8Test)
ARMNN_AUTO_TEST_CASE(GreaterBroadcast1ElementUint8, GreaterBroadcast1ElementUint8Test)
ARMNN_AUTO_TEST_CASE(GreaterBroadcast1DVectorUint8, GreaterBroadcast1DVectorUint8Test)

// Reshape
ARMNN_AUTO_TEST_CASE(SimpleReshapeFloat32, SimpleReshapeTest<armnn::DataType::Float32>)
ARMNN_AUTO_TEST_CASE(SimpleReshapeUint8, SimpleReshapeTest<armnn::DataType::QuantisedAsymm8>)
ARMNN_AUTO_TEST_CASE(Reshape5d, Reshape5dTest<armnn::DataType::Float32>)

// Pad
ARMNN_AUTO_TEST_CASE(PadFloat322d, PadFloat322dTest)
ARMNN_AUTO_TEST_CASE(PadFloat322dCustomPadding, PadFloat322dCustomPaddingTest)
ARMNN_AUTO_TEST_CASE(PadFloat323d, PadFloat323dTest)
ARMNN_AUTO_TEST_CASE(PadFloat324d, PadFloat324dTest)

ARMNN_AUTO_TEST_CASE(PadUint82d, PadUint82dTest)
ARMNN_AUTO_TEST_CASE(PadUint82dCustomPadding, PadUint82dCustomPaddingTest)
ARMNN_AUTO_TEST_CASE(PadUint83d, PadUint83dTest)
ARMNN_AUTO_TEST_CASE(PadUint84d, PadUint84dTest)

ARMNN_AUTO_TEST_CASE(Pad2dQSymm16, Pad2dTestCommon<DataType::QuantisedSymm16>, 2.0f, 0, 0.0f)
ARMNN_AUTO_TEST_CASE(Pad2dQSymm16CustomPadding, Pad2dTestCommon<DataType::QuantisedSymm16>, 2.0f, 0, 1.0f)
ARMNN_AUTO_TEST_CASE(Pad3dQSymm16, Pad3dTestCommon<DataType::QuantisedSymm16>, 2.0f, 0)
ARMNN_AUTO_TEST_CASE(Pad4dQSymm16, Pad4dTestCommon<DataType::QuantisedSymm16>, 2.0f, 0)

// Permute
ARMNN_AUTO_TEST_CASE(SimplePermuteFloat32, SimplePermuteTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(PermuteFloat32ValueSet1Test, PermuteValueSet1Test<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(PermuteFloat32ValueSet2Test, PermuteValueSet2Test<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(PermuteFloat32ValueSet3Test, PermuteValueSet3Test<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(SimplePermuteQASymm8, SimplePermuteTest<DataType::QuantisedAsymm8>)
ARMNN_AUTO_TEST_CASE(PermuteQASymm8ValueSet1Test, PermuteValueSet1Test<DataType::QuantisedAsymm8>)
ARMNN_AUTO_TEST_CASE(PermuteQASymm8ValueSet2Test, PermuteValueSet2Test<DataType::QuantisedAsymm8>)
ARMNN_AUTO_TEST_CASE(PermuteQASymm8ValueSet3Test, PermuteValueSet3Test<DataType::QuantisedAsymm8>)

// Lstm
ARMNN_AUTO_TEST_CASE(LstmLayerFloat32WithCifgWithPeepholeNoProjection,
                     LstmLayerFloat32WithCifgWithPeepholeNoProjectionTest)
ARMNN_AUTO_TEST_CASE(LstmLayerFloat32NoCifgNoPeepholeNoProjection,
                     LstmLayerFloat32NoCifgNoPeepholeNoProjectionTest)
ARMNN_AUTO_TEST_CASE(LstmLayerFloat32NoCifgWithPeepholeWithProjection,
                     LstmLayerFloat32NoCifgWithPeepholeWithProjectionTest)
ARMNN_AUTO_TEST_CASE(LstmLayerFloat32NoCifgWithPeepholeWithProjectionWithLayerNorm,
                     LstmLayerFloat32NoCifgWithPeepholeWithProjectionWithLayerNormTest)

ARMNN_AUTO_TEST_CASE(QuantizedLstm, QuantizedLstmTest)

// Mean
ARMNN_AUTO_TEST_CASE(MeanSimpleFloat32, MeanSimpleTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(MeanSimpleAxisFloat32, MeanSimpleAxisTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(MeanKeepDimsFloat32, MeanKeepDimsTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(MeanMultipleDimsFloat32, MeanMultipleDimsTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(MeanVts1Float32, MeanVts1Test<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(MeanVts2Float32, MeanVts2Test<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(MeanVts3Float32, MeanVts3Test<DataType::Float32>)

ARMNN_AUTO_TEST_CASE(MeanSimpleQuantisedAsymm8, MeanSimpleTest<DataType::QuantisedAsymm8>)
ARMNN_AUTO_TEST_CASE(MeanSimpleAxisQuantisedAsymm8, MeanSimpleAxisTest<DataType::QuantisedAsymm8>)
ARMNN_AUTO_TEST_CASE(MeanKeepDimsQuantisedAsymm8, MeanKeepDimsTest<DataType::QuantisedAsymm8>)
ARMNN_AUTO_TEST_CASE(MeanMultipleDimsQuantisedAsymm8, MeanMultipleDimsTest<DataType::QuantisedAsymm8>)
ARMNN_AUTO_TEST_CASE(MeanVts1QuantisedAsymm8, MeanVts1Test<DataType::QuantisedAsymm8>)
ARMNN_AUTO_TEST_CASE(MeanVts2QuantisedAsymm8, MeanVts2Test<DataType::QuantisedAsymm8>)
ARMNN_AUTO_TEST_CASE(MeanVts3QuantisedAsymm8, MeanVts3Test<DataType::QuantisedAsymm8>)

// Max
ARMNN_AUTO_TEST_CASE(SimpleMaximum, MaximumSimpleTest)
ARMNN_AUTO_TEST_CASE(MaximumBroadcast1Element, MaximumBroadcast1ElementTest)
ARMNN_AUTO_TEST_CASE(MaximumBroadcast1DVector, MaximumBroadcast1DVectorTest)
ARMNN_AUTO_TEST_CASE(MaximumUint8, MaximumUint8Test)
ARMNN_AUTO_TEST_CASE(MaximumBroadcast1ElementUint8, MaximumBroadcast1ElementUint8Test)
ARMNN_AUTO_TEST_CASE(MaximumBroadcast1DVectorUint8, MaximumBroadcast1DVectorUint8Test)

// Min
ARMNN_AUTO_TEST_CASE(SimpleMinimum1, MinimumBroadcast1ElementTest1)
ARMNN_AUTO_TEST_CASE(SimpleMinimum2, MinimumBroadcast1ElementTest2)
ARMNN_AUTO_TEST_CASE(Minimum1DVectorUint8, MinimumBroadcast1DVectorUint8Test)

// Normalization
ARMNN_AUTO_TEST_CASE(SimpleNormalizationAcross, SimpleNormalizationAcrossTest)
ARMNN_AUTO_TEST_CASE(SimpleNormalizationWithin, SimpleNormalizationWithinTest)
ARMNN_AUTO_TEST_CASE(SimpleNormalizationAcrossNhwc, SimpleNormalizationAcrossNhwcTest)

// Resize Bilinear - NCHW data layout
ARMNN_AUTO_TEST_CASE(SimpleResizeBilinear, SimpleResizeBilinearTest<DataType::Float32>, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeBilinearNop, ResizeBilinearNopTest<DataType::Float32>, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeBilinearSqMin, ResizeBilinearSqMinTest<DataType::Float32>, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeBilinearMin, ResizeBilinearMinTest<DataType::Float32>, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeBilinearMag, ResizeBilinearMagTest<DataType::Float32>, DataLayout::NCHW)

ARMNN_AUTO_TEST_CASE(SimpleResizeBilinearUint8,
                     SimpleResizeBilinearTest<DataType::QuantisedAsymm8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeBilinearNopUint8,
                     ResizeBilinearNopTest<DataType::QuantisedAsymm8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeBilinearSqMinUint8,
                     ResizeBilinearSqMinTest<DataType::QuantisedAsymm8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeBilinearMinUint8,
                     ResizeBilinearMinTest<DataType::QuantisedAsymm8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeBilinearMagUint8,
                     ResizeBilinearMagTest<DataType::QuantisedAsymm8>,
                     DataLayout::NCHW)

// Resize Bilinear - NHWC data layout
ARMNN_AUTO_TEST_CASE(ResizeBilinearNopNhwc,
                     ResizeBilinearNopTest<DataType::Float32>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(SimpleResizeBilinearNhwc,
                     SimpleResizeBilinearTest<DataType::Float32>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeBilinearSqMinNhwc,
                     ResizeBilinearSqMinTest<DataType::Float32>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeBilinearMinNhwc,
                     ResizeBilinearMinTest<DataType::Float32>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeBilinearMagNhwc,
                     ResizeBilinearMagTest<DataType::Float32>,
                     DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(ResizeBilinearNopUint8Nhwc,
                     ResizeBilinearNopTest<DataType::QuantisedAsymm8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(SimpleResizeBilinearUint8Nhwc,
                     SimpleResizeBilinearTest<DataType::QuantisedAsymm8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeBilinearSqMinUint8Nhwc,
                     ResizeBilinearSqMinTest<DataType::QuantisedAsymm8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeBilinearMinUint8Nhwc,
                     ResizeBilinearMinTest<DataType::QuantisedAsymm8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeBilinearMagUint8Nhwc,
                     ResizeBilinearMagTest<DataType::QuantisedAsymm8>,
                     DataLayout::NHWC)

// Resize NearestNeighbor - NCHW
ARMNN_AUTO_TEST_CASE(SimpleResizeNearestNeighbor,
                     SimpleResizeNearestNeighborTest<DataType::Float32>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborNop,
                     ResizeNearestNeighborNopTest<DataType::Float32>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborSqMin,
                     ResizeNearestNeighborSqMinTest<DataType::Float32>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborMin,
                     ResizeNearestNeighborMinTest<DataType::Float32>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborMag,
                     ResizeNearestNeighborMagTest<DataType::Float32>,
                     DataLayout::NCHW, 0.1f, 50, 0.1f, 50)

ARMNN_AUTO_TEST_CASE(SimpleResizeNearestNeighborUint8,
                     SimpleResizeNearestNeighborTest<DataType::QuantisedAsymm8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborNopUint8,
                     ResizeNearestNeighborNopTest<DataType::QuantisedAsymm8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborSqMinUint8,
                     ResizeNearestNeighborSqMinTest<DataType::QuantisedAsymm8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborMinUint8,
                     ResizeNearestNeighborMinTest<DataType::QuantisedAsymm8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborMagUint8,
                     ResizeNearestNeighborMagTest<DataType::QuantisedAsymm8>,
                     DataLayout::NCHW, 0.1f, 50, 0.1f, 50)

// Resize NearestNeighbor - NHWC
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborNopNhwc,
                     ResizeNearestNeighborNopTest<DataType::Float32>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(SimpleResizeNearestNeighborNhwc,
                     SimpleResizeNearestNeighborTest<DataType::Float32>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborSqMinNhwc,
                     ResizeNearestNeighborSqMinTest<DataType::Float32>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborMinNhwc,
                     ResizeNearestNeighborMinTest<DataType::Float32>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborMagNhwc,
                     ResizeNearestNeighborMagTest<DataType::Float32>,
                     DataLayout::NHWC, 0.1f, 50, 0.1f, 50)

ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborNopUint8Nhwc,
                     ResizeNearestNeighborNopTest<DataType::QuantisedAsymm8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(SimpleResizeNearestNeighborUint8Nhwc,
                     SimpleResizeNearestNeighborTest<DataType::QuantisedAsymm8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborSqMinUint8Nhwc,
                     ResizeNearestNeighborSqMinTest<DataType::QuantisedAsymm8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborMinUint8Nhwc,
                     ResizeNearestNeighborMinTest<DataType::QuantisedAsymm8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborMagUint8Nhwc,
                     ResizeNearestNeighborMagTest<DataType::QuantisedAsymm8>,
                     DataLayout::NHWC, 0.1f, 50, 0.1f, 50)

// Strided Slice
ARMNN_AUTO_TEST_CASE(StridedSlice4DFloat32, StridedSlice4DFloat32Test)
ARMNN_AUTO_TEST_CASE(StridedSlice4DReverseFloat32, StridedSlice4DReverseFloat32Test)
ARMNN_AUTO_TEST_CASE(StridedSliceSimpleStrideFloat32, StridedSliceSimpleStrideFloat32Test)
ARMNN_AUTO_TEST_CASE(StridedSliceSimpleRangeMaskFloat32, StridedSliceSimpleRangeMaskFloat32Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskFloat32, StridedSliceShrinkAxisMaskFloat32Test)
ARMNN_AUTO_TEST_CASE(StridedSlice3DFloat32, StridedSlice3DFloat32Test)
ARMNN_AUTO_TEST_CASE(StridedSlice3DReverseFloat32, StridedSlice3DReverseFloat32Test)
ARMNN_AUTO_TEST_CASE(StridedSlice2DFloat32, StridedSlice2DFloat32Test)
ARMNN_AUTO_TEST_CASE(StridedSlice2DReverseFloat32, StridedSlice2DReverseFloat32Test)

ARMNN_AUTO_TEST_CASE(StridedSlice4DUint8, StridedSlice4DUint8Test)
ARMNN_AUTO_TEST_CASE(StridedSlice4DReverseUint8, StridedSlice4DReverseUint8Test)
ARMNN_AUTO_TEST_CASE(StridedSliceSimpleStrideUint8, StridedSliceSimpleStrideUint8Test)
ARMNN_AUTO_TEST_CASE(StridedSliceSimpleRangeMaskUint8, StridedSliceSimpleRangeMaskUint8Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskUint8, StridedSliceShrinkAxisMaskUint8Test)
ARMNN_AUTO_TEST_CASE(StridedSlice3DUint8, StridedSlice3DUint8Test)
ARMNN_AUTO_TEST_CASE(StridedSlice3DReverseUint8, StridedSlice3DReverseUint8Test)
ARMNN_AUTO_TEST_CASE(StridedSlice2DUint8, StridedSlice2DUint8Test)
ARMNN_AUTO_TEST_CASE(StridedSlice2DReverseUint8, StridedSlice2DReverseUint8Test)

// Quantize
ARMNN_AUTO_TEST_CASE(QuantizeSimpleUint8, QuantizeSimpleUint8Test)
ARMNN_AUTO_TEST_CASE(QuantizeClampUint8, QuantizeClampUint8Test)

// PReLU
ARMNN_AUTO_TEST_CASE(PreluFloat32, PreluTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(PreluUint8,   PreluTest<DataType::QuantisedAsymm8>)

// Stack
ARMNN_AUTO_TEST_CASE(Stack0Axis,               Stack0AxisTest<armnn::DataType::Float32>)
ARMNN_AUTO_TEST_CASE(Stack4dOutput1Axis,       Stack4dOutput1AxisTest<armnn::DataType::Float32>)
ARMNN_AUTO_TEST_CASE(Stack4dOutput2Axis,       Stack4dOutput2AxisTest<armnn::DataType::Float32>)
ARMNN_AUTO_TEST_CASE(Stack4dOutput3Axis,       Stack4dOutput3AxisTest<armnn::DataType::Float32>)
ARMNN_AUTO_TEST_CASE(Stack3dOutput1Axis3Input, Stack3dOutput1Axis3InputTest<armnn::DataType::Float32>)
ARMNN_AUTO_TEST_CASE(Stack5dOutput,            Stack5dOutputTest<armnn::DataType::Float32>)

// TransposeConvolution2d
ARMNN_AUTO_TEST_CASE(SimpleTransposeConvolution2dFloatNchw,
                     SimpleTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     true,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleTransposeConvolution2dFloatNhwc,
                     SimpleTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     true,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(SimpleTransposeConvolution2dUint8Nchw,
                     SimpleTransposeConvolution2dTest<DataType::QuantisedAsymm8, DataType::Signed32>,
                     true,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleTransposeConvolution2dUint8Nhwc,
                     SimpleTransposeConvolution2dTest<DataType::QuantisedAsymm8, DataType::Signed32>,
                     true,
                     DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(UnbiasedSimpleTransposeConvolution2dFloatNchw,
                     SimpleTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     false,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(UnbiasedSimpleTransposeConvolution2dFloatNhwc,
                     SimpleTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     true,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(UnbiasedSimpleTransposeConvolution2dUint8Nchw,
                     SimpleTransposeConvolution2dTest<DataType::QuantisedAsymm8, DataType::Signed32>,
                     true,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(UnbiasedSimpleTransposeConvolution2dUint8Nhwc,
                     SimpleTransposeConvolution2dTest<DataType::QuantisedAsymm8, DataType::Signed32>,
                     true,
                     DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(PaddedTransposeConvolution2dFloatNchw,
                     PaddedTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     true,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(PaddedTransposeConvolution2dFloatNhwc,
                     PaddedTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     true,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(PaddedTransposeConvolution2dUint8Nchw,
                     PaddedTransposeConvolution2dTest<DataType::QuantisedAsymm8, DataType::Signed32>,
                     true,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(PaddedTransposeConvolution2dUint8Nhwc,
                     PaddedTransposeConvolution2dTest<DataType::QuantisedAsymm8, DataType::Signed32>,
                     true,
                     DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(UnbiasedPaddedTransposeConvolution2dFloatNchw,
                     PaddedTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     false,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(UnbiasedPaddedTransposeConvolution2dFloatNhwc,
                     PaddedTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     true,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(UnbiasedPaddedTransposeConvolution2dUint8Nchw,
                     PaddedTransposeConvolution2dTest<DataType::QuantisedAsymm8, DataType::Signed32>,
                     true,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(UnbiasedPaddedTransposeConvolution2dUint8Nhwc,
                     PaddedTransposeConvolution2dTest<DataType::QuantisedAsymm8, DataType::Signed32>,
                     true,
                     DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(StridedTransposeConvolution2dFloatNchw,
                     StridedTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     true,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(StridedTransposeConvolution2dFloatNhwc,
                     StridedTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     true,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(StridedTransposeConvolution2dUint8Nchw,
                     StridedTransposeConvolution2dTest<DataType::QuantisedAsymm8, DataType::Signed32>,
                     true,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(StridedTransposeConvolution2dUint8Nhwc,
                     StridedTransposeConvolution2dTest<DataType::QuantisedAsymm8, DataType::Signed32>,
                     true,
                     DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(UnbiasedStridedTransposeConvolution2dFloatNchw,
                     StridedTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     false,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(UnbiasedStridedTransposeConvolution2dFloatNhwc,
                     StridedTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     true,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(UnbiasedStridedTransposeConvolution2dUint8Nchw,
                     StridedTransposeConvolution2dTest<DataType::QuantisedAsymm8, DataType::Signed32>,
                     true,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(UnbiasedStridedTransposeConvolution2dUint8Nhwc,
                     StridedTransposeConvolution2dTest<DataType::QuantisedAsymm8, DataType::Signed32>,
                     true,
                     DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(MultiChannelTransposeConvolution2dFloatNchw,
                     MultiChannelTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(MultiChannelTransposeConvolution2dFloatNhwc,
                     MultiChannelTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(MultiChannelTransposeConvolution2dUint8Nchw,
                     MultiChannelTransposeConvolution2dTest<DataType::QuantisedAsymm8, DataType::Signed32>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(MultiChannelTransposeConvolution2dUint8Nhwc,
                     MultiChannelTransposeConvolution2dTest<DataType::QuantisedAsymm8, DataType::Signed32>,
                     DataLayout::NHWC)

#if defined(ARMNNREF_ENABLED)

// The ARMNN_COMPARE_REF_AUTO_TEST_CASE and the ARMNN_COMPARE_REF_FIXTURE_TEST_CASE test units are not available
// if the reference backend is not built

// ============================================================================
// COMPARE tests

ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareConv2dWithReference, CompareConvolution2dTest)

ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareDepthwiseConv2dWithReferenceFloat32,
                                 CompareDepthwiseConvolution2dFloatTest,
                                 DataLayout::NCHW)
ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareDepthwiseConv2dWithReferenceUint8,
                                 CompareDepthwiseConvolution2dUint8Test,
                                 DataLayout::NCHW)

ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareDepthwiseConv2dWithReferenceFloat32Nhwc,
                                 CompareDepthwiseConvolution2dFloatTest,
                                 DataLayout::NHWC)
ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareDepthwiseConv2dWithReferenceUint8Nhwc,
                                 CompareDepthwiseConvolution2dUint8Test,
                                 DataLayout::NHWC)

ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareNormalizationWithinWithReference, CompareNormalizationTest,
                                 NormalizationAlgorithmChannel::Within,
                                 NormalizationAlgorithmMethod::LocalBrightness)
ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareNormalizationAcrossWithReference, CompareNormalizationTest,
                                 NormalizationAlgorithmChannel::Across,
                                 NormalizationAlgorithmMethod::LocalBrightness)

ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareMaxPooling2dWithReference, ComparePooling2dTest, PoolingAlgorithm::Max)
ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareMaxPooling2dWithReferenceUint8, ComparePooling2dUint8Test,
                                 PoolingAlgorithm::Max)
ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareAveragePooling2dWithReference, ComparePooling2dTest,
                                 PoolingAlgorithm::Average)
ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareAveragePooling2dWithReferenceUint8, ComparePooling2dUint8Test,
                                 PoolingAlgorithm::Average)
ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareL2Pooling2dWithReference, ComparePooling2dTest, PoolingAlgorithm::L2)
ARMNN_COMPARE_REF_AUTO_TEST_CASE(UNSUPPORTED_CompareL2Pooling2dWithReferenceUint8, ComparePooling2dUint8Test,
                                 PoolingAlgorithm::L2)

ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareSoftmaxBeta1WithReference, CompareSoftmaxTest, 1.0f)
ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareSoftmaxBeta2WithReference, CompareSoftmaxTest, 2.0f)

ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareSoftmaxUint8Beta1WithReference, CompareSoftmaxUint8Test, 1.0f)
ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareSoftmaxUint8Beta2WithReference, CompareSoftmaxUint8Test, 2.0f)

ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareAddition, CompareAdditionTest)

ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareMultiplicationWithReference, CompareMultiplicationTest)

ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareBatchNorm, CompareBatchNormTest)

ARMNN_COMPARE_REF_AUTO_TEST_CASE(ReLu1, CompareBoundedReLuTest, 1.0f, -1.0f)
ARMNN_COMPARE_REF_AUTO_TEST_CASE(ReLu6, CompareBoundedReLuTest, 6.0f, 0.0f)

// ============================================================================
// FIXTURE tests

ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareSigmoidActivationWithReference, ActivationFixture,
                                    CompareActivationTest, ActivationFunction::Sigmoid, 5u)

ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareTanhActivationWithReference, ActivationFixture,
                                    CompareActivationTest, ActivationFunction::TanH, 5u)

ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareLinearActivationWithReference, ActivationFixture,
                                    CompareActivationTest, ActivationFunction::Linear, 5u)

ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareReLuActivationWithReference, ActivationFixture,
                                    CompareActivationTest, ActivationFunction::ReLu, 5u)

ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareBoundedReLuActivationWithReference, ActivationFixture,
                                    CompareActivationTest, ActivationFunction::BoundedReLu, 5u)
ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareBoundedReLuActivationWithReferenceUint8, ActivationFixture,
                                    CompareActivationUint8Test, ActivationFunction::BoundedReLu)

ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareSoftReLuActivationWithReference, ActivationFixture,
                                    CompareActivationTest, ActivationFunction::SoftReLu, 1u)

ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareLeakyReLuActivationWithReference, ActivationFixture,
                                    CompareActivationTest, ActivationFunction::LeakyReLu, 5u)

ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareAbsActivationWithReference, ActivationFixture,
                                    CompareActivationTest, ActivationFunction::Abs, 5u)

ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareSqrtActivationWithReference, PositiveActivationFixture,
                                    CompareActivationTest, ActivationFunction::Sqrt, 5u)

ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareSquareActivationWithReference, ActivationFixture,
                                    CompareActivationTest, ActivationFunction::Square, 5u)

#endif

BOOST_AUTO_TEST_SUITE_END()
