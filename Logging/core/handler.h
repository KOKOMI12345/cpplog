#pragma once

#include "../utils/Formatter.h"
#include "../utils/StreamWriter.h"
#include "../utils/filewriter.h"
#include "../core/loglevel.h"
#include "../core/logbody.h"
#include "../utils/Color.h"
#include "../core/loglevel.h"

#include <memory>
#include <unordered_map>
#include <iostream>
#include <string>

// Base class for all logging handlers
class Handler {
public:
    const std::string name_;
    const LogLevel level_;
    Formatter formatter_;

    Handler(const std::string& name, const LogLevel& level, const Formatter& formatter)
        : name_(name), level_(level), formatter_(formatter) {}

    virtual void handle(LogRecord record) = 0;

    virtual ~Handler() {}

    std::string getName() const {
        return name_;
    }

    LogLevel getLevel() const {
        return level_;
    }
};

class StreamHandler : public Handler {
public:
    Stream stream_;
    bool colorize_;

    StreamHandler(const std::string& name, const LogLevel& level, const Formatter& formatter, std::ostream& stream, bool colorize)
        : Handler(name, level, formatter), stream_(stream), colorize_(colorize) {}

    void handle(LogRecord record) override {
        if (record.level >= level_) {
            std::map<std::string, std::string> extraInfo = record.getExtraInfo();
            std::string formatted = formatter_.GetFormattedString(extraInfo, false);
            if (colorize_) {
                std::string color = LogLevelToColor[record.level];
                std::string formattedWithColor = ColorRender(formatted, color, true);
                stream_.write(formattedWithColor, true);
            } else {
                stream_.write(formatted, true);
            }
        }
    }
};

// HandlerFactory: make handler objects
class HandlerFactory {
public:
    static std::unique_ptr<Handler> createStreamHandler(const std::string& name, LogLevel level, const Formatter& formatter, std::ostream& stream, bool colorize) {
        return std::make_unique<StreamHandler>(name, level, formatter, stream, colorize);
    }
};