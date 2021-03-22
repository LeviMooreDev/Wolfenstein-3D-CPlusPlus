#pragma once
#include "DLLHelper.h"
#include "UIBase.h"
#include <iostream>

typedef std::basic_string<char> string;

//use to write numbers on the screen with
class UINumber : public UIBase
{
private:
	//texture with the number images we want to use
	unsigned int texture;
	//true if we have a texture to use
	bool hasTexture;

public:
	//the number to display
	int number;

	//textureName: name of the texture with the number images we want to use
	DLLEXTERN UINumber(string textureName);

	//draws the numbers to the screen. called every frame
	void Draw();
};

