
# C++日志库 (C++ Logging Library)

## 描述

- **C++日志库** 这个C++日志库是我自己编写的C++日志库，为了提供易于使用的接口，不需要繁琐的配置，只需要简单地调用接口即可快速地记录日志。
- **日志级别** 日志库提供了6个日志级别，分别是：TRACE、DEBUG、INFO、WARNING、ERROR、FATAL。
- **日志格式** 日志库提供了两种日志格式，分别是：文本格式和JSON格式。
- **日志输出** 日志库提供了多种日志输出方式，包括：文件、控制台、网络、数据库等。
- **日志过滤** 日志库提供了日志过滤功能，可以根据日志级别、日志内容、日志来源进行过滤，实现精准的日志记录。
- **日志线程安全** 日志库是线程安全的，可以在多线程环境下使用。

## 快速开始

```cpp
#include "Logging/logging.h"

int main() {
    Formatter mylogFormatter("{time} | {level:<7} | {file}:{function}:{line} | {message}");
    Logger& logger = LogManager::getLogger("test", LogLevel::LevelTRACE, mylogFormatter);

    // 使用 HandlerFactory 创建 StreamHandler
    auto consoleHandler = HandlerFactory::createStreamHandler("console", LogLevel::LevelTRACE, mylogFormatter, std::cout, true);
    logger.addHandler(std::move(consoleHandler));

    logger.trace("This is a trace message", __FILE__, __FUNCTION__, __LINE__);
    logger.debug("This is a debug message", __FILE__, __FUNCTION__, __LINE__);
    logger.info("This is an info message", __FILE__, __FUNCTION__, __LINE__);
    logger.warn("This is a warning message", __FILE__, __FUNCTION__, __LINE__);
    logger.error("This is an error message", __FILE__, __FUNCTION__, __LINE__);
    logger.fatal("This is a fatal message", __FILE__, __FUNCTION__, __LINE__);

    return 0;
}
```
