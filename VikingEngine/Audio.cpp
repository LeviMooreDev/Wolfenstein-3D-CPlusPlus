#include "Audio.h"
#include "Debug.h"
#include <iostream>
#include <irrKlang/irrKlang.h>
#include <thread>
typedef std::basic_string<char> string;
using namespace irrklang;

std::unordered_map<string, string> Audio::audioIds;
static ISoundEngine * engine = nullptr;

void Audio::Setup()
{
	engine = createIrrKlangDevice();
	if (!engine)
	{
		Debug::Error("Failed to create irrklang engine");
		engine = nullptr;
	}
}

void Audio::Play(string name)
{
	if (audioIds.count(name) != 1)
	{
		Debug::Error("Trying to play a sound that does not exists. Name: " + name);
	}

	if (engine != nullptr)
	{
		engine->play2D(audioIds.find(name)->second.c_str());
	}
}

void Audio::PlayRandom(string * names, int count)
{
	int index = (rand() %(count));
	Play(names[index]);
}

void Audio::Add(string name, string file)
{
	if (audioIds.count(name) != 0)
	{
		Debug::Error("Trying to add two sounds with the same name. Name: " + name + ". File: " + file);
	}

	string fullPath = ".\\Audio/" + file + ".wav";
	audioIds.insert(std::pair<string, string>(name, fullPath));
}
