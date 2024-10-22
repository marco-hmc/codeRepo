#include <gtest/gtest.h>

#include "../include/threadPool.h"

TEST(ThreadPoolTest, TestExample) { ASSERT_TRUE(true); }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}