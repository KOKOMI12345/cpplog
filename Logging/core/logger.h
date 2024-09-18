#pragma once

#include <iostream>
#include <mutex>
#include <vector>
#include <map>
#include "../core/getinfo.h"
#include "../utils/exceptions.h"
#include "../utils/timeUtils.h"
#include "../utils/Formatter.h"
#include "../utils/Color.h"
#include "../utils/StreamWriter.h"
#include "../core/loglevel.h"
#include "../core/LogBody.h"  // 确保包含 LogRecord 类的定义
#include "../core/handler.h"

class Logger {
private:
    std::mutex mtx;
    std::string name;
    bool enabled = true;
    bool colorized = true;
    Formatter logformatter;
    LogLevel level = LogLevel::LevelINFO; // 默认日志级别
    Stream stream; // 用于写入日志的流
    std::vector<std::unique_ptr<Handler>> handlers; // 日志处理器

public:
    Logger(
        const std::string& name,
        LogLevel level,
        const Formatter& formatter, 
        bool enabled = true
    ): name(name), enabled(enabled), logformatter(formatter), level(level), stream(std::cout) {
        if (name.empty()) {
            throw InvalidArgumentException("Logger的名称不能为空");
        }
        if (logformatter.isSet() == false) {
            throw InvalidArgumentException("Logger的Formatter不能为空");
        }
    }

    std::string getName() const {
        return name;
    }

    void setEnabled(bool enabled) {
        this->enabled = enabled;
    }

    bool isEnabled() const {
        return enabled;
    }

    void setLogLevel(LogLevel level) {
        this->level = level;
    }

    LogLevel getLogLevel() const {
        return this->level;
    }

    void addHandler(std::unique_ptr<Handler> handler) {
        if (handler == nullptr) {
            throw InvalidArgumentException("Handler不能为空");
        }
        handlers.push_back(std::move(handler));
    }

    void removeHandler(const std::string& name) {
        for (auto it = handlers.begin(); it != handlers.end(); ++it) {
            if ((*it)->getName() == name) {
                handlers.erase(it);
                return;
            }
        }
    }

    void clearHandlers() {
        handlers.clear();
    }

    void log(const LogRecord& record) {
        if (!enabled || record.level < level) {
            return; // 如果日志未启用或消息级别低于当前级别，则不记录
        }

        std::lock_guard<std::mutex> lock(mtx); // 确保线程安全
        // 遍历handler，将日志记录发送到每个handler
        for (auto& handler : handlers) {
            handler->handle(record);
        }
    }

    void trace(const std::string& message, const std::string& func, std::string file, int line) {
        LogRecord logrecord(this->name, LogLevel::LevelTRACE, message, getCurrentFileName(file, false), line, func, getThreadId(), getCurrentTime(), getCurrentFileName(file, true), "", "", "");
        this->log(logrecord);
    }

    void debug(const std::string& message, const std::string& func, std::string file, int line) {
        LogRecord logrecord(this->name, LogLevel::LevelDEBUG, message, getCurrentFileName(file, false), line, func, getThreadId(), getCurrentTime(), getCurrentFileName(file, true), "", "", "");
        this->log(logrecord);
    }

    void info(const std::string& message, const std::string& func, std::string file, int line) {
        LogRecord logrecord(this->name, LogLevel::LevelINFO, message, getCurrentFileName(file, false), line, func, getThreadId(), getCurrentTime(), getCurrentFileName(file, true), "", "", "");
        this->log(logrecord);
    }

    void warn(const std::string& message, const std::string& func, std::string file, int line) {
        LogRecord logrecord(this->name, LogLevel::LevelWARNING, message, getCurrentFileName(file, false), line, func, getThreadId(), getCurrentTime(), getCurrentFileName(file, true), "", "", "");
        this->log(logrecord);
    }

    void error(const std::string& message, const std::string& func, std::string file, int line) {
        LogRecord logrecord(this->name, LogLevel::LevelERROR, message, getCurrentFileName(file, false), line, func, getThreadId(), getCurrentTime(), getCurrentFileName(file, true), "", "", "");
        this->log(logrecord);
    }

    void fatal(const std::string& message, const std::string& func, std::string file, int line) {
        LogRecord logrecord(this->name, LogLevel::LevelFATAL, message, getCurrentFileName(file, false), line, func, getThreadId(), getCurrentTime(), getCurrentFileName(file, true), "", "", "");
        this->log(logrecord);
    }
};