
// 假设我们有一个日志记录系统，需要根据日志级别（如 INFO、DEBUG、ERROR）来记录日志。
// 我们可以使用责任链模式来实现不同级别的日志记录器，每个记录器处理特定级别的日志，并将其他级别的日志传递给下一个记录器。
// 责任链（Chain of Responsibility）设计模式的本质是将请求沿着处理链传递，直到有一个处理器处理它。
// 每个处理器都包含对下一个处理器的引用，如果当前处理器不能处理请求，它会将请求传递给下一个处理器。

#include <iostream>
#include <string>

class Logger {
   protected:
    Logger* nextLogger;

   public:
    Logger() : nextLogger(nullptr) {}

    void setNextLogger(Logger* nextLogger) { this->nextLogger = nextLogger; }

    void logMessage(int level, const std::string& message) {
        if (this->canHandle(level)) {
            this->write(message);
        }
        if (this->nextLogger != nullptr) {
            this->nextLogger->logMessage(level, message);
        }
    }

    virtual bool canHandle(int level) = 0;
    virtual void write(const std::string& message) = 0;
};

// 具体处理者类
class InfoLogger : public Logger {
   public:
    bool canHandle(int level) override { return level == 1; }

    void write(const std::string& message) override {
        std::cout << "INFO: " << message << std::endl;
    }
};

class DebugLogger : public Logger {
   public:
    bool canHandle(int level) override { return level == 2; }

    void write(const std::string& message) override {
        std::cout << "DEBUG: " << message << std::endl;
    }
};

class ErrorLogger : public Logger {
   public:
    bool canHandle(int level) override { return level == 3; }

    void write(const std::string& message) override {
        std::cout << "ERROR: " << message << std::endl;
    }
};

int main() {
    Logger* errorLogger = new ErrorLogger();
    Logger* debugLogger = new DebugLogger();
    Logger* infoLogger = new InfoLogger();

    infoLogger->setNextLogger(debugLogger);
    debugLogger->setNextLogger(errorLogger);

    infoLogger->logMessage(1, "This is an information.");
    infoLogger->logMessage(2, "This is a debug level information.");
    infoLogger->logMessage(3, "This is an error information.");

    delete errorLogger;
    delete debugLogger;
    delete infoLogger;

    return 0;
}