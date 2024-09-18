#pragma once

#include <mutex>
#include <unordered_map>
#include <memory>
#include "../core/Logger.h"
#include "../utils/Formatter.h"
#include "../core/loglevel.h"

class LogManager {
private:
    static LogManager instance;  // 静态实例
    static std::mutex instanceMtx;  // 互斥锁用于实例创建
    std::unordered_map<std::string, std::unique_ptr<Logger>> loggers;  // 使用 unique_ptr 存储 Logger 指针

    LogManager() {}  // 私有构造函数
    LogManager(const LogManager&) = delete;
    LogManager& operator=(const LogManager&) = delete;

public:
    static LogManager& getInstance() {
        std::lock_guard<std::mutex> lock(instanceMtx);
        return instance;
    }

    static Logger& getLogger(const std::string& name, LogLevel level, const Formatter& formatter) {
        std::lock_guard<std::mutex> lock(instanceMtx);
        auto it = instance.loggers.find(name);
        if (it != instance.loggers.end()) {
            return *(it->second);  // 返回现有的 Logger 引用
        }
        auto newLogger = std::make_unique<Logger>(name, level, formatter);
        auto newLoggerPtr = newLogger.get();
        instance.loggers[name] = std::move(newLogger);
        return *newLoggerPtr;
    }
};

// 在.cpp文件中初始化静态成员变量
LogManager LogManager::instance;
std::mutex LogManager::instanceMtx;