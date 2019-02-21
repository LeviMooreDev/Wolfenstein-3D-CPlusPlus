#pragma once
#include "DLLHelper.h"
#include "Vector2.h"

//the base class all ui elements inherit from
class UIBase
{
private:
	//id of the next ui element that is created.
	static int nextId;
	//id of the ui element. is unique and automatically assigned.
	int id;

public:
	//if false the draw method is not called
	bool enabled = true;
	//position of the ui element in pixels
	Vector2 position;
	//size of the ui element in pixels
	Vector2 size;

	UIBase();

	//called every frame
	virtual void Draw() {};

	//returns the ui elements id
	DLLEXTERN int GetId() const;
};

