#pragma once
#include "DLLHelper.h"
#include <iostream>

typedef std::basic_string<char> string;

class GameObject;
class Scene;

class Component
{
private:
	virtual void Update(Scene * scene) { };
	virtual void Draw1(Scene * scene) { };
	virtual void Draw2(Scene * scene) { };

protected:
	GameObject * gameObject = nullptr;

public:
	bool enabled = true;

	void SetParentGameObject(GameObject * gameObject);
	GameObject * GetParentGameObject();
	void RemoveParentGameObject();

	virtual string GetName() { return "Component"; };
	
	//We hide the Update method behind V_Update because when a method is public and virtual it is always visible outside the dll and we dont want that.
	//by doing it this way all other classes in the engine can still call the Update method without it being visible to the user outside the dll
	void V_Update(Scene * scene);
	void V_Draw1(Scene * scene);
	void V_Draw2(Scene * scene);
};

