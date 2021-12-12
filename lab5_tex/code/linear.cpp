void linearProcessing(int rows, int cols, int count, bool print, bool compareTime) {
    std::queue<Matrix> q1;
    std::queue<Matrix> q2;
    std::queue<Matrix> q3;

    std::mutex m;

    for (int i = 0; i < count; i++) {
        q1.push(Matrix(rows, cols, true));
    }

    std::vector<MatrixState> MatrixStateArr;
    initMatrixStateArr(MatrixStateArr, count);

    std::chrono::time_point<std::chrono::system_clock> timeStart, timeEnd,
            time_begin = std::chrono::system_clock::now();

    std::vector<ResultTime> time_result_arr;
    initTimeResultArr(time_result_arr, time_begin, count, THREADS_COUNT);

    for (int i = 0; i < count; i++) {
        timeStart = std::chrono::system_clock::now();
        stage1(std::ref(q1), std::ref(q2));
        timeEnd = std::chrono::system_clock::now();

        saveResult(time_result_arr, timeStart, timeEnd, time_begin, i + 1, 1);

        timeStart = std::chrono::system_clock::now();
        stage2(std::ref(q2), std::ref(q3));
        timeEnd = std::chrono::system_clock::now();

        saveResult(time_result_arr, timeStart, timeEnd, time_begin, i + 1, 2);

        timeStart = std::chrono::system_clock::now();
        stage3(std::ref(q3), i + 1, count, print);
        timeEnd = std::chrono::system_clock::now();

        saveResult(time_result_arr, timeStart, timeEnd, time_begin, i + 1, 3);
    }
}