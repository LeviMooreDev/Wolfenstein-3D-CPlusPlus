#pragma once
#include "DLLHelper.h"
#include <iostream>
#include <exception>
typedef std::basic_string<char> string;

//we create empty classes because we need them as parameters, but if we include them we end up in an endless loop of including
class GameObject;
class Scene;

//the base class all components inherit from
class Component
{
private:
	//called every frame
	virtual void Update(Scene * scene) { };

	//we have two draw methods so things that are important to draw last like transparent textures and collider wireframes can use Draw2 and everything else Draw1
	//called every frame before Draw2()
	virtual void Draw1(Scene * scene) { };
	//called every frame after Draw1()
	virtual void Draw2(Scene * scene) { };

public:
	//if false the update and draw methods is not called
	bool enabled = true;

	//the game object the component is on
	GameObject * gameObject = nullptr;

	//if a component has not overwritten GetName we throw an exception to let them know
	virtual string GetName() { throw "Component does not have a name"; };
	
	//We hide the Update method behind V_Update because when a method is public and virtual it is always visible outside the dll and we dont want that.
	//by doing it this way all other classes in the engine can still call the Update method using V_Update without it being visible to the user outside the dll
	void V_Update(Scene * scene);
	
	//same explanation as above
	void V_Draw1(Scene * scene);
	void V_Draw2(Scene * scene);
};

