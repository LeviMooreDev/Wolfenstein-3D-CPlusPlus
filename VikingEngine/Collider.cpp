#include "Collider.h"
#include "Scene.h"
#include <GLFW\glfw3.h>
#include <iostream>
#include "Debug.h"
#include "Raycast.h"
typedef std::basic_string<char> string;

bool Collider::showWireframe = false;

Collider::Collider()
{
	(*this).onHit = nullptr;
}
Collider::~Collider()
{
}

void Collider::ListenForHit(std::function<void(GameObject *)> onHit)
{
	(*this).onHit = onHit;
}
void Collider::ListenForTrigger(std::function<void(GameObject *)> onTrigger)
{
	(*this).onTrigger = onTrigger;
}

Vector3 Collider::Min()
{
	return Vector3(gameObject->transform.position.x - center.x - size.x / 2,
				   gameObject->transform.position.y - center.y - size.y / 2,
				   gameObject->transform.position.z - center.z - size.z / 2);
}
Vector3 Collider::Max()
{
	return Vector3(gameObject->transform.position.x + center.x + size.x / 2,
				   gameObject->transform.position.y + center.y + size.y / 2,
				   gameObject->transform.position.z + center.z + size.z / 2);
}

void Collider::Update(Scene * scene)
{
checkAgain:
	if (lastCenter == center && lastSize == size && lastPosition == gameObject->transform.position)
		return;
	lastCenter = center;
	lastSize = size;
	lastPosition = gameObject->transform.position;

	Vector3 selfMin = Min();
	Vector3 selfMax = Max();

	std::unordered_set<GameObject *>::iterator otherGameObject = scene->GetAllGameObjects()->begin();
	while (otherGameObject != scene->GetAllGameObjects()->end())
	{
		if ((*otherGameObject) != gameObject && (*otherGameObject)->enabled)
		{
			if ((*otherGameObject)->HasColliders())
			{
				Collider * otherCollider = (Collider *)(*otherGameObject)->GetComponent(Collider().GetName());
				if (otherCollider->enabled)
				{
					Vector3 otherMin = otherCollider->Min();
					Vector3 otherMax = otherCollider->Max();

					if ((selfMax.x > otherMin.x && selfMin.x < otherMax.x && selfMax.y > otherMin.y && selfMin.y < otherMax.y && selfMax.z > otherMin.z && selfMin.z < otherMax.z))
					{
						if (solid)
						{
							//right
							Vector3 normal = Vector3();
							if (selfMin.x < otherMin.x)
							{
								gameObject->transform.position -= Vector3(selfMax.x - otherMin.x, 0, 0);
								goto checkAgain;
							}
							//left
							else if (selfMax.x > otherMax.x)
							{
								gameObject->transform.position += Vector3(otherMax.x - selfMin.x, 0, 0);
								goto checkAgain;
							}
							//forward
							else if (selfMin.z < otherMin.z)
							{
								gameObject->transform.position -= Vector3(0, 0, selfMax.z - otherMin.z);
								goto checkAgain;
							}
							//back
							else if (selfMax.z > otherMax.z)
							{
								gameObject->transform.position += Vector3(0, 0, otherMax.z - selfMin.z);
								goto checkAgain;
							}

							if (onHit != nullptr)
								onHit(otherCollider->gameObject);
						}
						else
						{
							if (onTrigger != nullptr)
								onTrigger(otherCollider->gameObject);
						}
					}
				}
			}
		}

		otherGameObject++;
	}
}
void Collider::Draw2(Scene * scene)
{
	if (!Collider::showWireframe)
		return;

	//glDepthMask(true);

	glPushMatrix();

	//position
	glTranslatef(gameObject->transform.position.x + center.x, gameObject->transform.position.y + center.y, -gameObject->transform.position.z - center.z);

	//scale
	glScalef(size.x, size.y, size.z);

	//draw as wireframe
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_DEPTH_TEST);

	//vertices
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, colors);

	//draw
	glDrawArrays(GL_QUADS, 0, 24);

	//cleanup
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();
}