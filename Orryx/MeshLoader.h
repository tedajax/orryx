#ifndef ORRYX_MESH_LOADER_H
#define ORRYX_MESH_LOADER_H

#include "Mesh.h"
#include "OrryxTypes.h"
#include "OrryxMath.h"
#include "OrryxLogging.h"

#include <string>
#include <fstream>
#include <vector>

namespace orx
{
    class MeshLoader
    {
    public:
        static bool LoadObj(const char* filename, Mesh& destination);

    private:
        bool static ParseLines(const char* filename, std::vector<std::string>& destination);
        static void ObjParseFaceEntry(std::string faceEntry, int& vertex, int& texCoord, int& normal);
    };
}

#endif