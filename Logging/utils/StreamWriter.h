
#pragma once

#include <iostream>
#include <mutex>

class Stream {
private:
    std::ostream& m_stream;
    std::mutex m_mutex;

public:
    Stream(std::ostream& stream) : m_stream(stream) {}

    void write(const std::string& str, bool auto_newline = true) {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (auto_newline) {
            m_stream << str << std::endl;
        } else {
            m_stream << str;
        }
        m_stream.flush();
    }
};