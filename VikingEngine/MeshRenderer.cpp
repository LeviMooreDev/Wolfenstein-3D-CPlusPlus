#include "MeshRenderer.h"
#include "Debug.h"
#include <GLFW\glfw3.h>

MeshRenderer::MeshRenderer()
{
	(*this).vertices = nullptr;
	(*this).colors = nullptr;
}
MeshRenderer::MeshRenderer(float * vertices, float * colors)
{
	(*this).vertices = vertices;
	(*this).colors = colors;
}
MeshRenderer::~MeshRenderer()
{
	delete vertices;
	delete colors;
}

void MeshRenderer::Update(Scene * scene)
{
	glPushMatrix();

	//position
	glTranslatef(gameObject->transform.position.x, gameObject->transform.position.y, gameObject->transform.position.z);

	//rotation
	glRotatef(gameObject->transform.rotation.x, 1, 0, 0);
	glRotatef(gameObject->transform.rotation.y, 0, 1, 0);
	glRotatef(gameObject->transform.rotation.z, 0, 0, 1);

	//scale
	glScalef(gameObject->transform.scale.x, gameObject->transform.scale.y, gameObject->transform.scale.z);

	/* We have a color array and a vertex array */
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);

	/* Send data : 24 vertices */
	glDrawArrays(GL_QUADS, 0, 24);

	/* Cleanup states */
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();
}
