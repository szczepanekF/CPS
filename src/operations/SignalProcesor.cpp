#include <utility>
#include <fstream>
#include <iostream>
#include "operations/SignalProcesor.h"

SignalProcesor::SignalProcesor(std::unique_ptr<SignalStrategy> signalStrategy) : strategy(std::move(signalStrategy)),
                                                                                 signalValues() {

}


Signal SignalProcesor::getCalculatedSignal(std::string &operationType) {
    Signal baseSignal = strategy->getSignal();
    Signal value;
    value.timeValues = baseSignal.timeValues;
    value.signalValues = baseSignal.signalValues;

    for (auto &sig: signalValues) {
        value = calculateSignalOperation(operationType, value, sig);
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

}


void SignalProcesor::removeSignal(int i) {
    signalValues.erase(signalValues.begin() + i);
}

void SignalProcesor::addNewSignal(const Signal &signal) {
    signalValues.push_back(signal);
}

void SignalProcesor::saveSignalToBinary(const Signal &sig, const std::string &filename) {
    // Open a binary file for writing
    std::ofstream outFile(filename, std::ios::out | std::ios::binary | std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }
    //write parameters

    double bTime = strategy->getBeginTime();
    outFile.write(reinterpret_cast<const char *>(&bTime), sizeof(bTime));
    double dur = strategy->getDuration();
    outFile.write(reinterpret_cast<const char *>(&dur), sizeof(dur));
    int sampleCount = strategy->getSampleCount();
    outFile.write(reinterpret_cast<const char *>(&sampleCount), sizeof(sampleCount));

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
    int sampleCount;
    inFile.read(reinterpret_cast< char *>(&bTime), sizeof(bTime));
    inFile.read(reinterpret_cast< char *>(&dur), sizeof(dur));
    inFile.read(reinterpret_cast< char *>(&sampleCount), sizeof(sampleCount));
    // Read the size of the vectors
    size_t sizeX;
    inFile.read(reinterpret_cast<char *>(&sizeX), sizeof(sizeX));



    // Read the data of the vectors
    inFile.read(reinterpret_cast<char *>(newSignal->signalValues.data()), sizeX * sizeof(double));
    // Resize vectors to fit the read data
    newSignal->signalValues.resize(sizeX);
    newSignal->timeValues.resize(sizeX);
    double diff = dur / sampleCount;
    double time = bTime;
    int i = 0;
    while (time < bTime + dur) {
        newSignal->timeValues[i] = time;
        time += diff;
        i ++;
    }

    // Close the file
    inFile.close();

    return std::move(newSignal);
}





