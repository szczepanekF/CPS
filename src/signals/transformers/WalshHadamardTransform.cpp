
#include <cmath>
#include <vector>
#include "signals/transformers/WalshHadamardTransform.h"

std::vector<double> WalshHadamardTransform::transform(std::vector<double> x) const{
    int N = x.size();
    int m = std::log2(N);
    std::vector<double> output(N, 0);
    std::vector<std::vector<double>> matrix(N, std::vector<double>(N, 0));
    fillWalshHadamardMatrix(matrix, m);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            output[i] += x[j] * matrix[i][j];
        }
    }
    return output;
}

void WalshHadamardTransform::fillWalshHadamardMatrix(std::vector<std::vector<double>> &H, int m) const  {
    if (m == 0) {
        H[0][0] = 1;
        return;
    }
    int size = (1 << m);
    int halfSize = size / 2;
    fillWalshHadamardMatrix(H, m - 1);
    for (int i = 0; i < halfSize; i++) {
        for (int j = 0; j < halfSize; j++) {
            H[i][j + halfSize] = H[i][j];
            H[i + halfSize][j] = H[i][j];
            H[i + halfSize][j + halfSize] = -H[i][j];
        }
    }
}
