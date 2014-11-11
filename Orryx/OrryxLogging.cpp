#include "OrryxLogging.h"

#include <sstream>
#include <cstdlib>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace orx
{
    std::ofstream Logging::s_outFile;

    void Logging::Initialize()
    {
        s_outFile.open("log.txt", std::ios::out);
    }

    void Logging::Terminate()
    {
        s_outFile.close();
    }

    void Logging::Log(LogLevel level, const char* context, const char* msg)
    {
        std::stringstream stream;

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        int color;
        switch (level)
        {
            default:
            case LOG_LEVEL_INFO:
                color = 7;
                break;

            case LOG_LEVEL_WARN:
                color = 0xE;
                break;

            case LOG_LEVEL_ERROR:
                color = 0xC;
                break;

            case LOG_LEVEL_PANIC:
                color = 0xC + 0xF0;
                break;
        }
        SetConsoleTextAttribute(hConsole, color);
        

        stream << "[" << context << "] " << GetLogLevelString(level) << ": " << msg << std::endl << std::endl;
        std::cout << stream.str();
        s_outFile << stream.str();

        if (level == LOG_LEVEL_PANIC)
        {
            __debugbreak();
        }
    }

    void Logging::LogFormat(LogLevel level, const char* context, const char* format, ...)
    {
        va_list args;
        va_start(args, format);
        Logging::LogFormatV(level, context, format, args);
        va_end(args);
    }

    void Logging::LogFormatV(LogLevel level, const char* context, const char* format, va_list args)
    {
        const size_t MAX_LENGTH = 256;
        char msg[MAX_LENGTH];

        vsnprintf_s(&msg[0], MAX_LENGTH, _TRUNCATE, format, args);

        Logging::Log(level, context, msg);
    }

    void Logging::LogInfo(const char* context, const char* msg)
    {
        Logging::Log(LOG_LEVEL_INFO, context, msg);
    }

    void Logging::LogInfoFormat(const char* context, const char* format, ...)
    {
        va_list args;
        va_start(args, format);
        Logging::LogFormatV(LOG_LEVEL_INFO, context, format, args);
        va_end(args);
    }

    void Logging::LogWarn(const char* context, const char* msg)
    {
        Logging::Log(LOG_LEVEL_WARN, context, msg);
    }

    void Logging::LogWarnFormat(const char* context, const char* format, ...)
    {
        va_list args;
        va_start(args, format);
        Logging::LogFormatV(LOG_LEVEL_WARN, context, format, args);
        va_end(args);
    }

    void Logging::LogError(const char* context, const char* msg)
    {
        Logging::Log(LOG_LEVEL_ERROR, context, msg);
    }

    void Logging::LogErrorFormat(const char* context, const char* format, ...)
    {
        va_list args;
        va_start(args, format);
        Logging::LogFormatV(LOG_LEVEL_ERROR, context, format, args);
        va_end(args);
    }

    void Logging::LogPanic(const char* context, const char* msg)
    {
        Logging::Log(LOG_LEVEL_PANIC, context, msg);
    }

    void Logging::LogPanicFormat(const char* context, const char* format, ...)
    {
        va_list args;
        va_start(args, format);
        Logging::LogFormatV(LOG_LEVEL_PANIC, context, format, args);
        va_end(args);
    }

    const char* Logging::GetLogLevelString(LogLevel level)
    {
        switch (level)
        {
        default:
        case LOG_LEVEL_INFO:
            return "Info";

        case LOG_LEVEL_WARN:
            return "Warning";

        case LOG_LEVEL_ERROR:
            return "Error";

        case LOG_LEVEL_PANIC:
            return "Panic";
        }
    }
}