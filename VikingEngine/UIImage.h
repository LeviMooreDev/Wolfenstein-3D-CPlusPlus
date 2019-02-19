#pragma once
#include "DLLHelper.h"
#include "UIBase.h"
#include "Vector2.h"
#include <iostream>

typedef std::basic_string<char> string;

class UIImage : public UIBase
{
private:
	unsigned int texture;
	float * texture_coord;
	bool hasTexture;

public:

	DLLEXTERN UIImage();
	DLLEXTERN ~UIImage();

	DLLEXTERN void SetTexture(string textureName, float * texture_coord);

	void Draw();
};

