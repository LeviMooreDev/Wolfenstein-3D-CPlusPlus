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


void UINumber::Draw()
{
	//if there is no texture to draw return
	if (!hasTexture)
		return;

	//convert the numbers into a string and reverse it
	//we reverse it, because we are going to write from right to left
	string numberAsString = std::to_string(number);
	std::reverse(numberAsString.begin(), numberAsString.end());

	//loop numbers
	for (float i = 0.0f; i < numberAsString.length(); i++)
	{
		//get the current number
		char cn = numberAsString[i];
		//find the start and end uv x position in our texture that we are going to use
		float startX = (cn - '0') * 0.1f;
		float endX = startX + 0.1f;
		float uv[8] = { startX, 0, startX, 1, endX, 1, endX, 0, };

		glPushMatrix();

		//enable textures
		glEnable(GL_TEXTURE_2D);

		//enable textures and set filter mode to nearest, we want to use nearest to get a clear pixel art style
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, texture);

		//set polygon mode to fill so we draw the entire surface of the mesh
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//set position
		glTranslatef(position.x - i * size.x, position.y, 0);

		//set scale
		glScalef(size.x, size.y, 1);

		//draw number
		glBegin(GL_QUADS);
			glTexCoord2f(uv[0], uv[1]);
			glVertex2f(0, 0);

			glTexCoord2f(uv[2], uv[3]);
			glVertex2f(0, 1);

			glTexCoord2f(uv[4], uv[5]);
			glVertex2f(1, 1);

			glTexCoord2f(uv[6], uv[7]);
			glVertex2f(1, 0);
		glEnd();

		//cleanup
		glDisable(GL_TEXTURE_2D);

		glPopMatrix();
	}
}