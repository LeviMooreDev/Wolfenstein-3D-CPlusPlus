#pragma once
#include "DLLHelper.h"
#include <unordered_set>

typedef std::basic_string<char> string;

class DLLEXTERN GameObject
{
private:
	//id of the next game object that is created.
	static int nextId;

	//id of the game object. is unique and automatically assigned.
	int id;

public:
	//name of the game object.
	string name;

	GameObject();
	~GameObject();

	//returns game object id
	int GetId() const;

	// == and < operators for GameObject objects. We need to use unordered_set.
	bool operator==(const GameObject & other) const
	{
		return id == other.id;
	}
	bool operator<(const GameObject & other) const
	{
		return id < other.id;
	}
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