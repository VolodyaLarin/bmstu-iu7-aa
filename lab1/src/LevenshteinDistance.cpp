//
// Created by volodya on 09.10.2021.
//

#include "../inc/LevenshteinDistance.h"

int rec_l(const std::string &left, const std::string &right, const int i, const int j) {
    if (std::min(i, j) == 0) {
        return std::max(i, j);
    }

    int m = left[i - 1] == right[j - 1] ? 0 : 1;
    std::initializer_list<int> res = {
            rec_l(left, right, i, j - 1) + 1,
            rec_l(left, right, i - 1, j) + 1,
            rec_l(left, right, i - 1, j - 1) + m
    };

    return std::min(res);
}

int rec_l(const std::string &left, const std::string &right) {
    return rec_l(left, right, left.size(), right.size());
}


int Rec_Mem_l::_step(int i, int j) {

    int temp = _buffer[i][j];
    if (temp != NoData) {
        return temp;
    }

    temp = __step(i, j);
    _buffer[i][j] = temp;
    return temp;

}

int Rec_Mem_l::__step(int i, int j) {

    if (std::min(i, j) == 0) {
        return std::max(i, j);
    }

    int m = _left[i - 1] == _right[j - 1] ? 0 : 1;
    std::initializer_list<int> res = {
            _step(i, j - 1) + 1,
            _step(i - 1, j) + 1,
            _step(i - 1, j - 1) + m
    };

    return std::min(res);
}

int Rec_Mem_l::operator()(const std::string &left, const std::string &right) {
    _left = left;
    _right = right;

    int i = left.size(), j = right.size();
    _buffer.resize(i + 1);
    for (auto &row: _buffer) {
        row.resize(j + 1);
        for (auto &el: row) {
            el = NoData;
        }
    }

    return _step(i, j);
}

int iter_l(const std::string &left, const std::string &right) {
    int width = right.size();
    int height = left.size();
    std::vector<int> v1(width + 1);
    std::vector<int> v2(width + 1);

    for (size_t i = 0; i < width; i++) {
        v1[i] = i;
    }

    for (size_t i = 0; i < height; i++) {
        v2[0] = i + 1;
        for (size_t j = 0; j < width; j++) {
            int del = v1[j + 1] + 1;
            int ins = v2[j] + 1;
            int sub = v1[j];
            if (left[i] != right[j]) {
                sub++;
            }

            v2[j + 1] = std::min({del, ins, sub});
        }
        std::swap(v1, v2);
    }
    return v1[width];
}