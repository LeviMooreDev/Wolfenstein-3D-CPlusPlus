#include "Textures.h"
#include "Debug.h"
#include <GLFW\glfw3.h>
#include <SOIL\SOIL.h>
#include <iostream>
typedef std::basic_string<char> string;

//declare static fields
std::unordered_map<string, GLuint> Textures::textureIds;

void Textures::AddTexture(string name, string filePath)
{
	//check if the texture has already been added
	if (textureIds.count(name) != 0)
	{
		Debug::Error("Trying to add two textures with the same name. Name: " + name + ". File: " + filePath);
	}

	//find fill path
	string fullPath = "Textures/" + filePath + ".png";
	
	//load the texture using SOIL
	GLuint id = SOIL_load_OGL_texture(fullPath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	//add the texture id to textureIds map
	textureIds.insert(std::pair<string, GLuint>(name, id));
}

GLuint Textures::GetTexture(string name)
{
	//check if the texture has been added
	if (textureIds.count(name) == 0)
	{
		Debug::Error("Trying to get a texture that has not been added. Name: " + name);
		return 0;
	}

	//return the texture with that name
	return textureIds.find(name)->second;
}
