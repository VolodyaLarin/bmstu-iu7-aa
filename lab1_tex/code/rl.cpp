int rec_l(const std::string &left, const std::string &right, const int i, const int j) {
    if (std::min(i, j) == 0) {
        return std::max(i, j);
    }

    int m = left[i - 1] == right[j - 1] ? 0 : 1;

    return std::min({
            rec_l(left, right, i, j - 1) + 1,
            rec_l(left, right, i - 1, j) + 1,
            rec_l(left, right, i - 1, j - 1) + m
    });
}