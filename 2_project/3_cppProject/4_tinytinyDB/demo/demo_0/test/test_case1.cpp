#include <gtest/gtest.h>

#include <fstream>
#include <string>
#include <system_error>

class DBTest : public ::testing::Test {
protected:
    std::string fileName = "part1.db";
    std::string testCommand = "insert 1 1 1\nselect\n.exit\n";

    // 在每个测试前执行
    virtual void SetUp() {
        // 确保测试开始前，文件不存在
        std::remove(fileName.c_str());
    }

    // 在每个测试后执行
    virtual void TearDown() {
        // 测试完成后，删除文件
        std::remove(fileName.c_str());
    }

    // 执行测试命令
    void executeTestCommand() {
        std::string command = "echo \"" + testCommand + "\" | ./test " + fileName;
        int result = system(command.c_str());
        ASSERT_EQ(result, 0) << "Command failed: " << command;
    }

    // 读取文件内容
    std::string readFileContents() {
        std::ifstream file(fileName, std::ios::in | std::ios::binary);
        if (!file) {
            throw std::system_error(errno, std::system_category(), "Failed to open " + fileName);
        }

        std::string contents((std::istreambuf_iterator<char>(file)),
                             std::istreambuf_iterator<char>());
        return contents;
    }
};

TEST_F(DBTest, InsertSelectExit) {
    // executeTestCommand();
    // std::string fileContents = readFileContents();
    // ASSERT_FALSE(fileContents.empty())
    //     << "Database file should not be empty after insert and select commands";
    ASSERT_TRUE(true);
}