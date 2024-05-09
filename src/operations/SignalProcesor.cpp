#include <utility>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <ranges>
#include "operations/SignalProcesor.h"

SignalProcesor::SignalProcesor() : signalValues() {

}


Signal SignalProcesor::getCalculatedSignal(std::string &operationType) {
    if (signalValues.empty()) return {};
    Signal value = signalValues[0];

    for (size_t i = 1; i < signalValues.size(); i++) {
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


void SignalProcesor::addNewSignal(const Signal &signal) {
    signalValues.push_back(signal);
}

void SignalProcesor::saveSignalToBinary(const Signal &sig, const std::string &filename) {
    if (sig.empty()) {
        throw std::logic_error("Signal empty");
    }

    std::ofstream outFile(filename, std::ios::out | std::ios::binary | std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    double bTime = sig.getTimeValues().front();
    double dur = sig.getTimeValues().back() - sig.getTimeValues().front();
    double frequency = 0;

    outFile.write(reinterpret_cast<const char *>(&bTime), sizeof(bTime));
    outFile.write(reinterpret_cast<const char *>(&dur), sizeof(dur));
    double time = bTime + 1;
    frequency = std::distance(sig.getTimeValues().begin(),
                              std::ranges::find_if(sig.getTimeValues(), [time](double val) { return time <= val; }));
    outFile.write(reinterpret_cast<const char *>(&frequency), sizeof(frequency));

    size_t sizeX = sig.size();
    outFile.write(reinterpret_cast<const char *>(&sizeX), sizeof(sizeX));

    outFile.write(reinterpret_cast<const char *>(sig.getSignalValues().data()), sizeX * sizeof(double));

    outFile.close();
}

std::unique_ptr<Signal> SignalProcesor::readSignalFromBinary(const std::string &filename) {
    std::ifstream inFile(filename, std::ios::in | std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Error opening file for reading!" << std::endl;
        return {};
    }
    std::unique_ptr<Signal> newSignal = std::make_unique<Signal>();
    double bTime;
    double dur;
    double frequency;
    size_t sizeX;

    inFile.read(reinterpret_cast< char *>(&bTime), sizeof(bTime));
    inFile.read(reinterpret_cast< char *>(&dur), sizeof(dur));
    inFile.read(reinterpret_cast< char *>(&frequency), sizeof(frequency));
    inFile.read(reinterpret_cast< char *>(&sizeX), sizeof(sizeX));

    std::vector<double> sigVals(sizeX);
    std::vector<double> timeVals(sizeX);
    inFile.read(reinterpret_cast<char *>(sigVals.data()), sizeX * sizeof(double));
    inFile.close();


    double diff = 1 / frequency;
    double time = bTime;
    int i = 0;
    while (time <= bTime + dur) {
        timeVals[i] = time;
        time += diff;
        i++;
    }

    newSignal->setValues(sigVals, timeVals);
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
    size_t sizeX;
    inFile.read(reinterpret_cast<char *>(&sizeX), sizeof(sizeX));
    message += "Time 0: " + std::to_string(bTime) + "\n";
    message += "Duration: " + std::to_string(dur) + "\n";
    message += "Frequency: " + std::to_string(frequency) + "\n";
    message += "Amplitude amount: " + std::to_string(sizeX) + "\n";
    message += "REST DATA IS AMPLITUDE VALUES";

    inFile.close();

    return message;
}

void SignalProcesor::clearSignals() {
    signalValues.clear();
}





