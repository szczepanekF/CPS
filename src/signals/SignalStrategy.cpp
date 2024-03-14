#include "signals/SignalStrategy.h"

SignalStrategy::SignalStrategy(double amp, double time0, double dur): SAMPLE_COUNT(10000), duration(dur), beginTime(time0), amplitude(amp) {
}

double SignalStrategy::getAmplitude() const {
    return amplitude;
}

double SignalStrategy::getBeginTime() const {
    return beginTime;
}

double SignalStrategy::getDuration() const {
    return duration;
}

//void SignalStrategy::saveToFile(const std::string &filename) {
//    // Open a binary file for writing
//    std::ofstream outFile(filename, std::ios::out | std::ios::binary | std::ios::trunc);
//    if (!outFile.is_open()) {
//        std::cerr << "Error opening file for writing!" << std::endl;
//        return;
//    }
//
//    // Write the size of the vectors
//    size_t sizeX = xData.size();
//    size_t sizeY = yData.size();
//    outFile.write(reinterpret_cast<const char *>(&sizeX), sizeof(sizeX));
//    outFile.write(reinterpret_cast<const char *>(&sizeY), sizeof(sizeY));
//
//    // Write the data of the vectors
//    outFile.write(reinterpret_cast<const char *>(xData.data()), sizeX * sizeof(double));
//    outFile.write(reinterpret_cast<const char *>(yData.data()), sizeY * sizeof(double));
//
//    // Close the file
//    outFile.close();
//
//    std::cout << "Vectors saved to file successfully." << std::endl;
//}
//
//SignalStrategy &SignalStrategy::readFromFile(const std::string &path) {
//    return <#initializer#>;
//}

Signal& SignalStrategy::getSignal() {

    return signal;
}

void SignalStrategy::calculateSignal() {
    double diff = getDuration() / SAMPLE_COUNT;
    double time = getBeginTime();
    while (time < getBeginTime() + getDuration()) {
        signal.signalValues.push_back(calculateSignalAt(time));
        signal.timeValues.push_back(time);
        time += diff;
    }
}

double SignalStrategy::calculateSignalAt(double) {
    return 0;
}

int SignalStrategy::getSampleCount() const {
    return SAMPLE_COUNT;
}

void SignalStrategy::setSignal(const Signal &signal) {
    SignalStrategy::signal = signal;
}

void SignalStrategy::setSampleCount(int sampleCount) {
    SAMPLE_COUNT = sampleCount;
}



