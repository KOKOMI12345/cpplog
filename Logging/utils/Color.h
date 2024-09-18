
#pragma once
// includes
#include <string>
#include <map>
// end includes

const std::map<std::string, std::string> color_map = {
    {"red", "\033[31m"},
    {"green", "\033[32m"},
    {"yellow", "\033[33m"},
    {"blue", "\033[34m"},
    {"magenta", "\033[35m"},
    {"cyan", "\033[36m"},
    {"white", "\033[37m"},
    {"gray", "\033[90m"},
    {"reset", "\033[0m"},
    {"bold", "\033[1m"},
    {"underline", "\033[4m"},
    {"invisible", "\033[08m"},
    {"reverse", "\033[07m"}
};

std::string ColorRender(std::string str, std::string color, bool bold = false, bool italic = false, bool underline = false)
{
    std::string result = color_map.at(color);
    if (bold)
        result += color_map.at("bold");
    if (italic)
        result += color_map.at("italic");
    if (underline)
        result += color_map.at("underline");
    result += str;
    result += color_map.at("reset");
    return result;
}