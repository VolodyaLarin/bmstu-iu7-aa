//
// Created by volodya on 11.10.2021.
//

#include <vector>

template<class T>
void BubbleSort(std::vector<T> vector) {
    auto size = vector.size();
    for (size_t i = 0; i < size - 1; ++i) {
        for (size_t j = i + 1; j < size; ++j) {
            if (vector[i] > vector[j]) {
                std::swap(vector[i], vector[j]);
            }
        }
    }
}


template<class T>
void InsertSort(std::vector<T> vector) {
    auto size = vector.size();
    for (size_t i = 0; i < size; ++i) {
        auto x = vector[i];
        size_t j;
        for (j = i; j > 0 && vector[j - 1] > x; --j) {
            if (vector[i] > vector[j]) {
                vector[j] = vector[j - 1];
            }
        }
        vector[j] = x;
    }
}

template<class T>
void SelectSort(std::vector<T> vector) {
    auto size = vector.size();
    for (size_t i = 0; i < size; ++i) {
        size_t minI = i;
        for (auto j = i; j < size; ++j) {
            if (vector[i] < vector[minI]) {
                minI = j;
            }
        }
        std::swap(vector[i], vector[minI]);
    }
}