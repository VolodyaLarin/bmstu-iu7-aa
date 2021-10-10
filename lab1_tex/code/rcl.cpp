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

int Rec_Mem_l::_step(int i, int j) {

    int temp = _buffer[i][j];
    if (temp != NoData) {
        return temp;
    }

    temp = __step(i, j);
    _buffer[i][j] = temp;
    return temp;

}

int Rec_Mem_l::__step(int i, int j) {

    if (std::min(i, j) == 0) {
        return std::max(i, j);
    }

    int m = _left[i - 1] == _right[j - 1] ? 0 : 1;
    std::initializer_list<int> res = {
            _step(i, j - 1) + 1,
            _step(i - 1, j) + 1,
            _step(i - 1, j - 1) + m
    };

    return std::min(res);
}

int Rec_Mem_l::operator()(const std::string &left, const std::string &right) {
    _left = left;
    _right = right;

    int i = left.size(), j = right.size();
    _buffer.resize(i + 1);
    for (auto &row: _buffer) {
        row.resize(j + 1);
        for (auto &el: row) {
            el = NoData;
        }
    }

    return _step(i, j);
}
