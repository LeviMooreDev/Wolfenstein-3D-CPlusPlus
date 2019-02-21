#include "MeshRenderer.h"
#include "Debug.h"
#include <GLFW\glfw3.h>
#include <SOIL\SOIL.h>
#include "Textures.h"
#include <iostream>
typedef std::basic_string<char> string;


MeshRenderer::~MeshRenderer()
{
	delete uv;
	delete vertices;
}

void MeshRenderer::SetVertices(float * vertices, int verticesCount)
{
	//remove old vertices from memory
	delete (*this).vertices;

	//set new vertices
	(*this).verticesCount = verticesCount;
	(*this).vertices = vertices;

	hasVertices = true;
}
void MeshRenderer::SetTexture(string textureName, float * texture_coord, bool isTransparent)
{
	//remove old uvs from memory
	delete (*this).uv;

	//set new texture and uvs
	texture = Textures::GetTexture(textureName);
	(*this).uv = texture_coord;
	(*this).isTransparent = isTransparent;
}
void MeshRenderer::SetTextureRandom(string textures[], int count, float * texture_coord, bool isTransparent)
{
	//call SetTexture() with a random texture from the array
	int index = (rand() % (count));
	SetTexture(textures[index], texture_coord, isTransparent);
}

void MeshRenderer::DrawMesh()
{
	//if the mesh does not have any vertices stop here
	if (!hasVertices)
		return;

	glPushMatrix();

	//set position
	glTranslatef(gameObject->transform.position.x, gameObject->transform.position.y, -gameObject->transform.position.z);

	//set rotation
	glRotatef(gameObject->transform.rotation.x, 1, 0, 0);
	glRotatef(gameObject->transform.rotation.y, 0, 1, 0);
	glRotatef(gameObject->transform.rotation.z, 0, 0, 1);

	//set scale
	glScalef(gameObject->transform.scale.x, gameObject->transform.scale.y, gameObject->transform.scale.z);
	
	//set polygon mode to fill so we draw the entire surface of the mesh
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//disable cullface if we want to draw both sides, else enable it
	if (doubleSided)
		glDisable(GL_CULL_FACE);
	else
		glEnable(GL_CULL_FACE);

	//enable depth test, we dont want to draw objects that is behind things already drawn
	glEnable(GL_DEPTH_TEST);

	//enable drawing by vertex and texture coord (we we call uv) arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, uv);

	//enable textures and set filter mode to nearest, we want to use nearest to get a clear pixel art style
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	//bind texture
	glBindTexture(GL_TEXTURE_2D, texture);

	//draw
	glDrawArrays(GL_QUADS, 0, verticesCount);

	//cleanup
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
void MeshRenderer::Draw1(Scene * scene)
{
	//if we don't have transparency in our texture draw the mesh as part of the first draw call
	glDepthMask(true);
	if (!isTransparent)
		DrawMesh();
}
void MeshRenderer::Draw2(Scene * scene)
{
	//if we do have transparency in our texture draw the mesh as part of the second draw call
	glDepthMask(false);
	if (isTransparent)
		DrawMesh();
}