void parallelStage2(std::queue<Matrix> &q2, std::queue<Matrix> &q3,
                    std::vector<ResultTime> &timeResultArr,
                    std::vector<MatrixState> &matrixStateArr,
                    bool &q1IsEmpty, bool &q2IsEmpty) {
    std::chrono::time_point<std::chrono::system_clock> timeStart, timeEnd;
    int taskNum = 1;

    while (true) {
        if (!q2.empty()) {
            if (matrixStateArr[taskNum - 1].stage_1) {
                timeStart = std::chrono::system_clock::now();
                stage2(std::ref(q2), std::ref(q3));
                timeEnd = std::chrono::system_clock::now();

                saveResult(timeResultArr, timeStart, timeEnd, timeResultArr[0].timeBegin, taskNum, 2);

                matrixStateArr[taskNum - 1].stage_2 = true;
                taskNum++;
            }
        } else if (q1IsEmpty) {
            break;
        }
    }

    q2IsEmpty = true;
}