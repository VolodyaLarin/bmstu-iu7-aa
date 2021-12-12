void parallelStage1(std::queue<Matrix> &q1, std::queue<Matrix> &q2,
                    std::vector<ResultTime> &time_result_arr,
                    std::vector<MatrixState> &matrixStateArr,
                    bool &q1IsEmpty) {
    std::chrono::time_point<std::chrono::system_clock> timeStart, timeEnd;
    int taskNum = 1;

    while (!q1.empty()) {
        timeStart = std::chrono::system_clock::now();
        stage1(std::ref(q1), std::ref(q2));
        timeEnd = std::chrono::system_clock::now();

        saveResult(time_result_arr, timeStart, timeEnd, time_result_arr[0].timeBegin, taskNum, 1);

        matrixStateArr[taskNum - 1].stage_1 = true;
        taskNum++;
    }

    q1IsEmpty = true;
}