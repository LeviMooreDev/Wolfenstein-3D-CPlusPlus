#include "UIImage.h"
#include <GLFW\glfw3.h>
#include "Textures.h"


UIImage::UIImage()
{
}
UIImage::~UIImage()
{
}

void UIImage::Draw()
{
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, Textures::GetTexture("handgun frame 1"));

	glPolygonMode(GL_FRONT, GL_FILL);

	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex2f(0, 0);

		glTexCoord2f(0, 1);
		glVertex2f(0, 128);

		glTexCoord2f(1, 1);
		glVertex2f(128, 128);

		glTexCoord2f(1, 0);
		glVertex2f(128, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
