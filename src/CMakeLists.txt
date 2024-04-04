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
        signals/ADC/Sampling.cpp
        signals/ADC/Quantization.cpp
        signals/ADC/QuantizationRounded.cpp
        signals/ADC/QuantizationClipped.cpp
        signals/DAC/ReconstructionZeroOrderHold.cpp
        signals/DAC/ReconstructionFirstOrderHold.cpp
        signals/DAC/ReconstructionSincBased.cpp
        operations/SignalProcesor.cpp

        frontend/Option.cpp
        frontend/Parameter.cpp
        frontend/MainApp.cpp
        frontend/PlottingComponent.cpp
        frontend/AcConversionComponent.cpp
        frontend/Operation.cpp
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

