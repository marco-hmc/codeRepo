#include "../include/server.http.hpp"
#include <gtest/gtest.h>

TEST(ServerHttpTest, TestExample) {
  // 这里编写测试逻辑
  ASSERT_TRUE(true); // 示例断言
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}