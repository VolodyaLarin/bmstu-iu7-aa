#include <iostream>
#include "../inc/read.hpp"
#include "../inc/color.h"


void readNumberAction(int &action) {
    std::cout << YELLOW <<
              "\n\tМеню\n\n"
              "1. Линейная обработка\n"
              "2. Конвейерная обработка\n"
              "3. Замеры время\n"
              "0. Выход \n\n"
              "Выбор: "
              << BASE_COLOR;

    std::cin >> action;

    if (action < MIN_COMMAND_NUMBER || action > MAX_COMMAND_NUMBER)
        throw std::exception();
}


void readNumberRowsColumnsCount(int &n, int &m, int &cnt) {
    std::cout << BLUE << "\nВведите кол-во строк и столбцов матрицы: " << BASE_COLOR;

    std::cin >> n >> m;

    if (n <= 0 || m <= 0)
        throw std::exception();
    std::cout << GREEN << "\nВведите кол-во матриц: " << BASE_COLOR;

    std::cin >> cnt;

    if (cnt <= 0)
        throw std::exception();

    std::cout << "\n";

}
