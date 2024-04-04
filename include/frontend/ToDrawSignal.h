#include "string"

class ToDrawSignal {

public:
    ToDrawSignal(float *xData, float *yData, int dataSize, int bins, std::string name);

    float *getXData() const;

    float *getYData() const;

    int getDataSize() const;

    int getBins() const;

    const std::string &getName() const;

private:
    float* xData;
    float* yData;
    int dataSize;
    int bins;
    std::string name;
};
