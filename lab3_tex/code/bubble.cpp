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
