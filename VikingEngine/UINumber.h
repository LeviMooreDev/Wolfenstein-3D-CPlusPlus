#pragma once
#include "DLLHelper.h"
#include "UIBase.h"
#include <iostream>

typedef std::basic_string<char> string;

class UINumber : public UIBase
{
private:
	unsigned int texture;
	bool hasTexture;

public:
	int number;

	DLLEXTERN UINumber(string textureName);
	DLLEXTERN ~UINumber();

	void Draw();
};

