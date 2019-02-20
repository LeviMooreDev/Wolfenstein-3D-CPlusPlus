#pragma once
#include "DLLHelper.h"
#include <iostream>
#include <unordered_map>
typedef std::basic_string<char> string;

class Audio
{
private:
	static std::unordered_map<string, string> audioIds;

public:
	static void Setup();

	DLLEXTERN static void Play(string name);
	DLLEXTERN static void PlayRandom(string * names, int count);
	DLLEXTERN static void Add(string name, string file);
};

