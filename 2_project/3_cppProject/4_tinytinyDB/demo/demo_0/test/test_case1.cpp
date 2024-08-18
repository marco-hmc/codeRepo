#include <gtest/gtest.h>

#include <fstream>
#include <string>
#include <system_error>

class DBTest : public ::testing::Test {
protected:
    std::string fileName = "test.db";
    std::string initialCommands = "insert 1 1 1\ninsert 2 2 2\n.exit\n";
    std::string selectCommand = "select\n.exit\n";

    // 在每个测试前执行
    virtual void SetUp() {
        // 确保测试开始前，文件不存在
        std::remove(fileName.c_str());
        std::ofstream file(fileName, std::ios::out);
        if (!file) {
            throw std::system_error(errno, std::system_category(), "Failed to create " + fileName);
        }
        file.close();
    }

    // 在每个测试后执行
    virtual void TearDown() {
        // 测试完成后，删除文件
        std::remove(fileName.c_str());
    }

    // 执行测试命令
    void executeTestCommand(const std::string& command) {
        std::string fullCommand = "echo \"" + command + "\" | ../demo_0 " + fileName;
        int result = system(fullCommand.c_str());
        ASSERT_EQ(result, 0) << "Command failed: " << fullCommand;
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
    std::string fileContents = readFileContents();
    ASSERT_TRUE(fileContents.empty());

    // 第一次执行插入命令并退出
    executeTestCommand(initialCommands);

    // 第二次打开数据库并执行选择命令
    executeTestCommand(selectCommand);

    // 读取文件内容并验证
    fileContents = readFileContents();
    ASSERT_FALSE(fileContents.empty())
        << "Database file should not be empty after insert and select commands";
}