#ifndef ORRYX_CONFIG_DATA_H
#define ORRYX_CONFIG_DATA_H

#include "OrryxTypes.h"
#include "OrryxFile.h"
#include "OrryxLogging.h"

#include <map>
#include <string>

namespace orx
{
    class ConfigData
    {
    public:
        ConfigData() {}
        ~ConfigData() {}

        static void Initialize();
        static void Terminate();

        static int get(std::string key, int ifFail = 0)
        {
            auto search = m_data.find(key);

            if (search == m_data.end())
            {
                Logging::LogWarnFormat("ConfigData", "Unable to find value with key %s.", key.c_str());
                return ifFail;
            }

            return search->second;
        }

        static void set(std::string key, int value)
        {
            m_data[key] = value;
        }

    private:
        static std::map<std::string, int> m_data;
    };
}

#endif