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
        Calculator.cpp
        )
add_to_project_libs(Python3::NumPy)
add_app(${PROJECT_NAME} run/main.cpp)
