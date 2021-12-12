void stage2(std::queue<Matrix> &q2, std::queue<Matrix> &q3) {
    std::mutex m;

    m.lock();
    Matrix matrix = q2.front();
    m.unlock();

    matrix.modByMinElem();

    m.lock();
    q3.push(matrix);
    m.unlock();

    m.lock();
    q2.pop();
    m.unlock();
}