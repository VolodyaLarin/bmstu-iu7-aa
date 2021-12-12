#include <algorithm>
#include "../inc/matrix.hpp"


void initMatrixStateArr(std::vector<MatrixState> &matrixStateArr, int count) {
    matrixStateArr.resize(count);

    for (auto &el: matrixStateArr) {
        el = MatrixState();
    }
}

void Matrix::print() {
    std::cout << PURPLE << std::endl;

    for (auto &row: buffer) {
        for (auto &el: row) {
            std::cout << el << " ";
        }
        std::cout << std::endl;

    }

    std::cout << BASE_COLOR;
}

Matrix::Matrix(int n, int m, bool random) {
    buffer.resize(n);

    for (auto &row: buffer) {
        row.resize(m);
    }

    if (random) {
        for (auto &row: buffer) {
            for (auto &el: row) {
                el = rand() % 90 + 10;
            }
        }
    }
}

int Matrix::getMinElem() {
    int minElement = buffer[0][0];

    for (auto &row: buffer) {
        auto rowMin = *std::min_element(row.begin(), row.end());
        if (minElement < rowMin) {
            minElement = rowMin;
        }
    }

    return minElement;
}

void Matrix::modByMinElem() {
    for (auto &row: buffer) {
        for (auto &el: row) {
            el %= minElem;
        }
    }
}

int Matrix::getSumElements() {
    int sum = 0;
    for (auto &row: buffer) {
        sum += std::accumulate(row.begin(), row.end(), 0);
    }
    return sum;
}
