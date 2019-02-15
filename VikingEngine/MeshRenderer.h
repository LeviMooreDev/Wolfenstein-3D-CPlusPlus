#pragma once
#include "DLLHelper.h"
#include "Component.h"
#include "GameObject.h"

class MeshRenderer : public Component
{
private:
	float * vertices;
	float * colors;
	int verticesCount;
	void Draw(Scene * scene);

public:
	DLLEXTERN MeshRenderer();
	DLLEXTERN MeshRenderer(float * vertices, float * colors, int verticesCount);
	DLLEXTERN ~MeshRenderer();

	string GetName() { return "Mesh Renderer"; };
};

