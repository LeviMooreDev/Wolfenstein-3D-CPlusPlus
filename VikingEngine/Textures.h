#pragma once
#include "DLLHelper.h"
#include <iostream>
#include <unordered_map>

typedef std::basic_string<char> string;

class Textures
{
private:
	static std::unordered_map<string, unsigned int> textureIds;

public:
	DLLEXTERN static void AddTexture(string name, string path);
	DLLEXTERN static unsigned int GetTexture(string name);
};

