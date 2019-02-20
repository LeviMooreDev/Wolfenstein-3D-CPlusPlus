#include "UIImage.h"
#include <GLFW\glfw3.h>
#include "Textures.h"


UIImage::UIImage()
{
}
UIImage::~UIImage()
{
	delete (*this).texture_coord;
}

void UIImage::SetTexture(string textureName, float * texture_coord)
{
	delete (*this).texture_coord;

	texture = Textures::GetTexture(textureName);
	(*this).texture_coord = texture_coord;
	hasTexture = true;
}

void UIImage::Draw()
{
	if (!hasTexture)
		return;

	glPushMatrix();

	//position
	glTranslatef(position.x, position.y, order);

	//scale
	glScalef(size.x, size.y, 1);

	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, texture);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_QUADS);
		glTexCoord2f(texture_coord[0], texture_coord[1]);
		glVertex2f(0, 0);

		glTexCoord2f(texture_coord[2], texture_coord[3]);
		glVertex2f(0, 1);

		glTexCoord2f(texture_coord[4], texture_coord[5]);
		glVertex2f(1, 1);

		glTexCoord2f(texture_coord[6], texture_coord[7]);
		glVertex2f(1, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
