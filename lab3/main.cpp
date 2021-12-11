#include <string>
#include <iostream>
#include <fstream>

#include <sys/types.h>
#include <unistd.h>

#include <functional>
#include <filesystem>


#include "inc/sorts.h"

//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/json_parser.hpp>

void test() {

}

void printRes(const std::function<void(std::vector<int> &)> &sort, std::vector<int> vec)
{
    sort(vec);
    for (auto &i: vec ) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
int interactive() {
    int x;
    std::cout << "Введите длину массива: ";
    std::cin >> x ;
    std::vector<int> vec;
    vec.resize(x);
    for (int & i : vec) {
        std::cin >> i;
    }

    std::cout << "Сортировка пузырьком: ";
    printRes(BubbleSort<int>, vec);
    std::cout << "Сортировка вставками: ";
    printRes(InsertSort<int>, vec);
    std::cout << "Сортировка  выбором: ";
    printRes(SelectSort<int>, vec);
}



struct params_t {
    bool help = false;
    bool test = false;
    bool benchmark = false;
    bool interact = false;
};

params_t params_parse(int argc, char *argv[]) {
    params_t params;

    if (argc != 2) {
        params.help = true;
        return params;
    }
    std::string mode = argv[1];
    if (mode == "-t" || mode == "--test") {
        params.test = true;
    }
    if (mode == "-i" || mode == "--interactive") {
        params.interact = true;
    }
    if (mode == "-b" || mode == "--benchmark") {
        params.benchmark = true;
    }

    return params;
};

void help(const char *p) {
    std::filesystem::path path = p;

    std::cout << "Испольщование: " << path.filename().string()
              << " [[-h | -t | -i | -b] | [--help | --test | --interactive || --benchmark]"
              << std::endl
              << "-h | --help  - показать справку" << std::endl
              << "-t | --test  - провести тестирование" << std::endl
              << "-i | --interactive  - запустить программу в ручном режиме" << std::endl
              << "-b | --benchmark  - провести нагрузочное тестирование" << std::endl;
}


std::vector<int> randomVector(int len) {
    std::vector<int> vector;
    vector.resize(len);

    srand((unsigned) time(NULL) * getpid());
    for (int i = 0; i < len; ++i) {
        vector[i] = rand();
    }

    return vector;
}

std::vector<int> sortedVector(int len) {
    std::vector<int> vector;
    vector.reserve(len);

    for (int i = 0; i < len; ++i) {
        vector.push_back(i);
    }

    return vector;
}
auto reSortedVector = [](int len) {
    auto vector = sortedVector(len);
    std::reverse(vector.begin(), vector.end());
    return vector;
};

struct BenchRes {
    int size;
    double time = -1;
};

void exportResults(const std::vector<BenchRes> &results, const std::string &path);

void benchmark(const std::function<void(std::vector<int> &)> &sort, const std::function<std::vector<int>(int)> &generator,
               const std::string &path, const std::vector<int> &values) {
    int counts = 100;


    std::vector<BenchRes> results;
    results.reserve(values.size());

    std::cout << "Генерируется отчет  " << path << std::endl;

    for (auto i: values) {
        BenchRes res;
        res.size = i;
        std::cout << i << "-";

        auto randomVector = generator(i);

        clock_t start;

        start = clock();
        for (int j = 0; j < counts; ++j) {
            std::vector<int> tmp = randomVector;
            sort(tmp);
        }
        res.time = double(clock() - start) / counts;

        results.push_back(res);
    }

    std::cout << "Done" << std::endl;


    exportResults(results, path);
}

void benchmark() {
    std::vector<int> values = {
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 50, 100, 200, 500, 1000
    };

    auto reSortedVector = [](int len) {
        auto vector = sortedVector(len);
        std::reverse(vector.begin(), vector.end());
        return vector;
    };

    benchmark(BubbleSort<int>, randomVector, "./bench_results/bubble_random.csv", values);
    benchmark(InsertSort<int>, randomVector, "./bench_results/insert_random.csv", values);
    benchmark(SelectSort<int>, randomVector, "./bench_results/select_random.csv", values);


    benchmark(BubbleSort<int>, sortedVector, "./bench_results/bubble_sorted.csv", values);
    benchmark(InsertSort<int>, sortedVector, "./bench_results/insert_sorted.csv", values);
    benchmark(SelectSort<int>, sortedVector, "./bench_results/select_sorted.csv", values);

    benchmark(BubbleSort<int>, reSortedVector, "./bench_results/bubble_resorted.csv", values);
    benchmark(InsertSort<int>, reSortedVector, "./bench_results/insert_resorted.csv", values);
    benchmark(SelectSort<int>, reSortedVector, "./bench_results/select_resorted.csv", values);



}

void exportResults(const std::vector<BenchRes> &results, const std::string &path) {
    std::ofstream finRL(path);
    if (!finRL) {
        std::cerr << "Can't open files";
    }

    finRL << "x;y" << std::endl;
    for (auto &res: results) {
        if (res.time < 0) continue;
        finRL << res.size << ";" << res.time << std::endl;
    }
}

int main(int argc, char *argv[]) {
    auto params = params_parse(argc, argv);

    if (params.help) {
        help(argv[0]);
    }

    if (params.test) {
        test();
    }
    if (params.interact) {
        interactive();
    }
    if (params.benchmark) {
        benchmark();
    }
    return 0;
}