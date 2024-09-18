
#pragma once
#include "../utils/exceptions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>

class FileWriter {
public:
    FileWriter(const std::string& filename) : filename_(filename), fileStream_(filename, std::ios::out) {
        if (!fileStream_.is_open()) {
            throw FileOpenException("Failed to open file for writing: " + filename_);
        }
    }

    ~FileWriter() {
        if (fileStream_.is_open()) {
            fileStream_.close();
        }
    }

    // 禁止拷贝构造和拷贝赋值
    FileWriter(const FileWriter&) = delete;
    FileWriter& operator=(const FileWriter&) = delete;

    std::string GetFilename() const {
        return filename_;
    }

    // 写入内容到文件
    void Write(const std::string& content) {
        std::lock_guard<std::mutex> lock(mutex_); // 锁定互斥体
        if (fileStream_.is_open()) {
            fileStream_ << content;
            fileStream_.flush(); // 确保内容被写入文件
        } else {
            throw FileWriteException("Failed to write to file: " + filename_);
        }
    }

    // 检查文件是否成功打开
    bool IsOpen() const {
        std::lock_guard<std::mutex> lock(mutex_); // 锁定互斥体
        return fileStream_.is_open();
    }

private:
    std::string filename_;       // 文件名
    std::ofstream fileStream_;   // 文件流
    mutable std::mutex mutex_;   // 互斥体，用于同步写入操作
};