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
