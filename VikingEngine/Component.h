#pragma once
#include "DLLHelper.h"
#include <iostream>

typedef std::basic_string<char> string;

class GameObject;

class Component
{
public:
	bool enabled = true;

	virtual void Update(GameObject * go) { };
	virtual string GetName() { return "Component"; };
};

