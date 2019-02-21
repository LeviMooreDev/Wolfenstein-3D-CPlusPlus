#pragma once
#include "DLLHelper.h"
#include <iostream>
#include <unordered_map>

typedef std::basic_string<char> string;

//used to store textures we can use when drawing on the screen
class Textures
{
private:
	//list of loaded textures
	static std::unordered_map<string, unsigned int> textureIds;

public:
	//add a new texture
	//name: name of the texture. this is what we are going to use to get it back later
	//path: name of the texture file
	DLLEXTERN static void AddTexture(string name, string path);

	//returns a texture with the given name
	DLLEXTERN static unsigned int GetTexture(string name);
};

