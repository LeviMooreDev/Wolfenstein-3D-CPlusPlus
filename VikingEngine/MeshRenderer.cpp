#include "MeshRenderer.h"
#include "Debug.h"
#include <GLFW\glfw3.h>

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

void MeshRenderer::Update(GameObject * go)
{
	glPushMatrix();

	//position
	glTranslatef(go->transform.position.x, go->transform.position.y, go->transform.position.z);

	//rotation
	glRotatef(go->transform.rotation.x, 1, 0, 0);
	glRotatef(go->transform.rotation.y, 0, 1, 0);
	glRotatef(go->transform.rotation.z, 0, 0, 1);

	//scale
	glScalef(go->transform.scale.x, go->transform.scale.y, go->transform.scale.z);

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
