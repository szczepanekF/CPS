#include <utility>
#include <fstream>
#include <iostream>
#include "operations/SignalProcesor.h"

SignalProcesor::SignalProcesor() : signalValues() {

}


Signal SignalProcesor::getCalculatedSignal(std::string &operationType) {
    if (signalValues.empty()) return {};
    Signal value = signalValues[0];

    for (size_t i = 1; i < signalValues.size() - 1 ; i++) {
        value = calculateSignalOperation(operationType, value, signalValues[i]);
    }

    return value;
}


Signal SignalProcesor::calculateSignalOperation(std::string &operationType, const Signal &firstSig,
                                                const Signal &secondSig) {
    if (operationType == "add") {
        return firstSig + secondSig;
    } else if (operationType == "subtract") {
        return firstSig - secondSig;
    } else if (operationType == "multiply") {
        return firstSig * secondSig;
    } else if (operationType == "divide") {

        return firstSig / secondSig;
    }
    return firstSig;
}


void SignalProcesor::removeSignal(int i) {
    signalValues.erase(signalValues.begin() + i);
}

void SignalProcesor::addNewSignal(const Signal &signal) {
    signalValues.push_back(signal);
}

void SignalProcesor::saveSignalToBinary(const SignalStrategy& strat, const Signal &sig, const std::string &filename) {
    // Open a binary file for writing
    std::ofstream outFile(filename, std::ios::out | std::ios::binary | std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }
    //write parameters

    double bTime = strat.getBeginTime();
    outFile.write(reinterpret_cast<const char *>(&bTime), sizeof(bTime));
    double dur = strat.getDuration();
    outFile.write(reinterpret_cast<const char *>(&dur), sizeof(dur));
    double frequency = strat.getFrequency();
    outFile.write(reinterpret_cast<const char *>(&frequency), sizeof(frequency));

    size_t sizeX = sig.size();
    outFile.write(reinterpret_cast<const char *>(&sizeX), sizeof(sizeX));

    outFile.write(reinterpret_cast<const char *>(sig.signalValues.data()), sizeX * sizeof(double));


    // Close the file
    outFile.close();

    std::cout << "Vectors saved to file successfully." << std::endl;
}

std::unique_ptr<Signal> SignalProcesor::readSignalFromBinary(const std::string &filename) {
    std::ifstream inFile(filename, std::ios::in | std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Error opening file for reading!" << std::endl;
        return {};
    }
    std::unique_ptr<Signal> newSignal = std::make_unique<Signal>();
    double bTime, dur;
    double frequency;
    inFile.read(reinterpret_cast< char *>(&bTime), sizeof(bTime));
    inFile.read(reinterpret_cast< char *>(&dur), sizeof(dur));
    inFile.read(reinterpret_cast< char *>(&frequency), sizeof(frequency));
    // Read the size of the vectors
    size_t sizeX;
    inFile.read(reinterpret_cast<char *>(&sizeX), sizeof(sizeX));



    // Read the data of the vectors
    std::vector<double> tmp;
    inFile.read(reinterpret_cast<char *>(tmp.data()), sizeX * sizeof(double));
    // Resize vectors to fit the read data
    newSignal->signalValues = tmp;
    newSignal->timeValues.resize(sizeX);

    double diff = 1 / frequency;
    double time = bTime;
    int i = 0;
    std::cout<<"debug2";

    while (time <= bTime + dur) {
        newSignal->timeValues[i] = time;
        time += diff;
        i ++;
    }

    std::cout<<"debug3";


    // Close the file
    inFile.close();

    return newSignal;
}

std::string SignalProcesor::readSignalFromBinaryAsString(const std::string &filename) {
    std::string message = "Data read from file\n";
    std::ifstream inFile(filename, std::ios::in | std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Error opening file for reading!" << std::endl;
        return {};
    }
    double bTime, dur;
    double frequency;
    inFile.read(reinterpret_cast< char *>(&bTime), sizeof(bTime));
    inFile.read(reinterpret_cast< char *>(&dur), sizeof(dur));
    inFile.read(reinterpret_cast< char *>(&frequency), sizeof(frequency));
    // Read the size of the vectors
    size_t sizeX;
    inFile.read(reinterpret_cast<char *>(&sizeX), sizeof(sizeX));
    message += "Time 0: " + std::to_string(bTime) + "\n";
    message += "Duration: " + std::to_string(dur) + "\n";
    message += "Sample count: " + std::to_string(frequency) + "\n";
    message += "Amplitude amount: " + std::to_string(sizeX) + "\n";
    message += "REST DATA IS AMPLITUDE VALUES";

    // Close the file
    inFile.close();

    return message;
}





