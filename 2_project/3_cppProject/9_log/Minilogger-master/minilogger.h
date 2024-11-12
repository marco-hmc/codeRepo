#ifndef LOGGER_H
#define LOGGER_H

#include <ctime>
#include <filesystem>
#include <fstream>
#include <string>

static std::string TimeStamp() {
    time_t a = time(nullptr);
    struct tm* b = localtime(&a);

    char str[9];
    strftime(str, 9, "%H:%M:%S", b);
    return str;
}

static std::string DateStamp() {
    time_t a = time(nullptr);
    struct tm* b = localtime(&a);

    char str[11];
    strftime(str, 11, "%Y.%m.%d", b);
    return str;
}

class TextDecorator {
   public:
    static std::string FileHeader(const std::string& p_title) {
        return "==================================================\n" +
               p_title + "\n" +
               "==================================================\n\n";
    }

    static std::string SessionOpen() { return "\n"; }
    static std::string SessionClose() { return "\n"; }
    static std::string Decorate(const std::string& p_string) {
        return p_string + "\n";
    }
};

template <class decorator>
class Logger {
   public:
    Logger(const std::string& p_filename, const std::string& p_logTitle,
           bool p_timestamp = false, bool p_dateStamp = false);

    ~Logger();
    void Log(const std::string& p_entry);

   private:
    std::fstream m_logfile;
    bool m_timestamp;
    bool m_dateStamp;
};

using TextLog = Logger<TextDecorator>;

template <class decorator>
Logger<decorator>::Logger(const std::string& p_filename,
                          const std::string& p_logTitle, bool p_timestamp,
                          bool p_dateStamp) {
    namespace fs = std::filesystem;

    const bool fileExists = fs::exists(p_filename);

    std::ios_base::openmode mode = std::ios::out;
    if (fileExists) {
        mode |= std::ios::app;
    }
    m_logfile.open(p_filename, mode);

    if (!m_logfile.is_open()) {
        throw std::runtime_error("Failed to open log file: " + p_filename);
    }

    // 如果文件不存在，写入文件头
    if (!fileExists) {
        m_logfile << decorator::FileHeader(p_logTitle);
    }

    // 打印开头语句，确保时间和日期戳
    m_timestamp = true;
    m_dateStamp = true;
    m_logfile << decorator::SessionOpen();
    Log("Session opened.");
    m_timestamp = p_timestamp;
    m_dateStamp = p_dateStamp;
}

template <class decorator>
Logger<decorator>::~Logger() {
    m_timestamp = true;
    m_dateStamp = true;
    Log("Session closed.");
    m_logfile << decorator::SessionClose();
}

template <class decorator>
void Logger<decorator>::Log(const std::string& p_entry) {
    std::string message;

    if (m_dateStamp) {
        message += "[" + DateStamp() + "] ";
    }
    if (m_timestamp) {
        message += "[" + TimeStamp() + "] ";
    }

    message += p_entry;
    m_logfile << decorator::Decorate(message);
    m_logfile.flush();
}

#endif
