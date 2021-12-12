#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <random>

#include "color.h"


struct Matrix {
    std::vector<std::vector<int>> buffer;

    int minElem = 0;
    int sumElem = 0;

    void print();

    Matrix(int n, int m, bool random = false);


    int getMinElem();

    void modByMinElem();

    int getSumElements();
};

struct MatrixState {
    bool stage_1 = false;
    bool stage_2 = false;
    bool stage_3 = false;
};


void initMatrixStateArr(std::vector<MatrixState> &matrixStateArr, int count);

#endif
