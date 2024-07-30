#include "../include/InputBuffer.h"

#include <iostream>

#include "../include/Statement.h"

void InputBuffer::readLine() {
    std::getline(std::cin, m_buffer);
    // std::cout << buffer << std::endl;
    if (std::cin.fail()) {
        throw std::runtime_error("Error reading input");
    }
}

MetaCommandResult InputBuffer::parseMetaCommand() {
    if (m_buffer == ".exit") {
        return MetaCommandResult::META_COMMAND_EXIT;
    }

    return MetaCommandResult::META_COMMAND_UNRECOGNIZED;
}

StatementResult InputBuffer::parseStatement(Statement &statement) {
    StatementType statementType;
    StatementResult statementResult = getStatementType(statementType);
    if (statementResult != StatementResult::PREPARE_SUCCESS) {
        return statementResult;
    }

    return statement.init(m_buffer, statementType);
}

StatementResult InputBuffer::getStatementType(StatementType &statementType) {
    if (m_buffer.compare(0, 6, "insert") == 0) {
        statementType = StatementType::STATEMENT_INSERT;
        return StatementResult::PREPARE_SUCCESS;
    }

    if (m_buffer.compare(0, 6, "select") == 0) {
        statementType = StatementType::STATEMENT_SELECT;
        return StatementResult::PREPARE_SUCCESS;
    }

    return StatementResult::PREPARE_UNRECOGNIZED_STATEMENT;
}