#include "Audio.h"
#include "Debug.h"
#include <iostream>
#include <irrKlang/irrKlang.h>
#include <thread>

typedef std::basic_string<char> string;
using namespace irrklang;

//declare static fields
std::unordered_map<string, string> Audio::audioClips;

//the reason we define and declare engine here and not in the header file is because if we did the project using our Engine.dll file would also need to include irrKlang.lib
static ISoundEngine * engine = nullptr;

void Audio::Setup()
{
	//create a ISoundEngine using irrKlang
	engine = createIrrKlangDevice();
	if (!engine)
	{
		Debug::Error("Failed to create irrklang engine");
		engine = nullptr;
	}
}

void Audio::Play(string name)
{
	//check if an audio clip with that name exists
	if (audioClips.count(name) != 1)
	{
		Debug::Error("Trying to play a sound that does not exists. Name: " + name);
	}

	//if the irrKlang engine is not null play the sound
	if (engine != nullptr)
	{
		engine->play2D(audioClips.find(name)->second.c_str());
	}
}

void Audio::PlayRandom(string * names, int count)
{
	//call Play() with a random name from the names array
	int index = (rand() %(count));
	Play(names[index]);
}

void Audio::Add(string name, string file)
{
	//check if an audio clip with that name already exists
	if (audioClips.count(name) != 0)
	{
		Debug::Error("Trying to add two sounds with the same name. Name: " + name + ". File: " + file);
	}

	//find full path to file
	string fullPath = ".\\Audio/" + file + ".wav";
	
	//addd it to list of audio clips
	audioClips.insert(std::pair<string, string>(name, fullPath));
}
