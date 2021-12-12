#ifndef CONVEYOR_HPP
#define CONVEYOR_HPP

#include <iostream>
#include <queue>
#include <mutex>
#include <chrono>
#include <thread>

#include "color.h"

#define THREADS_COUNT 3

struct ResultTime {
    int task;
    int tape;

    double begin;
    double end;

    std::chrono::time_point<std::chrono::system_clock> timeBegin;
};


void linearProcessing(int rows, int cols, int count, bool print, bool compareTime);

void parallelProcessing(int rows, int cols, int count, bool print, bool compareTime);

#endif
