find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(Python3 COMPONENTS NumPy REQUIRED)


add_lib(src
        SOURCES
        signals/SignalStrategy.cpp
        signals/UniformNoise.cpp
        signals/GaussianNoise.cpp
        signals/ImpulseNoise.cpp
        signals/SquareSignal.cpp
        signals/SinusoidalSignal.cpp
        )
add_to_project_libs(Python3::NumPy)
add_app(${PROJECT_NAME} run/main.cpp)
