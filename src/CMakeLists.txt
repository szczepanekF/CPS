find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(Python3 COMPONENTS NumPy REQUIRED)
find_package(imgui REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glew REQUIRED )
find_package(implot REQUIRED)

add_lib(src
        SOURCES
        signals/ContinousSignal.cpp
        signals/DiscreteSignal.cpp
        signals/GaussianNoise.cpp
        signals/ImpulseNoise.cpp
        signals/RectangularSignal.cpp
        signals/RectangularSymmetricSignal.cpp
        signals/SignalStrategy.cpp
        signals/SinusoidalSignal.cpp
        signals/SinusoidalOneHalfRectifiedSignal.cpp
        signals/SinusoidalTwoHalfRectifiedSignal.cpp
        signals/TriangularSignal.cpp
        signals/UniformNoise.cpp
        signals/UnitImpulseSignal.cpp
        signals/UnitJumpSignal.cpp
        signals/Signal.cpp
        operations/SignalProcesor.cpp

        frontend/Option.cpp
        frontend/Parameter.cpp


        frontend/MainApp.cpp
        frontend/PlottingComponent.cpp

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

