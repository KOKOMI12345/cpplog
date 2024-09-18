
#pragma once
#include <string>
#include <ctime>
#include <iomanip> // 包含用于格式化时间的库

// 获取当前时间的字符串表示，不进行格式化
std::string getCurrentTime()
{
    time_t now = time(0);
    char buffer[100]; // 创建一个足够大的字符数组来存储时间字符串
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return std::string(buffer);
}

// 返回当前的时间戳字符串
std::string getCurrentTimeStamp()
{
    time_t now = time(0);
    char* dt = ctime(&now); // 获取当前时间的字符串表示
    return std::string(dt); // 将字符串转换为std::string类型并返回
}

// 根据提供的格式获取格式化的当前时间字符串
std::string getFormattedTime(const std::string& format)
{
    time_t now = time(0);
    std::tm* ptm = localtime(&now);
    std::ostringstream oss; // 使用字符串流进行格式化
    oss << std::put_time(ptm, format.c_str()); // 将格式化的时间写入字符串流
    return oss.str(); // 将字符串流的内容转换为字符串并返回
}