#pragma once
#include "DLLHelper.h"
#include "Component.h"
#include "GameObject.h"

class MeshRenderer : public Component
{
private:
	unsigned int texture;
	float * texture_coord;
	bool useTexture;
	bool useAlpha;

	float * colors;
	bool useColor;

	float * vertices;
	int verticesCount;
	bool hasVertices;

	void Draw();
	void Draw1(Scene * scene);
	void Draw2(Scene * scene);

public:
	DLLEXTERN static bool showWireframe;

	DLLEXTERN MeshRenderer();
	DLLEXTERN ~MeshRenderer();

	DLLEXTERN void SetVertices(float * vertices, int verticesCount);
	DLLEXTERN void SetTexture(string texture, float * texture_coord, bool useAlpha);
	DLLEXTERN void SetColor(float * colors);
	DLLEXTERN void SetColor(float color);
	DLLEXTERN void SetColor(float r, float g, float b);

	string GetName() { return "Mesh Renderer"; };
};

