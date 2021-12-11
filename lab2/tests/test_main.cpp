#include <gtest/gtest.h>
#include <iostream>

int test() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}