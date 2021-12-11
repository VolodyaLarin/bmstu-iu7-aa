std::vector<int> randomVector(int len) {
    std::vector<int> vector;
    vector.resize(len);

    srand((unsigned) time(NULL) * getpid());
    for (int i = 0; i < len; ++i) {
        vector[i] = rand();
    }

    return vector;
}

std::vector<int> sortedVector(int len) {
    std::vector<int> vector;
    vector.reserve(len);

    for (int i = 0; i < len; ++i) {
        vector.push_back(i);
    }

    return vector;
}

auto reSortedVector = [](int len) {
    auto vector = sortedVector(len);
    std::reverse(vector.begin(), vector.end());
    return vector;
};