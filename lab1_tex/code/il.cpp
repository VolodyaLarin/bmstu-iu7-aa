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