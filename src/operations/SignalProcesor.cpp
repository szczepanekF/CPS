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
    double amp = strategy->getAmplitude();
    outFile.write(reinterpret_cast<const char *>(&amp), sizeof(amp));
    double bTime = strategy->getBeginTime();
    outFile.write(reinterpret_cast<const char *>(&bTime), sizeof(bTime));
    double dur = strategy->getDuration();
    outFile.write(reinterpret_cast<const char *>(&dur), sizeof(dur));
    int sampleCount = strategy->getSampleCount();
    outFile.write(reinterpret_cast<const char *>(&sampleCount), sizeof(sampleCount));

    // Write size of vectors
    size_t sizeX = sig.size();
    outFile.write(reinterpret_cast<const char *>(&sizeX), sizeof(sizeX));
    outFile.write(reinterpret_cast<const char *>(&sizeX), sizeof(sizeX));

    // Write the data of the vectors
    outFile.write(reinterpret_cast<const char *>(sig.signalValues.data()), sizeX * sizeof(double));
    outFile.write(reinterpret_cast<const char *>(sig.timeValues.data()), sizeX * sizeof(double));

    // Close the file
    outFile.close();

    std::cout << "Vectors saved to file successfully." << std::endl;
}

SignalStrategy *SignalProcesor::readSignalFromBinary(const std::string &filename) {
    std::ifstream inFile(filename, std::ios::in | std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Error opening file for reading!" << std::endl;
        return nullptr;
    }
    double amp, bTime, dur;
    int sampleCount;
    inFile.read(reinterpret_cast< char *>(&amp), sizeof(amp));
    inFile.read(reinterpret_cast< char *>(&bTime), sizeof(bTime));
    inFile.read(reinterpret_cast< char *>(&dur), sizeof(dur));
    inFile.read(reinterpret_cast< char *>(&sampleCount), sizeof(sampleCount));
    // Read the size of the vectors
    size_t sizeX, sizeY;
    inFile.read(reinterpret_cast<char *>(&sizeX), sizeof(sizeX));
    inFile.read(reinterpret_cast<char *>(&sizeY), sizeof(sizeY));

    Signal newSignal;
    // Resize vectors to fit the read data
    newSignal.signalValues.resize(sizeX);
    newSignal.timeValues.resize(sizeY);

    // Read the data of the vectors
    inFile.read(reinterpret_cast<char *>(newSignal.signalValues.data()), sizeX * sizeof(double));
    inFile.read(reinterpret_cast<char *>(newSignal.timeValues.data()), sizeY * sizeof(double));

    // Close the file
    inFile.close();
    SignalStrategy* newStrat = new SignalStrategy(amp,bTime, dur);
    newStrat->setSampleCount(sampleCount);
    newStrat->setSignal(newSignal);
    return newStrat;
}





