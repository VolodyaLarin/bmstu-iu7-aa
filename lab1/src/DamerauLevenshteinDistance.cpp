//
// Created by volodya on 09.10.2021.
//

#include <algorithm>
#include <vector>
#include "../inc/DamerauLevenshteinDistance.h"


int rec_dl(const std::string &left, const std::string &right, const int i, const int j) {

    if (std::min(i, j) == 0) {
        return std::max(i, j);
    }

    int m = left[i - 1] == right[j - 1] ? 0 : 1;

    int res = std::min({
            rec_dl(left, right, i, j - 1) + 1,
            rec_dl(left, right, i - 1, j) + 1,
            rec_dl(left, right, i - 1, j - 1) + m
    });
    if (i > 1 && j > 1 && left[i - 1] == right[j - 2] && left[i - 2] == right[j - 1]) {
        res = std::min(res, rec_dl(left, right, i - 2, j - 2) + 1);
    }

    return res;
}

int rec_dl(const std::string &left, const std::string &right) {
    return rec_dl(left, right, left.size(), right.size());
}