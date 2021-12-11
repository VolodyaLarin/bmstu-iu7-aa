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
