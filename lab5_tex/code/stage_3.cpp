void stage3(std::queue<Matrix> &q3, int taskNum, int cntMatr, bool matrIsPrint) {
    std::mutex m;

    m.lock();
    Matrix matrix = q3.front();
    m.unlock();

    matrix.sumElem = matrix.getSumElements();

    m.lock();
    q3.pop();
    m.unlock();
}