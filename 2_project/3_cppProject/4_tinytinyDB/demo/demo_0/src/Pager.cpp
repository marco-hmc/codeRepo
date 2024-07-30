#include "../include/Pager.h"

#include <cstring>
#include <iostream>

#include "../include/Macros.h"

Pager::Pager(const std::string& filename) {
    m_file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!m_file) {
        std::cerr << "Failed to open file: " << filename << ".\n";
        std::exit(EXIT_FAILURE);
    }

    m_file.seekg(0, std::ios::end);
    m_file_length = m_file.tellg();
    m_file.seekg(0, std::ios::beg);

    m_pages.resize(TABLE_MAX_PAGES, nullptr);
}

Pager::~Pager() {
    for (void* page : m_pages) {
        if (page) {
            free(page);
        }
    }

    m_file.close();
}

void* Pager::getPage(uint32_t page_num) {
    if (m_pages.size() <= page_num) {
        std::cerr << "out of limitation: " << std::strerror(errno) << ".\n";
        std::exit(EXIT_FAILURE);
    }

    if (m_pages[page_num] == nullptr) {
        void* page = malloc(PAGE_SIZE);

        if (m_file_length > 0 && m_file_length >= page_num * PAGE_SIZE) {
            m_file.seekg(page_num * PAGE_SIZE, std::ios::beg);
            if (!m_file) {
                std::cerr << "get page error seek: " << std::strerror(errno) << ".\n";
                std::exit(EXIT_FAILURE);
            }

            m_file.read(static_cast<char*>(page), PAGE_SIZE);
            if (!m_file) {
                std::cerr << "get page error read" << std::strerror(errno) << ".\n";
                std::exit(EXIT_FAILURE);
            }
        }
        m_pages[page_num] = page;
    }

    return m_pages[page_num];
}

void Pager::pager_flush(uint32_t page_num, uint32_t size) {
    if (m_pages[page_num] == NULL) {
        printf("flush error by empty page at %d, size: %d .\n", page_num, size);
        exit(EXIT_FAILURE);
    }

    // 将文件指针移动到正确的位置
    m_file.seekp(page_num * PAGE_SIZE, std::ios::beg);
    if (!m_file) {
        std::cerr << "flush seek page at " << page_num << ", error: " << std::strerror(errno)
                  << ".\n";
        std::exit(EXIT_FAILURE);
    }

    // 写入数据到文件
    m_file.write(static_cast<char*>(m_pages[page_num]), size);
    if (!m_file) {
        std::cerr << "flush write page at " << page_num << ", error: " << std::strerror(errno)
                  << ".\n";
        std::exit(EXIT_FAILURE);
    }
}