#include "../include/Table.h"

#include <cstdint>
#include <cstring>

#include "../include/Macros.h"

Table::Table(const std::string& filename) {
    m_pager = new Pager(filename);
    m_row_nums = m_pager->m_file_length / ROW_SIZE;
};

Table::~Table() {
    db_close();
    delete m_pager;
};

void Table::db_close() {
    // 计算需要写入的整页面数
    uint32_t full_num_rows = m_row_nums / ROWS_PER_PAGE;
    for (int i = 0; i < full_num_rows; i++) {
        if (!m_pager->m_pages[i]) {
            continue;
        }

        m_pager->pager_flush(i, PAGE_SIZE);
        m_pager->m_pages[i] = nullptr;
    }

    uint32_t additional_rows = m_row_nums % ROWS_PER_PAGE;
    if (additional_rows > 0) {
        if (m_pager->m_pages[full_num_rows]) {
            m_pager->pager_flush(full_num_rows, additional_rows * ROW_SIZE);
            m_pager->m_pages[full_num_rows] = nullptr;
        }
    }
};

ExecuteResult Table::execute_statement(Statement& stmt) {
    switch (stmt.m_type) {
        case StatementType::STATEMENT_INSERT:
            return insert_row(stmt);
        case StatementType::STATEMENT_SELECT:
            return select_row(stmt);
        default:
            return ExecuteResult::EXECUTE_UNKNOWN;
    }
};

ExecuteResult Table::insert_row(Statement& stmt) {
    if (m_row_nums >= TABLE_MAX_ROWS) {
        return ExecuteResult::EXECUTE_FULL_TABLE;
    }

    void* page = get_row_slot(m_row_nums);
    serialize_row_insert(&stmt.m_row_to_insert, page);
    m_row_nums++;
    return ExecuteResult::EXECUTE_SUCCESS;
};

ExecuteResult Table::select_row(Statement& stmt) {
    Row row;
    for (int i = 0; i < m_row_nums; i++) {
        void* page = get_row_slot(i);
        deserialize_row_select(page, &row);
        row.print_row();
    }
    return ExecuteResult::EXECUTE_SUCCESS;
};

void* Table::get_row_slot(uint32_t row_num) {
    uint32_t page_num = row_num / ROWS_PER_PAGE;
    void* page = m_pager->getPage(page_num);
    uint32_t row_offset = row_num % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * ROW_SIZE;
    return (void*)((char*)page + byte_offset);
};

void Table::serialize_row_insert(Row* source, void* destination) {
    memcpy(destination, &(source->m_id), ID_SIZE);
    memcpy((char*)destination + USERNAME_OFFSET, source->m_username, USERNAME_SIZE);
    memcpy((char*)destination + EMAIL_OFFSET, source->m_email, EMAIL_SIZE);
};

void Table::deserialize_row_select(void* source, Row* destination) {
    memcpy(&(destination->m_id), source, ID_SIZE);
    memcpy(destination->m_username, (char*)source + USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(destination->m_email, (char*)source + EMAIL_OFFSET, EMAIL_SIZE);
};