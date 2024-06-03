find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(Python3 COMPONENTS NumPy REQUIRED)
find_package(imgui REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glew REQUIRED )
find_package(implot REQUIRED)

add_lib(src
        SOURCES
        signals/baseSignals/ContinousSignal.cpp
        signals/baseSignals/DiscreteSignal.cpp
        signals/baseSignals/GaussianNoise.cpp
        signals/baseSignals/ImpulseNoise.cpp
        signals/baseSignals/RectangularSignal.cpp
        signals/baseSignals/RectangularSymmetricSignal.cpp
        signals/baseSignals/SignalStrategy.cpp
        signals/baseSignals/SinusoidalSignal.cpp
        signals/baseSignals/SinusoidalOneHalfRectifiedSignal.cpp
        signals/baseSignals/SinusoidalTwoHalfRectifiedSignal.cpp
        signals/baseSignals/TriangularSignal.cpp
        signals/baseSignals/UniformNoise.cpp
        signals/baseSignals/UnitImpulseSignal.cpp
        signals/baseSignals/UnitJumpSignal.cpp
        signals/baseSignals/Signal.cpp
        signals/baseSignals/DiscreteSignalStatic.cpp
        signals/baseSignals/OperationResultSignal.cpp
        signals/signalConversion/ADC/Sampling.cpp
        signals/signalConversion/ADC/Quantization.cpp
        signals/signalConversion/ADC/QuantizationRounded.cpp
        signals/signalConversion/ADC/QuantizationClipped.cpp
        signals/signalConversion/DAC/Reconstruction.cpp
        signals/signalConversion/DAC/ReconstructionZeroOrderHold.cpp
        signals/signalConversion/DAC/ReconstructionFirstOrderHold.cpp
        signals/signalConversion/DAC/ReconstructionSincBased.cpp
        signals/operations/SignalProcesor.cpp
        signals/filters/ConvolutionSignal.cpp
        signals/filters/CorrelationSignal.cpp
        signals/filters/LowPassFilter.cpp
        signals/filters/HighPassFilter.cpp
        signals/filters/BandPassFilter.cpp
        signals/simulation/SimulatedSignal.cpp
        signals/simulation/DistanceSensor.cpp
        signals/simulation/Environment.cpp
        signals/windows/Window.cpp
        signals/windows/HammingWindow.cpp
        signals/windows/HanningWindow.cpp
        signals/windows/BlackmanWindow.cpp
        signals/windows/RectangularWindow.cpp
        signals/complexSignals/ComplexSignal.cpp
        signals/complexSignals/DiscreteComplexSignalStatic.cpp
        signals/transformers/ComplexTransform.cpp
        signals/transformers/DiscreteCosineTransform.cpp
        signals/transformers/DiscreteFourierTransform.cpp
        signals/transformers/FastCosineTransform.cpp
        signals/transformers/DITFastFourierTransform.cpp
        signals/transformers/WalshHadamardTransform.cpp
        signals/transformers/FastWalshHadamardTransform.cpp
        signals/transformers/DIFFastFourierTransform.cpp
        signals/transformers/WaveletTransform.cpp
        signals/transformers/SignalTransformer.cpp
        signals/complexSignals/DiscreteComplexSignal.cpp

        frontend/Parameter.cpp
        frontend/MainApp.cpp
        frontend/SignalManagementComponent.cpp
        frontend/ConversionComponent.cpp
        frontend/ConvFilterCorComponent.cpp
        frontend/SimulationComponent.cpp
        frontend/Operation.cpp
        frontend/PlotComponent.cpp
        frontend/Component.cpp
        frontend/ComplexTransformerComponent.cpp
        bindings/imgui_impl_glfw.cpp
        bindings/imgui_impl_opengl3.cpp
        mediator/SignalMediator.cpp

        DEPENDS
        Python3::NumPy
        imgui::imgui
        glfw
        GLEW::glew_s
        implot::implot
        )

include_directories(bindings)

add_app(${PROJECT_NAME}
        run/main.cpp

        )

