#pragma once
#include "DLLHelper.h"
#include "Component.h"
#include "GameObject.h"

class MeshRenderer : public Component
{
private:
	unsigned int texture;
	float * texture_coord = nullptr;
	bool useAlpha;

	float * vertices = nullptr;
	int verticesCount;
	bool hasVertices;

	void Draw();
	void Draw1(Scene * scene);
	void Draw2(Scene * scene);

public:
	bool doubleSided;

	DLLEXTERN MeshRenderer();
	DLLEXTERN ~MeshRenderer();

	DLLEXTERN void SetVertices(float * vertices, int verticesCount);
	DLLEXTERN void SetTexture(string texture, float * texture_coord, bool useAlpha);
	DLLEXTERN void SetTextureRandom(string textures[], int count, float * texture_coord, bool useAlpha);

	string GetName() { return "Mesh Renderer"; };
};

