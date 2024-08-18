#include <iostream>
#include <memory>

#include "include/EnumClass.h"
#include "include/InputBuffer.h"
#include "include/Statement.h"
#include "include/Table.h"

int main(int argc, char *argv[]) {
    std::string filename;
    if (argc == 1) {
        filename =
            "/home/marco/0_codeRepo/2_project/3_cppProject/4_tinytinyDB/demo/demo_0/build/"
            "demo_debug.db";
    } else {
        filename = argv[1];
    }

    auto table = std::make_unique<Table>(filename);
    bool isRun = true;
    while (isRun) {
        std::cout << "> ";
        auto inputBuffer = std::make_unique<InputBuffer>();
        inputBuffer->readLine();

        if (inputBuffer->buffer()[0] == '.') {
            switch (inputBuffer->parseMetaCommand()) {
                case MetaCommandResult::META_COMMAND_SUCCESS:
                    continue;
                case MetaCommandResult::META_COMMAND_EXIT:
                    table.reset();
                    isRun = false;
                    continue;
                case MetaCommandResult::META_COMMAND_BTREE_PRINT:
                    table->printBtree();
                    continue;
                case MetaCommandResult::META_COMMAND_CONST_PRINT:
                    table->printConst();
                    continue;
                case MetaCommandResult::META_COMMAND_UNRECOGNIZED:
                    std::cout << "Unrecognized command '" << inputBuffer->buffer() << "'." << '\n';
                    continue;
            }
        }

        Statement statement;
        switch (auto parseState = inputBuffer->parseStatement(statement)) {
            case StatementResult::PREPARE_SUCCESS:
                std::cout << "Statement parse successfully." << '\n';
                break;
            default:
                Statement::statementWarnMap()[parseState]();
                continue;
        }

        switch (auto executeState = table->execute_statement(statement)) {
            case ExecuteResult::EXECUTE_SUCCESS:
                std::cout << "Executed." << '\n';
                break;
            default:
                Statement::executeWarnMap()[executeState]();
                continue;
        }
    }

    return 0;
}