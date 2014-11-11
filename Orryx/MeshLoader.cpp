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

        std::vector<Vector3> vertices;
        std::vector<u16> indices;

        for (int i = 0; i < lines.size(); ++i)
        {
            std::string line = lines[i];
            std::vector<std::string> tokens;
            orx::tokenize<decltype(tokens)>(line, tokens);
            
            if (tokens[0] == "v")
            {
                f32 x = std::stof(tokens[1]);
                f32 y = std::stof(tokens[2]);
                f32 z = std::stof(tokens[3]);
                vertices.push_back({ x, y, z });
            }
            else if (tokens[0] == "vt")
            {
                
            }
            else if (tokens[0] == "vn")
            {

            }
            else if (tokens[0] == "f")
            {
                int vertex = -1;
                int texCoord = -1;
                int normal = -1;

                ObjParseFaceEntry(tokens[1], vertex, texCoord, normal);

                if (vertex > 0)
                {
                    indices.push_back((u16)(vertex - 1));
                }

                ObjParseFaceEntry(tokens[2], vertex, texCoord, normal);

                if (vertex > 0)
                {
                    indices.push_back((u16)(vertex - 1));
                }

                ObjParseFaceEntry(tokens[3], vertex, texCoord, normal);

                if (vertex > 0)
                {
                    indices.push_back((u16)(vertex - 1));
                }
            }
        }

        destination.setVertices(vertices);
        destination.setIndices(indices);
        destination.calculateNormals();

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

    void MeshLoader::ObjParseFaceEntry(std::string faceEntry, int& vertex, int& texCoord, int& normal)
    {
        std::vector<std::string> tokens;
        orx::tokenize<decltype(tokens)>(faceEntry, tokens, "/");

        if (tokens.size() >= 3)
        {
            vertex = std::stoi(tokens[0]);
            if (tokens[1].length() > 0)
            {
                texCoord = std::stoi(tokens[1]);
            }
            normal = std::stoi(tokens[2]);
        }
        else if (tokens.size() >= 2)
        {
            vertex = std::stoi(tokens[0]);
            texCoord = std::stoi(tokens[1]);
        }
        else if (tokens.size() >= 1)
        {
            vertex = std::stoi(tokens[0]);
        }
    }
}