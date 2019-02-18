#pragma once
#include "DLLHelper.h"

class UIBase
{
private:
	//id of the next game object that is created.
	static int nextId;
	//id of the game object. is unique and automatically assigned.
	int id;

public:
	bool enabled = true;

	UIBase();

	virtual void Update() {};
	virtual void Draw() {};

	DLLEXTERN int GetId() const;

	bool operator==(const UIBase & other) const;
};
