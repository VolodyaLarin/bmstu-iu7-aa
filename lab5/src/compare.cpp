#include "../inc/compare.hpp"
#include "../inc/matrix.hpp"
#include "../inc/conveyor.hpp"


void compareTime(void) {
    std::cout << BLUE <<
              "\nЗависимость времени от кол-ва матриц для Конвейерной обработки\n\n"
              << BASE_COLOR;

    printf(" Размер матриц %s|%s Кол-во матриц %s|%s  Время конца  \n"
           "%s-----------------------------------------------\n%s",
           PURPLE, BASE_COLOR, PURPLE, BASE_COLOR, PURPLE, BASE_COLOR);

    for (int i = 50; i < 5000; i *= 2) {
        parallelProcessing(100, 100, i, false, true);
    }


    std::cout << BLUE <<
              "\nЗависимость времени от кол-ва матриц для Линейной обработки\n\n"
              << BASE_COLOR;

    printf(" Размер матриц %s|%s Кол-во матриц %s|%s  Время конца  \n"
           "%s-----------------------------------------------\n%s",
           PURPLE, BASE_COLOR, PURPLE, BASE_COLOR, PURPLE, BASE_COLOR);

    for (int i = 50; i < 5000; i *= 2) {
        linearProcessing(100, 100, i, false, true);
    }


    std::cout << GREEN <<
              "\nЗависимость времени от размера матриц для Конвейерной обработки\n\n"
              << BASE_COLOR;

    printf(" Размер матриц %s|%s Кол-во матриц %s|%s  Время конца  \n"
           "%s-----------------------------------------------\n%s",
           PURPLE, BASE_COLOR, PURPLE, BASE_COLOR, PURPLE, BASE_COLOR);

    for (int i = 20; i < 1000; i *= 2) {
        parallelProcessing(i, i, 100, false, true);
    }


    std::cout << GREEN <<
              "\nЗависимость времени от размера матриц для Линейной обработки\n\n"
              << BASE_COLOR;

    printf(" Размер матриц %s|%s Кол-во матриц %s|%s  Время конца  \n"
           "%s-----------------------------------------------\n%s",
           PURPLE, BASE_COLOR, PURPLE, BASE_COLOR, PURPLE, BASE_COLOR);

    for (int i = 20; i < 1000; i *= 2) {
        linearProcessing(i, i, 100, false, true);
    }
}
