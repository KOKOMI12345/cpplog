#pragma once
#include <string>
#include <thread>
#include <mutex>
#include <exception>
#include <typeinfo>
#ifdef _WIN32
#include <windows.h>
#include <stdexcept>
DWORD getThisThreadId() {
    return GetCurrentThreadId();
}

void setThreadName(DWORD dwThreadID, const char* threadName) {
    const DWORD MS_VC_EXCEPTION = 0x406D1388;
    struct THREADNAME_INFO {
        DWORD dwType;           // Must be 0x1000
        LPCSTR szName;          // Pointer to name (in user addr space)
        DWORD dwThreadID;       // Thread ID (-1=caller thread)
        DWORD dwFlags;          // Reserved for future use, must be zero
    } info;
    info.dwType = 0x1000;
    info.szName = threadName;
    info.dwThreadID = dwThreadID;
    info.dwFlags = 0;
    __try {
        RaiseException(MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(ULONG_PTR), (ULONG_PTR*)&info);
    } catch (...) {
        printf("Exception in SetThreadName\n");
    }
}

void setThisThreadName(const char* threadName) {
    setThreadName(getThisThreadId(), threadName);
}

#else
#include <pthread.h>

void SetThreadName(const pthread_t threadId, const char* threadName) {
    // POSIX specific code here
    pthread_setname_np(threadId, threadName);
}

void setThisThreadName(const char* threadName) {
    SetThreadName(pthread_self(), threadName);
}
#endif

std::string getThreadId() {
    std::thread::id id = std::this_thread::get_id();
    return std::to_string(std::hash<std::thread::id>()(id));
}

inline std::string getProcessName() {
    // TODO: 获取进程名
    return "unknown";
}

inline std::string getCurrentFileName(std::string filename, bool fullpath = false) {
    if (fullpath) {
        return filename;
    }
    size_t pos = filename.rfind('/');
    if (pos == std::string::npos) {
        pos = filename.rfind('\\');
    }
    if (pos != std::string::npos) {
        filename = filename.substr(pos + 1);
    }
    return filename;
}

template<typename T>
inline std::string getType(const T& value) {
    return typeid(value).name();
}

// 或者使用 std::decay 来处理引用和 cv-qualifiers
template<typename T>
inline std::string getType(std::decay_t<T>& value) {
    return typeid(value).name();
}