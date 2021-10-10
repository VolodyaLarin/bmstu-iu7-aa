#include <string>
#include <iostream>
#include <filesystem>

#include "inc/LevenshteinDistance.h"
#include "inc/DamerauLevenshteinDistance.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

void test() {
    Rec_Mem_l rec_cached;

    boost::property_tree::ptree tests;
    boost::property_tree::read_json("./tests.json", tests);

    int counter = 0;
    for (auto &test: tests) {
        auto left = test.second.get<std::string>("left");
        auto right = test.second.get<std::string>("right");
        auto description = test.second.get<std::string>("description");
        auto l = test.second.get<int>("l");
        auto d = test.second.get<int>("dl");

        auto rl = rec_l(left, right);
        auto rcl = rec_cached(left, right);
        auto il = iter_l(left, right);
        auto dl = rec_dl(left, right);

        auto err = false;
        if (l != rl) {
            err = true;
            std::cout << "Rec L: returns: " << rl << std::endl;
        }

        if (l != rcl) {
            err = true;
            std::cout << "Rec CL: returns: " << rcl << std::endl;
        }

        if (l != il) {
            err = true;
            std::cout << "Iter L: returns: " << il << std::endl;
        }

        if (d != dl) {
            err = true;
            std::cout << "Damerau L: returns: " << dl << std::endl;
        }

        counter++;
        if (err) {
            std::cout << "TEST FAILED: left '" << left << "' right '" << right << "' ANSWER L: " << l << " D: " << d
                      << std::endl;
        } else {
            std::cout << "TEST #" << counter << " PASS: " << description << std::endl;
        }
    }
}

int interactive() {
    Rec_Mem_l rec_cached;

    std::string left, right;
    std::cout << "Введите два слова через пробел:" << std::endl;
    std::cin >> left >> right;
    std::cout << "Рекурсивный: " << rec_l(left, right) << std::endl;
    std::cout << "Рекурсивный с кэш-памятью: " << rec_cached(left, right) << std::endl;

    std::cout << "Итеративный: " << iter_l(left, right) << std::endl;
    std::cout << "Дамерау: " << rec_dl(left, right) << std::endl;
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

std::string randomString(int len) {
    std::string tmp_s;
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    srand((unsigned) time(NULL) * getpid());
    tmp_s.reserve(len);
    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

struct BenchRes {
    int size;
    double rl = -1;
    double rcl = -1;
    double il = -1;
    double dl = -1;
};

void exportResults(std::vector<BenchRes> results);

void benchmark() {
    Rec_Mem_l rec_cached;

    int counts = 10;

//    bool testRL = true, testRCL = true, testIL = true, testDL = true;
    std::vector<BenchRes> results;

    std::initializer_list<int> values = {
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 50, 100, 200
    };

    for (auto i: values) {
        std::cout << "Testing length " << i << std::endl;
        BenchRes res;
        res.size = i;

        auto left = randomString(i), right = randomString(i);

        clock_t start;
        if (i <= 15) {
            start = clock();
            for (int j = 0; j < counts; ++j) {
                rec_l(left, right);
            }
            res.rl = double(clock() - start) / counts;

            start = clock();
            for (int j = 0; j < counts; ++j) {
                rec_dl(left, right);
            }
            res.dl = double(clock() - start) / counts;

        }

        start = clock();
        for (int j = 0; j < counts; ++j) {
            rec_cached(left, right);
        }
        res.rcl = double(clock() - start) / counts;

        start = clock();
        for (int j = 0; j < counts; ++j) {
            iter_l(left, right);
        }
        res.il = double(clock() - start) / counts;


        results.push_back(res);
    }

    exportResults(results);
}

void exportResults(const std::vector<BenchRes> results) {
    std::ofstream finRL("./bench_results/rl.csv");
    std::ofstream finRCL("./bench_results/rcl.csv");
    std::ofstream finIL("./bench_results/il.csv");
    std::ofstream finDL("./bench_results/dl.csv");
    if (!finRL) {
        std::cerr << "Can't open files";
    }

    finRL << "x;y" << std::endl;
    for (auto &res: results) {
        if (res.rl < 0) continue;
        finRL << res.size << ";" << res.rl << std::endl;
    }

    finRCL << "x;y" << std::endl;
    for (auto &res: results) {
        if (res.rcl < 0) continue;
        finRCL << res.size << ";" << res.rcl << std::endl;
    }

    finIL << "x;y" << std::endl;
    for (auto &res: results) {
        if (res.il < 0) continue;
        finIL << res.size << ";" << res.il << std::endl;
    }

    finDL << "x;y" << std::endl;
    for (auto &res: results) {
        if (res.dl < 0) continue;
        finDL << res.size << ";" << res.dl << std::endl;
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