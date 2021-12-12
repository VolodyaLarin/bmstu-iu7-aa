void parallelProcessing(int rows, int cols, int count, bool print, bool compareTime) {
    std::queue<Matrix> q1;
    std::queue<Matrix> q2;
    std::queue<Matrix> q3;

    std::mutex m;

    for (int i = 0; i < count; i++) {
        Matrix matr (rows, cols, true);
        q1.push(matr);
    }

    bool q1IsEmpty = false;
    bool q2IsEmpty = false;

    std::vector<MatrixState> matrixStateArr;
    initMatrixStateArr(matrixStateArr, count);

    std::chrono::time_point<std::chrono::system_clock> time_begin =
            std::chrono::system_clock::now();

    std::vector<ResultTime> timeResultArr;
    initTimeResultArr(timeResultArr, time_begin, count, THREADS_COUNT);

    std::thread threads[THREADS_COUNT];

    threads[0] = std::thread(parallelStage1, std::ref(q1), std::ref(q2), std::ref(timeResultArr),
                             std::ref(matrixStateArr), std::ref(q1IsEmpty));
    threads[1] = std::thread(parallelStage2, std::ref(q2), std::ref(q3), std::ref(timeResultArr),
                             std::ref(matrixStateArr), std::ref(q1IsEmpty), std::ref(q2IsEmpty));
    threads[2] = std::thread(parallelStage3, std::ref(q3), std::ref(timeResultArr), std::ref(matrixStateArr),
                             std::ref(q2IsEmpty), count, print);

    for (auto & thread : threads) {
        thread.join();
    }
}