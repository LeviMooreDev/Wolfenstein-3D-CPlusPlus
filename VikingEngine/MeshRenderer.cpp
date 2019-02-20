#include "MeshRenderer.h"
#include "Debug.h"
#include <GLFW\glfw3.h>
#include <SOIL\SOIL.h>
#include "Textures.h"
#include <iostream>
typedef std::basic_string<char> string;

MeshRenderer::MeshRenderer()
{
}
MeshRenderer::~MeshRenderer()
{
	delete texture_coord;
	delete vertices;
}

void MeshRenderer::SetVertices(float * vertices, int verticesCount)
{
	delete (*this).vertices;

	(*this).verticesCount = verticesCount;
	(*this).vertices = vertices;
	hasVertices = true;
}
void MeshRenderer::SetTexture(string textureName, float * texture_coord, bool useAlpha)
{
	delete (*this).texture_coord;

	texture = Textures::GetTexture(textureName);
	(*this).texture_coord = texture_coord;
	(*this).useAlpha = useAlpha;
}
void MeshRenderer::SetTextureRandom(string textures[], int count, float * texture_coord, bool useAlpha)
{
	int index = (rand() % (count));
	SetTexture(textures[index], texture_coord, useAlpha);
}

void MeshRenderer::Draw()
{
	if (!hasVertices)
		return;

	glPushMatrix();

	//position
	glTranslatef(gameObject->transform.position.x, gameObject->transform.position.y, -gameObject->transform.position.z);

	//rotation
	glRotatef(gameObject->transform.rotation.x, 1, 0, 0);
	glRotatef(gameObject->transform.rotation.y, 0, 1, 0);
	glRotatef(gameObject->transform.rotation.z, 0, 0, 1);

	//scale
	glScalef(gameObject->transform.scale.x, gameObject->transform.scale.y, gameObject->transform.scale.z);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (doubleSided)
		glDisable(GL_CULL_FACE);
	else
		glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);

	//vertices
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texture_coord);

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
	glDepthMask(true);
	if (!useAlpha)
		Draw();
}
void MeshRenderer::Draw2(Scene * scene)
{
	glDepthMask(false);
	if (useAlpha)
		Draw();
}