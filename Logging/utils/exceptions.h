

#pragma once

#include <stdexcept>

// throw when an argument is invalid
class InvalidArgumentException : public std::invalid_argument {
public:
    InvalidArgumentException(const std::string& message) : std::invalid_argument(message) {}
};
// throw when a functionality is not implemented
class NotImplementedException : public std::logic_error {
public:
    NotImplementedException(const std::string& message) : std::logic_error(message) {}
};

// base class for all logging exceptions
class LoggingException : public std::runtime_error {
public:
    LoggingException(const std::string& message) : std::runtime_error(message) {}
};

//throw when the file cannot be opened
class FileOpenException : public LoggingException {
public:
    FileOpenException(const std::string& message) : LoggingException(message) {}
};

//throw when the file cannot be written to
class FileWriteException : public LoggingException {
public:
    FileWriteException(const std::string& message) : LoggingException(message) {}
};

//throw when the formatter is not valid or key missing in the formatter
class FormatterException : public LoggingException {
public:
    FormatterException(const std::string& message) : LoggingException(message) {}
};