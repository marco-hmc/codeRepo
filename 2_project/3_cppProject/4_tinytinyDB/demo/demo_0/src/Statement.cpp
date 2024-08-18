
#include "../include/Statement.h"

#include <cstring>
#include <iostream>

#include "../include/InputBuffer.h"
#include "../include/Macros.h"

std::map<StatementResult, std::function<void()>> Statement::statementWarnMap() {
    return {
        {StatementResult::PREPARE_SUCCESS, []() { std::cout << "Prepare success" << '\n'; }},
        {StatementResult::PREPARE_SYNTAX_ERROR, []() { std::cout << "SYNTAX_ERROR" << '\n'; }},
        {StatementResult::PREPARE_STRING_TOO_LONG,
         []() { std::cout << "STRING_TOO_LONG" << '\n'; }},
        {StatementResult::PREPARE_NEGATIVE_ID, []() { std::cout << "NEGATIVE_ID" << '\n'; }},
        {StatementResult::PREPARE_UNRECOGNIZED_STATEMENT,
         []() { std::cout << "UNRECOGNIZED_STATEMENT" << '\n'; }},
    };
}

std::map<ExecuteResult, std::function<void()>> Statement::executeWarnMap() {
    return {
        {ExecuteResult::EXECUTE_SUCCESS, []() { std::cout << "Prepare success" << '\n'; }},
        {ExecuteResult::EXECUTE_DUPLICATE_KEY, []() { std::cout << "DUPLICATE_KEY" << '\n'; }},
        {ExecuteResult::EXECUTE_FULL_TABLE, []() { std::cout << "FULL TABLE" << '\n'; }},
        {ExecuteResult::EXECUTE_UNKNOWN, []() { std::cout << "UNKNOWN ERROR" << '\n'; }},

    };
}

StatementResult Statement::init(std::string &bufferString, StatementType type) {
    switch (type) {
        case StatementType::STATEMENT_INSERT:
            return initInsert(bufferString);
        case StatementType::STATEMENT_SELECT:
            return initSelect(bufferString);
        default:
            return StatementResult::PREPARE_UNRECOGNIZED_STATEMENT;
    }
}

StatementResult Statement::initInsert(std::string &bufferString) {
    size_t pos = 0;
    size_t startPos = 0;
    std::string token = " ";

    pos = bufferString.find(token, startPos);
    std::string command = bufferString.substr(startPos, pos - startPos);
    std::cout << "command: " << command << '\n';
    startPos = pos + token.length();

    pos = bufferString.find(token, startPos);
    std::string idStr = bufferString.substr(startPos, pos - startPos);
    std::cout << "idStr: " << idStr << '\n';
    startPos = pos + token.length();

    pos = bufferString.find(token, startPos);
    std::string username = bufferString.substr(startPos, pos - startPos);
    std::cout << "username: " << username << '\n';
    startPos = pos + token.length();

    std::string email = bufferString.substr(startPos);
    std::cout << "email: " << email << '\n';

    if (idStr.empty() || username.empty() || email.empty()) {
        return StatementResult::PREPARE_SYNTAX_ERROR;
    }

    uint32_t id = std::stoi(idStr);
    if (id < 0) {
        return StatementResult::PREPARE_NEGATIVE_ID;
    }
    if (username.length() > COLUMN_USERNAME) {
        return StatementResult::PREPARE_STRING_TOO_LONG;
    }
    if (email.length() > COLUMN_EMAIL) {
        return StatementResult::PREPARE_STRING_TOO_LONG;
    }

    m_type = StatementType::STATEMENT_INSERT;
    m_row_to_insert.m_id = id;
    std::strncpy(m_row_to_insert.m_username, username.c_str(),
                 sizeof(m_row_to_insert.m_username) - 1);
    // Ensure null-termination
    m_row_to_insert.m_username[sizeof(m_row_to_insert.m_username) - 1] = '\0';

    std::strncpy(m_row_to_insert.m_email, email.c_str(), sizeof(m_row_to_insert.m_email) - 1);
    // Ensure null-termination
    m_row_to_insert.m_email[sizeof(m_row_to_insert.m_email) - 1] = '\0';
    return StatementResult::PREPARE_SUCCESS;
}

StatementResult Statement::initSelect(std::string &bufferString) {
    m_type = StatementType::STATEMENT_SELECT;
    return StatementResult::PREPARE_SUCCESS;
}