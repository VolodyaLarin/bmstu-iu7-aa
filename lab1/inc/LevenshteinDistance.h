
//
// Created by volodya on 09.10.2021.
//

#ifndef LAB1_LEVENSHTEINDISTANCE_H
#define LAB1_LEVENSHTEINDISTANCE_H

#include <string>
#include <vector>
#include <algorithm>

int rec_l(const std::string &left, const std::string &right);


class Rec_Mem_l {
    const int NoData = -1;

    std::vector<std::vector<int>> _buffer;
    std::string _left;
    std::string _right;

    int _step(int i, int j);

    int __step(int i, int j);

public:
    int operator()(const std::string &left, const std::string &right);
};


int iter_l(const std::string &left, const std::string &right) ;

#endif //LAB1_LEVENSHTEINDISTANCE_H
