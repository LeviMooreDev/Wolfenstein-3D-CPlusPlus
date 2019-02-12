#pragma once
#include "DLLHelper.h"
#include "Component.h"
#include "GameObject.h"

class DLLEXTERN MeshRenderer : public Component
{
public:
	MeshRenderer();
	~MeshRenderer();

	void Update(GameObject * go);
	string GetName() { return "Mesh Renderer"; };
};

