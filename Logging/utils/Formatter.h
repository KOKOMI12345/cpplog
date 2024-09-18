#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <iomanip>  // 用于格式化输出
#include "../utils/exceptions.h"

class Formatter {
private:
    std::string format;

public:
    Formatter(std::string fmt) {
        format = fmt;
    }
    void setFormatter(std::string fmt) {
        format = fmt;
    }

    bool isSet() {
        if (format.empty()) {
            return false;
        }
        return true;
    }

    std::string GetFormattedString(std::map<std::string, std::string>& values, bool throwsException = true) {
        std::string result = format;
        std::string::size_type pos = 0;

        while ((pos = result.find('{', pos)) != std::string::npos) {
            std::string::size_type endPos = result.find('}', pos);
            if (endPos == std::string::npos) {
                break; // 没有找到结束的 '}'
            }

            std::string placeholder = result.substr(pos + 1, endPos - pos - 1);
            std::string key;
            int width = -1;
            bool leftAlign = false;

            std::istringstream ss(placeholder);
            std::getline(ss, key, ':'); // 分离键和格式说明符
            if (ss) {
                std::getline(ss, placeholder); // 获取格式说明符
                if (placeholder[0] == '<' || placeholder[0] == '>') {
                    leftAlign = (placeholder[0] == '<');
                    std::string::size_type numPos = placeholder.find_first_of("0123456789");
                    if (numPos != std::string::npos) {
                        width = std::stoi(placeholder.substr(numPos));
                    }
                }
            }

            if (values.find(key) == values.end()) {
                if (throwsException) {
                    throw FormatterException("Placeholder '" + key + "' not found in values.");
                }
                result.replace(pos, endPos - pos + 1, "");
                continue;
            }

            std::ostringstream formatted;
            if (width != -1) {
                formatted << std::setw(width);
                if (key == "line" && !leftAlign) {
                    formatted << std::setfill('0');
                }
                formatted << (leftAlign ? std::left : std::right);
            }
            formatted << values.at(key);

            result.replace(pos, endPos - pos + 1, formatted.str());
            pos += formatted.str().length();
        }

        return result;
    }
};