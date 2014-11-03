#ifndef ORRYX_LOGGING_H
#define ORRYX_LOGGING_H

#include "OrryxTypes.h"
#include <cstdarg>
#include <fstream>
#include <iostream>

namespace orx
{
    class Logging
    {
    public:
        enum LogLevel
        {
            LOG_LEVEL_INFO,
            LOG_LEVEL_WARN,
            LOG_LEVEL_ERROR,
            LOG_LEVEL_PANIC,
        };

        static void Initialize();
        static void Terminate();

        static void Log(LogLevel level, const char* context, const char* msg);
        static void LogFormat(LogLevel level, const char* context, const char* format, ...);

        static void LogInfo(const char* context, const char* msg);
        static void LogInfoFormat(const char* context, const char* format, ...);

        static void LogWarn(const char* context, const char* msg);
        static void LogWarnFormat(const char* context, const char* format, ...);

        static void LogError(const char* context, const char* msg);
        static void LogErrorFormat(const char* context, const char* format, ...);

        static void LogPanic(const char* context, const char* msg);
        static void LogPanicFormat(const char* context, const char* format, ...);

    private:
        static void LogFormatV(LogLevel level, const char* context, const char* format, va_list args);

        static const char* GetLogLevelString(LogLevel level);

        static std::ofstream s_outFile;
    };
}
#endif