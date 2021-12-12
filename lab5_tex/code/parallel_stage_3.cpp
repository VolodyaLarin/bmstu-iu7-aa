void parallelStage3(std::queue<Matrix> &q3,
                    std::vector<ResultTime> &time_result_arr,
                    std::vector<MatrixState> &matrixStateArr,
                    bool &q2IsEmpty, int cntMatr, bool matrIsPrint) {
    std::chrono::time_point<std::chrono::system_clock> timeStart, timeEnd;
    int taskNum = 1;

    while (true) {
        if (!q3.empty()) {
            if (matrixStateArr[taskNum - 1].stage_2) {
                timeStart = std::chrono::system_clock::now();
                stage3(std::ref(q3), taskNum, cntMatr, matrIsPrint);
                timeEnd = std::chrono::system_clock::now();

                saveResult(time_result_arr, timeStart, timeEnd, time_result_arr[0].timeBegin, taskNum, 3);

                matrixStateArr[taskNum - 1].stage_3 = true;
                taskNum++;
            }
        } else if (q2IsEmpty) {
            break;
        }
    }
}
