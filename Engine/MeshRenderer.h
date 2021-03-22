#pragma once
#include "DLLHelper.h"
#include "Component.h"
#include "GameObject.h"
#define MeshRendererComponentName "Mesh Renderer"

//responsible for drawing a mesh and its texture on the screen
class MeshRenderer : public Component
{
private:
	//texture to draw
	unsigned int texture;
	//used to decide what part of a texture to use and where to draw it
	float * uv = nullptr;
	//is the texture transparent somewhere
	bool isTransparent;

	//mesh vertices
	float * vertices = nullptr;
	//amount of vertices
	int verticesCount;
	//true of the mesh has vertices
	bool hasVertices;

	//called on the first draw call
	void Draw1(Scene * scene);
	//called on the second draw call
	void Draw2(Scene * scene);
	
	//draws the mesh. called by Draw1() and Draw2()
	void DrawMesh();

public:
	//true if we want to draw both sides of the mesh
	bool doubleSided;

	DLLEXTERN MeshRenderer() {};
	DLLEXTERN ~MeshRenderer();

	//add vertice set. removes old set when called
	//vertices: vertices we want to add
	//verticesCount: amount of vertices we are adding
	DLLEXTERN void SetVertices(float * vertices, int verticesCount);

	//set texture
	//texture: the texture we want to use
	//uv: the uv we want to use
	//isTransparent: true if the texture is transparent somewhere
	DLLEXTERN void SetTexture(string texture, float * uv, bool isTransparent);

	//set a random texture
	//textures: array of texture we can pick
	//count: size of the array of textures
	//uv: the uv we want to use
	//isTransparent: true if the texture is transparent somewhere
	DLLEXTERN void SetTextureRandom(string textures[], int count, float * texture_coord, bool isTransparent);

	//returns the component name
	string GetName() { return MeshRendererComponentName; };
};

