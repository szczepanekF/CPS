find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(Python3 COMPONENTS NumPy REQUIRED)


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

        frontend/Option.cpp
        frontend/Parameter.cpp

        operations/SignalProcesor.cpp
        )

add_to_project_libs(Python3::NumPy)
add_to_project_libs(imgui::imgui)
add_to_project_libs(glfw)
add_to_project_libs(GLEW::glew_s)
add_to_project_libs(implot::implot)
include_directories(bindings)
add_app(${PROJECT_NAME}
        run/main.cpp
        bindings/imgui_impl_glfw.h
        bindings/imgui_impl_glfw.cpp
        bindings/imgui_impl_opengl3.h
        bindings/imgui_impl_opengl3.cpp)
