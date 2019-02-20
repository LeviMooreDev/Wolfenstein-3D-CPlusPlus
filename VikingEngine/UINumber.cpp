#include "UINumber.h"
#include <GLFW\glfw3.h>
#include "Textures.h"
#include <iostream>
#include <string>

typedef std::basic_string<char> string;

UINumber::UINumber(string textureName)
{
	texture = Textures::GetTexture(textureName);
	hasTexture = true;
}


UINumber::~UINumber()
{
}

void UINumber::Draw()
{
	if (!hasTexture)
		return;

	float dirStep = 1.0f / 10.0f;
	string numberAsString = std::to_string(number);
	std::reverse(numberAsString.begin(), numberAsString.end());

	for (float i = 0.0f; i < numberAsString.length(); i++)
	{
		char cn = numberAsString[i];
		float startX = (cn - '0') * dirStep;
		float endX = startX + dirStep;
		float texture_coord[8] = { startX, 0, startX, 1, endX, 1, endX, 0, };

		glPushMatrix();

		glEnable(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, texture);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//position
		glTranslatef(position.x - i * size.x, position.y, order);

		//scale
		glScalef(size.x, size.y, 1);

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

		//delete texture_coord;
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
}
