## Signal Processing Application



## Overview

This project is a sophisticated signal processing application designed to meet specific tasks, written in C++ and developed using the Clion IDE. The application features a comprehensive graphical user interface (GUI) created with the Dear ImGui module and visualizes data using the ImPlot library. It effectively manages windows and contexts with GLFW and performs high-quality graphics rendering using OpenGL.

## Features

- **Intuitive GUI**: Built with Dear ImGui for a user-friendly experience.
- **Dynamic Data Visualization**: Utilizes ImPlot for rendering plots and histograms.
- **File Operations**: Save and load signals in binary and text formats.
- **Signal Generation**: Generate signals sample signal types and perform mathematical operations on them (addidtion, subtraction, multiplication and division).
- **Signal Conversion (DAC/ADC)**: Perform sampling or quantization of generated signal, and reconstruct the signal with chosen method based on the performed sampling / quatization.
- **Signal Filtering, Convolution and Correlation visualisation**: Visualise result of operations like convolution / correlation of two sampled signals and filtering of sampled signal.
- **Distance sensor simulation based on correlation**: Simulate distance measuring operation based on correlation of probing and reflected signal.
- **Signal transformations**: Perform transformations on 3 predefined signals and compare time performance of the operations.
- **Design Pattern Implementations**: Implements Strategy, Mediator, and Singleton design patterns for efficient code management.

## Technical Details

- **Language**: C++
- **Development Environment**: Clion IDE
- **Libraries and Modules**:
  - **Dear ImGui**: GUI development
  - **ImPlot**: Plot and chart rendering
  - **GLFW**: Window and context management
  - **OpenGL**: Graphics rendering
  - **Conan**: Package management


## Requirements
- CMake 3.22.0
- Conan 2.1.0
- C++ 23
## Installation

1. **Clone the repository**:
    ```sh
    git clone https://github.com/szczepanekF/CPS
    cd CPS
    ```

2. **Build the project**:
    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```   

## Usage

### Main View
![cps 1](https://github.com/szczepanekF/CPS/assets/107700989/bdca167e-de2b-4746-b1c6-1a2091efa1ef)

To generate a signal:
1. Select the signal type from the "Signals and noises" section by checking the appropriate checkbox.
2. Set the required parameters in the "Parameters" section.
3. Click "Draw the plot" to render the signal.

To modify the histogram bins:
- Enter a value between 5 and 20 in the "Bins" field below the plot.

To toggle the visibility of a signal type:
- Click its representation in the legend.

To generate signal which is based on basic arithmetic operation performed on two other signals:
1. Check box "Signals operation".
2. Draw two signals that operation will be performed on.
3. Select on of 4 operations.

### File Operations

- **Save to File**: Enter a filename and click "Save to file".
- **Load from File**: Enter a filename and click "Load from file".
- **Load Text Signal**: Enter a filename and click "Load signal in text format".
- **Clear Loaded Signals**: Click "Unload files and clear signal".

### Signal Conversion and Reconstruction
![Sampling](https://github.com/szczepanekF/CPS/assets/107700989/7afc75c5-e71b-4adf-a1f8-d0ffc955b4e3)
![Sampled signal](https://github.com/szczepanekF/CPS/assets/107700989/c3fe3ffe-0c33-44f2-84a0-74f53fac1d7e)
![Reconstructed signal](https://github.com/szczepanekF/CPS/assets/107700989/e22ce00d-84b4-43f8-b419-b0701ef08ea5)


To start sampling or reconstruction of a continuous signal:
1. Draw the signal first.
2. Click on the "Signal conversion" tab.

In the "Signal conversion" section, you have three options:
- **Sampling**: Requires specifying the sampling frequency.
- **Quantization**: Requires specifying the sampling frequency and the number of quantization levels.

After generating samples, there are three signal reconstruction options:
- **Reconstruction Methods**: Only the sinc-based method requires specifying the parameter N.

Upon selecting a reconstruction method, the reconstructed signal will be displayed on the plot.



### Convolution correlation and filters
![correlation, convolution](https://github.com/szczepanekF/CPS/assets/107700989/d31e3fe9-a1f2-4eb5-88e5-cc933b03246f)

To perform correlation / convolution on 2 signals:
1. Draw the signal first.
2. Click on the "Signal conversion" tab.
3. Sample signal.
4. Click on the "Add to operations" button.
5. Go to first point and add second signal to operations
6. Click on the "Convolution, correlation and filters" tab.
7. Select correlation / convolution and click "Draw signal"



To filter a signal:
1. Draw the signal first.
2. Click on the "Signal conversion" tab.
3. Sample signal.
4. Click on the "Add to operations" button.
5. Click on the "Convolution, correlation and filters" tab.
6. Choose filter, pass parameters and click "Draw signal"

### Distance sensor simulation
Go to "Distance sensor simulation" tab, pass parameters and run the simulation
It is recommended to autofit all the plots right after starting the simmulation.



### Transformation Panel
![signal s3](https://github.com/szczepanekF/CPS/assets/107700989/eb761d88-9b3b-4715-b43b-db7d397defb3)
![real and imaginary part](https://github.com/szczepanekF/CPS/assets/107700989/765d19a2-7ed1-4d73-b551-3e88c64de144)
![absoulte and phase part](https://github.com/szczepanekF/CPS/assets/107700989/2bd214d0-2c54-4313-8644-dca3d8aec99a)


To draw a signal:
- Click "Draw signal" in the "Signals" section.

To perform a transformation:
- Select the signal (S1, S2, or S3), choose the transformation type, and click "Draw transformation".

For complex signal values:
- Toggle the display mode between W1 and W2.
- Save/load complex values using "FileOperations".
- Clear the plot using "Clear signal".

## Contributions

Contributions are welcome! Please fork this repository and submit a pull request with your improvements.

## License

This project is licensed under the MIT License.

---

For further information, please refer to the detailed documentation provided within the repository.
