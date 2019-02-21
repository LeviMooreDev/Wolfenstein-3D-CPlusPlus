#pragma once
#include "DLLHelper.h"
#include "UIBase.h"
#include "Vector2.h"
#include <iostream>

typedef std::basic_string<char> string;

//use to draw images on the screen in 2d
class UIImage : public UIBase
{
private:
	//texture to draw
	unsigned int texture;
	//used to decide what part of a texture to use and where to draw it
	float * uvs;
	//true if the uimage has a texture
	bool hasTexture;

public:

	DLLEXTERN UIImage() { };
	DLLEXTERN ~UIImage();

	//set texture
	//texture: the texture we want to use
	//uv: the uv we want to use
	DLLEXTERN void SetTexture(string textureName, float * uv);

	//draws the image to the screen. called every frame
	void Draw();
};

