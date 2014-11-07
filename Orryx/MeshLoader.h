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
        static bool ParseLines(const char* filename, std::vector<std::string>& destination);
        static std::vector<Vector3> ObjVertexPass(const std::vector<std::string>& lines);
        static std::vector<Vector2> ObjTexCoordPass(const std::vector<std::string>& lines);
        static std::vector<Vector3> ObjNormalPass(const std::vector<std::string>& lines);
        static std::vector<u16> ObjIndexPass(const std::vector<std::string>& lines);
    };
}

#endif