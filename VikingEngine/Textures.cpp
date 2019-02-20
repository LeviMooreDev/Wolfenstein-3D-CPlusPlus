#include "Textures.h"
#include "Debug.h"
#include <GLFW\glfw3.h>
#include <SOIL\SOIL.h>
#include <iostream>
typedef std::basic_string<char> string;

std::unordered_map<string, unsigned int> Textures::textureIds;

void Textures::AddTexture(string name, string filePath)
{
	if (textureIds.count(name) != 0)
	{
		Debug::Error("Trying to add two textures with the same name. Name: " + name + ". File: " + filePath);
	}

	string fullPath = ".\\Textures/" + filePath + ".png";
	unsigned int id = SOIL_load_OGL_texture(fullPath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	textureIds.insert(std::pair<string, unsigned int>(name, id));
}

unsigned int Textures::GetTexture(string name)
{
	if (textureIds.count(name) == 0)
	{
		Debug::Error("Trying to get a texture that has not been added. Name: " + name);
		return 0;
	}

	return textureIds.find(name)->second;
}
