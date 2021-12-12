void stage1(std::queue<Matrix> &q1, std::queue<Matrix> &q2) {
    std::mutex m;

    m.lock();
    Matrix matrix = q1.front();
    m.unlock();

    matrix.minElem = matrix.getMinElem();

    m.lock();
    q2.push(matrix);
    m.unlock();

    m.lock();
    q1.pop();
    m.unlock();
}