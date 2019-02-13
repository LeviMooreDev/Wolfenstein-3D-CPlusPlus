#include "Input.h"
#include <iostream> 
#include <iterator> 
#include <map>
#include "Debug.h"

std::map<int, bool> Input::hold = std::map<int, bool>();
std::map<int, bool> Input::down = std::map<int, bool>();
std::map<int, bool> Input::up	= std::map<int, bool>();

bool Input::KeyUp(Keys key)
{
	return Input::up[key];
}
bool Input::KeyDown(Keys key)
{
	return Input::down[key];
}
bool Input::KeyHold(Keys key)
{
	return Input::hold[key];
}

void Input::Setup()
{
	for (int i = Input::Keys::A; i != Input::Keys::MENU; i++)
	{
		Input::Keys key = static_cast<Input::Keys>(i);
		Input::hold.insert(std::pair<int, bool>((int)key, false));
		Input::down.insert(std::pair<int, bool>((int)key, false));
		Input::up.insert(std::pair<int, bool>((int)key, false));
	}
}
void Input::PreEventCollect()
{
	std::map<int, bool>::iterator c_itr;
	for (c_itr = down.begin(); c_itr != down.end(); ++c_itr)
	{
		Input::down[c_itr->first] = false;
	}
	for (c_itr = up.begin(); c_itr != up.end(); ++c_itr)
	{
		Input::up[c_itr->first] = false;
	}
}
void Input::EventCollectDown(int key)
{
	Input::down[key] = true;
	Input::hold[key] = true;
}
void Input::EventCollectUp(int key)
{
	Input::up[key] = true;
	Input::hold[key] = false;
}
