
#pragma once

enum class LogLevel {
    LevelTRACE,
    LevelDEBUG,
    LevelINFO,
    LevelWARNING,
    LevelERROR,
    LevelFATAL
};

std::map<LogLevel, std::string> LogLevelToString = {
    {LogLevel::LevelTRACE, "TRACE"},
    {LogLevel::LevelDEBUG, "DEBUG"},
    {LogLevel::LevelINFO, "INFO"},
    {LogLevel::LevelWARNING, "WARNING"},
    {LogLevel::LevelERROR, "ERROR"},
    {LogLevel::LevelFATAL, "FATAL"}
};

std::map<LogLevel, std::string> LogLevelToColor = {
    {LogLevel::LevelTRACE, "gray"},
    {LogLevel::LevelDEBUG, "blue"},
    {LogLevel::LevelINFO, "cyan"},
    {LogLevel::LevelWARNING, "yellow"},
    {LogLevel::LevelERROR, "red"},
    {LogLevel::LevelFATAL, "magenta"},
};