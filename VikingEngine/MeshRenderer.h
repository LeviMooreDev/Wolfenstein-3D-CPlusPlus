#pragma once
#include "DLLHelper.h"
#include "Component.h"
#include "GameObject.h"

class MeshRenderer : public Component
{
private:
	float * vertices;
	float * colors;

public:
	DLLEXTERN MeshRenderer(float * vertices, float * colors);
	DLLEXTERN ~MeshRenderer();

	void Update(GameObject * go);
	string GetName() { return "Mesh Renderer"; };
};

