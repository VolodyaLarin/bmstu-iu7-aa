//
// Created by volodya on 11.10.2021.
//

#include <vector>

template<class T>
void BubbleSort(std::vector<T> &vector) {
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
void InsertSort(std::vector<T> &arr) {
    T key;
    int n = arr.size();

    for (int i = 1; i < n; i++) {
        key = arr[i];
        auto j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

template<class T>
void SelectSort(std::vector<T> &vector) {
    auto size = vector.size();
    for (size_t i = 0; i < size; ++i) {
        size_t minI = i;
        for (auto j = i; j < size; ++j) {
            if (vector[j] < vector[minI]) {
                minI = j;
            }
        }
        std::swap(vector[i], vector[minI]);
    }
}