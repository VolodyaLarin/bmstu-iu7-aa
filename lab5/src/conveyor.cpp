#include "../inc/conveyor.hpp"
#include "../inc/matrix.hpp"


void printResTime(std::vector<ResultTime> &time_result_arr, int size_arr) {
    printf("%s--------------------------------------------------------%s"
           "\n  № Матрицы  %s|%s   № Этапа  %s|%s Время начала %s|%s Время конца \n"
           "%s--------------------------------------------------------\n%s",
           PURPLE, BASE_COLOR, PURPLE, BASE_COLOR, PURPLE, BASE_COLOR,
           PURPLE, BASE_COLOR, PURPLE, BASE_COLOR);

    for (int i = 0; i < size_arr; i++) {
        printf("    %3d      %s|%s     %2d     %s|%s   %.6f   %s|%s   %.6f   \n",
               time_result_arr[i].task, PURPLE, BASE_COLOR,
               time_result_arr[i].tape, PURPLE, BASE_COLOR,
               time_result_arr[i].begin, PURPLE, BASE_COLOR,
               time_result_arr[i].end);

        if ((i + 1) % 3 == 0) {
            printf("%s--------------------------------------------------------\n%s",
                   PURPLE, BASE_COLOR);
        }
    }
}


void initTimeResultArr(std::vector<ResultTime> &time_result_arr,
                       std::chrono::time_point<std::chrono::system_clock> time_begin,
                       int cnt_matr, int cnt_threads) {
    int len = cnt_matr * cnt_threads;
    time_result_arr.resize(len);

    for (int i = 0; i < len; i++) {
        ResultTime time_res;
        time_res.timeBegin = time_begin;

        time_result_arr[i] = time_res;
    }

}


void saveResult(std::vector<ResultTime> &timeResultArr,
                std::chrono::time_point<std::chrono::system_clock> timeStart,
                std::chrono::time_point<std::chrono::system_clock> time_end,
                std::chrono::time_point<std::chrono::system_clock> timeBegin,
                int task_num, int numb_stage) {
    double beg_time = (std::chrono::duration_cast<std::chrono::nanoseconds>
            (timeStart - timeBegin).count()) / 1e9;

    double end_time = (std::chrono::duration_cast<std::chrono::nanoseconds>
            (time_end - timeBegin).count()) / 1e9;

    int index = (task_num - 1) * THREADS_COUNT + numb_stage - 1;

    timeResultArr[index].task = task_num;
    timeResultArr[index].tape = numb_stage;
    timeResultArr[index].begin = beg_time;
    timeResultArr[index].end = end_time;
}


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


void stage3(std::queue<Matrix> &q3, int taskNum, int cntMatr, bool matrIsPrint) {
    std::mutex m;

    m.lock();
    Matrix matrix = q3.front();
    m.unlock();

    matrix.sumElem = matrix.getSumElements();

    if (matrIsPrint && taskNum == cntMatr) {
        printf("\nmin_elem = %d\n\nМатрица после 2 этапа:\n", matrix.minElem);
        matrix.print();
        printf("\nsum_elem = %d\n\n", matrix.sumElem);
    }

    m.lock();
    q3.pop();
    m.unlock();
}


void linearProcessing(int rows, int cols, int count, bool print, bool compareTime) {
    std::queue<Matrix> q1;
    std::queue<Matrix> q2;
    std::queue<Matrix> q3;

    std::mutex m;

    for (int i = 0; i < count; i++) {
        Matrix matrix(rows, cols, true);
        q1.push(matrix);

        if (print && i == count - 1) {
            const std::lock_guard<std::mutex> lock(m);
            std::cout <<"Первоначальная матрица:" << std::endl;
            matrix.print();
        }
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

    if (compareTime) {
        printf("     %4d      %s|%s     %4d      %s|%s   %.6f  \n",
               rows, PURPLE, BASE_COLOR,
               count, PURPLE, BASE_COLOR,
               time_result_arr[count - 1].end);
    } else {
        printResTime(time_result_arr, count * THREADS_COUNT);
    }
}


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


void parallelProcessing(int rows, int cols, int count, bool print, bool compareTime) {
    std::queue<Matrix> q1;
    std::queue<Matrix> q2;
    std::queue<Matrix> q3;

    std::mutex m;

    for (int i = 0; i < count; i++) {
        Matrix matr (rows, cols, true);
        q1.push(matr);

        if (print && i == count - 1) {
            std::lock_guard<std::mutex> guard(m);
            printf("Первоначальная матрица:\n");
            matr.print();
        }
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

    if (compareTime) {
        printf("     %4d      %s|%s     %4d      %s|%s   %.6f  \n",
               rows, PURPLE, BASE_COLOR,
               count, PURPLE, BASE_COLOR,
               timeResultArr[count - 1].end);
    } else {
        printResTime(timeResultArr, count * THREADS_COUNT);
    }
}
