#pragma once

#include <string>
#include "../core/loglevel.h"
#include "../utils/exceptions.h"
#include "../utils/timeUtils.h"
#include "../core/loglevel.h"

class LogRecord {
public:
    LogLevel level;
    std::string name;
    std::string message;
    std::string fileName;
    int lineno;
    std::string functionName;
    std::string threadName;
    std::string timeStamp;
    std::string pathName;
    std::string processName;
    std::string processId;
    std::string threadId;

public:
    // 构造函数
    LogRecord(
        std::string name, 
        LogLevel lvl, 
        std::string msg,
        std::string file,
        int line,
        std::string func,
        std::string thread,
        std::string time,
        std::string path,
        std::string procName,
        std::string procId,
        std::string threadId
    ) : level(lvl), message(msg), fileName(file), lineno(line), functionName(func),
        threadName(thread), timeStamp(time), pathName(path), processName(procName),
        processId(procId), threadId(threadId) {}

    // 获取日志级别
    LogLevel getLevel() const { return level; }

    // 获取日志消息
    std::string getMessage() const { return message; }

    // 其他成员函数...
    std::map<std::string, std::string> getExtraInfo() {
        std::map<std::string, std::string> extraInfo = {
            {"file", fileName},
            {"line", std::to_string(lineno)},
            {"function", functionName},
            {"thread", threadName},
            {"time", timeStamp},
            {"path", pathName},
            {"processName", processName},
            {"processId", processId},
            {"threadId", threadId},
            {"name", name},
            {"level", LogLevelToString[level]},
            {"message", message}
        };
        return extraInfo;
    }
};