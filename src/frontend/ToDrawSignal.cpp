
#include "frontend/ToDrawSignal.h"

float *ToDrawSignal::getXData() const {
    return xData;
}

float *ToDrawSignal::getYData() const {
    return yData;
}

int ToDrawSignal::getDataSize() const {
    return dataSize;
}

int ToDrawSignal::getBins() const {
    return bins;
}

ToDrawSignal::ToDrawSignal(float *xData, float *yData, int dataSize, int bins, std::string name) : xData(xData), yData(yData),
                                                                                 dataSize(dataSize), bins(bins), name(name) {}

const std::string &ToDrawSignal::getName() const {
    return name;
}
