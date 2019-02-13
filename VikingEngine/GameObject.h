#pragma once
#include "DLLHelper.h"
#include <unordered_set>
#include "Component.h"
#include "Transform.h"

typedef std::basic_string<char> string;

class GameObject
{
private:
	//id of the next game object that is created.
	static int nextId;
	//id of the game object. is unique and automatically assigned.
	int id;

	//list of components the game object has on it
	std::unordered_set<Component *> * components;
	std::unordered_map<const std::type_info *, Component *>

public:
	//name of the game object.
	string name = "NO NAME";
	Transform transform;

	DLLEXTERN GameObject();
	DLLEXTERN ~GameObject();

	//update the game objects components.
	void UpdateComponents();

	//add game object to scene. You can not add the same object twice.
	DLLEXTERN Component * AddComponent(Component * com);
	//remove game object from scene.
	DLLEXTERN void GetComponent(Type * com);
	//remove game object from scene.
	DLLEXTERN void RemoveComponent(Component * com);

	//returns game object id
	DLLEXTERN int GetId() const;

	// == and < operators for GameObject objects. We need to use unordered_set.
	bool operator==(const GameObject & other) const;
	bool operator<(const GameObject & other) const;
};

// hash function for GameObject objects. We need to use unordered_set.
namespace std
{
	template<>
	struct std::hash<GameObject>
	{
		std::size_t operator()(const GameObject & go) const
		{
			using std::size_t;
			using std::hash;
			using std::string;

			return hash<int>()(go.GetId());
		}
	};
}