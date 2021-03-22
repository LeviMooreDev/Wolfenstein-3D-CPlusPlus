#include "UIImage.h"
#include <GLFW\glfw3.h>
#include "Textures.h"


UIImage::~UIImage()
{
	delete (*this).uvs;
}

void UIImage::SetTexture(string textureName, float * texture_coord)
{
	//free up memory used by the old uv
	delete (*this).uvs;
	
	//set new texture
	texture = Textures::GetTexture(textureName);
	(*this).uvs = texture_coord;
	hasTexture = true;
}

void UIImage::Draw()
{
	//if there is no texture to draw return
	if (!hasTexture)
		return;

	glPushMatrix();

	//set position
	glTranslatef(position.x, position.y, 0);

	//set scale
	glScalef(size.x, size.y, 1);

	//enable textures
	glEnable(GL_TEXTURE_2D);

	//enable textures and set filter mode to nearest, we want to use nearest to get a clear pixel art style
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, texture);

	//set polygon mode to fill so we draw the entire surface of the mesh
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//draw texture
	glBegin(GL_QUADS);
		glTexCoord2f(uvs[0], uvs[1]);
		glVertex2f(0, 0);

		glTexCoord2f(uvs[2], uvs[3]);
		glVertex2f(0, 1);

		glTexCoord2f(uvs[4], uvs[5]);
		glVertex2f(1, 1);

		glTexCoord2f(uvs[6], uvs[7]);
		glVertex2f(1, 0);
	glEnd();

	//cleanup
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
