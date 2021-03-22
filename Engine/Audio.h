#pragma once
#include "DLLHelper.h"
#include <iostream>
#include <unordered_map>
typedef std::basic_string<char> string;

//used to play sound with
class Audio
{
private:
	//list of audio ids. 
	//we use this to assign names to audio clips that we then can use later when referencing the clip we want to play
	static std::unordered_map<string, string> audioClips;

public:
	//does some work to make sure the audio engine is ready for use
	static void Setup();

	//play a audio clip with the given name
	DLLEXTERN static void Play(string name);
	//play a random audio clip with one the given names
	//names: array of audio clip names
	//count: size of array
	DLLEXTERN static void PlayRandom(string * names, int count);
	//assign a name to an audio clip
	//name: name of the audio clip
	//file: file name of the audio name
	DLLEXTERN static void Add(string name, string file);
};

