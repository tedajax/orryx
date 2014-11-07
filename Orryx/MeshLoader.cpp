#include "MeshLoader.h"

#include "OrryxUtil.h"

namespace orx
{
    bool MeshLoader::LoadObj(const char* filename, Mesh& destination)
    {
        std::vector<std::string> lines;
        if (!ParseLines(filename, lines))
        {
            return false;
        }

        auto vertices = ObjVertexPass(lines);
        auto indices = ObjIndexPass(lines);
        
        destination.setVertices(vertices);
        destination.setIndices(indices);

        return true;
    }

    bool MeshLoader::ParseLines(const char* filename, std::vector<std::string>& destination)
    {
        std::ifstream in(filename, std::ios::in);

        if (!in.is_open())
        {
            return false;
        }

        destination.clear();
        std::string line = "";
        while (getline(in, line))
        {
            destination.push_back(line);
        }

        in.close();

        return true;
    }

    std::vector<Vector3> MeshLoader::ObjVertexPass(const std::vector<std::string>& lines)
    {
        std::vector<Vector3> vertices;

        for (auto line : lines)
        {
            std::vector<std::string> tokens;
            orx::tokenize<std::vector<std::string>>(line, tokens);

            if (tokens[0] == "v")
            {
                f32 x = std::stof(tokens[1]);
                f32 y = std::stof(tokens[2]);
                f32 z = std::stof(tokens[3]);

                vertices.push_back({ x, y, z });
            }
        }

        return vertices;
    }

    std::vector<Vector2> MeshLoader::ObjTexCoordPass(const std::vector<std::string>& lines)
    {
        std::vector<Vector2> texCoords;
        return texCoords;
    }

    std::vector<Vector3> MeshLoader::ObjNormalPass(const std::vector<std::string>& lines)
    {
        std::vector<Vector3> normals;
        return normals;
    }

    std::vector<u16> MeshLoader::ObjIndexPass(const std::vector<std::string>& lines)
    {
        std::vector<u16> indices;

        for (auto line : lines)
        {
            std::vector<std::string> tokens;
            orx::tokenize<std::vector<std::string>>(line, tokens);

            if (tokens[0] == "f")
            {
                u16 i0 = std::stoi(tokens[1]);
                u16 i1 = std::stoi(tokens[2]);
                u16 i2 = std::stoi(tokens[3]);

                indices.push_back(i0);
                indices.push_back(i1);
                indices.push_back(i2);
            }
        }

        return indices;
    }
}