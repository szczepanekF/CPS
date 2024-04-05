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
        signals/signalConversion/ADC/Sampling.cpp
        signals/signalConversion/ADC/Quantization.cpp
        signals/signalConversion/ADC/QuantizationRounded.cpp
        signals/signalConversion/ADC/QuantizationClipped.cpp
        signals/signalConversion/DAC/ReconstructionZeroOrderHold.cpp
        signals/signalConversion/DAC/ReconstructionFirstOrderHold.cpp
        signals/signalConversion/DAC/ReconstructionSincBased.cpp
        operations/SignalProcesor.cpp
        
        frontend/Parameter.cpp
        frontend/MainApp.cpp
        frontend/SignalManagementComponent.cpp
        frontend/ConversionComponent.cpp
        frontend/Operation.cpp
        frontend/PlotComponent.cpp

        bindings/imgui_impl_glfw.cpp
        bindings/imgui_impl_opengl3.cpp

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

