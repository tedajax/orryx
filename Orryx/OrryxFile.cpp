#include "OrryxFile.h"

#include <fstream>
#include <sstream>

namespace orx
{
    std::string loadFileString(const char* filename)
    {
        std::string result;
        std::ifstream inStream(filename, std::ios::in);
        
        if (inStream.is_open())
        {
            std::string line = "";
            while (getline(inStream, line))
            {
                result += "\n" + line;
            }
            inStream.close();
        }

        return result;
    }
}