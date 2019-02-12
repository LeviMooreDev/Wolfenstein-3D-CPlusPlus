#pragma once
#include "DLLHelper.h"
#include <iostream>

typedef std::basic_string<char> string;

class GameObject;

class DLLEXTERN Component
{
public:
	Component();
	~Component();

	virtual void Update(GameObject * go) { };
	virtual string GetName() { return "Component"; };
};

