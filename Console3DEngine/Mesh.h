#pragma once

#include "Triangle.h"

#include <vector>
#include <fstream>
#include <strstream>


struct Mesh
{
	std::vector<Triangle> triangles;

	bool LoadFromObjectFile(std::string fileName, bool hasTexture = false)
	{
		std::ifstream file(fileName);
		if (!file.is_open())
			return false;

		std::vector<Vector3D> vertices;
		std::vector<Vector2D> textures;

		while (!file.eof())
		{
			char line[128];
			file.getline(line, 128);

			std::strstream strLine;
			strLine << line;

			char header;

			if (line[0] == 'v')
			{
				if (line[1] == 't')
				{
					Vector2D texture;
					strLine >> header >> texture.u >> texture.v;
					textures.push_back(texture);
				}
				else
				{
					Vector3D vertex;
					strLine >> header >> vertex.x >> vertex.y >> vertex.z;
					vertices.push_back(vertex);
				}
			}

			if (line[0] == 'f')
			{
				if (hasTexture)
				{
					strLine >> header;

					std::string tokens[6];
					int tokenCount = -1;

					while (!strLine.eof())
					{
						char c = strLine.get();
						if (c == ' ' || c == '/')
							tokenCount++;
						else
							tokens[tokenCount].append(1, c);
					}

					tokens[tokenCount].pop_back();

					triangles.push_back({
						vertices[std::stoi(tokens[0]) - 1], vertices[std::stoi(tokens[2]) - 1], vertices[std::stoi(tokens[4]) - 1],
						textures[std::stoi(tokens[1]) - 1], textures[std::stoi(tokens[3]) - 1], textures[std::stoi(tokens[5]) - 1]
					});
				}
				else
				{
					int f[3];
					strLine >> header >> f[0] >> f[1] >> f[2];
					triangles.push_back({ vertices[f[0] - 1], vertices[f[1] - 1], vertices[f[2] - 1] });
				}
			}
		}

		file.close();

		return true;
	}
};