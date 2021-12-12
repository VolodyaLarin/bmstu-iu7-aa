
#include <iostream>

#include "inc/color.h"
#include "inc/read.hpp"
#include "inc/conveyor.hpp"
#include "inc/compare.hpp"

int main() {
    int rows, columns, count, action = -1;

    while (action) {
        try {
            readNumberAction(action);

            if (action == 1) {
                readNumberRowsColumnsCount(rows, columns, count);

                linearProcessing(rows, columns, count, false, false);
            } else if (action == 2) {
                readNumberRowsColumnsCount(rows, columns, count);

                parallelProcessing(rows, columns, count, false, false);
            } else if (action == 3) {
                compareTime();
            }
        }
        catch (std::exception &error) {
            std::cout << RED << error.what() << BASE_COLOR << std::endl;
        }
    }


    return 0;
}
