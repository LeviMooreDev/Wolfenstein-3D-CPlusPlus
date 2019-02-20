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
	return Vector3(gameObject->transform.position.x - center.x - size.x / 2.0f,
				   gameObject->transform.position.y - center.y - size.y / 2.0f,
				   gameObject->transform.position.z - center.z - size.z / 2.0f);
}
Vector3 Collider::Max()
{
	return Vector3(gameObject->transform.position.x + center.x + size.x / 2.0f,
				   gameObject->transform.position.y + center.y + size.y / 2.0f,
				   gameObject->transform.position.z + center.z + size.z / 2.0f);
}

void Collider::Update(Scene * scene)
{
	if (lastCenter == center && lastSize == size && lastPosition == gameObject->transform.position)
		return;

	bool checkAgain = true;
	int checkCountLeft = 5;

	while (checkAgain)
	{
		checkAgain = false;

		Vector3 selfMin = Min();
		Vector3 selfMax = Max();

		std::vector<GameObject *>::iterator otherGameObject = scene->GetAllGameObjects()->begin();
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
							if (otherCollider->solid)
							{
								if (solid)
								{
									Vector3 move = Vector3();

									//right
									if (gameObject->transform.position.x < (*otherGameObject)->transform.position.x)
									{
										Vector3 newMove = Vector3(-abs(selfMax.x - otherMin.x), 0, 0);

										if (move == Vector3() || move.Distance(Vector3()) > newMove.Distance(Vector3()))
											move = newMove;
									}

									//back
									if (gameObject->transform.position.z > (*otherGameObject)->transform.position.z)
									{
										Vector3 newMove = Vector3(0, 0, abs(otherMax.z - selfMin.z));

										if (move == Vector3() || move.Distance(Vector3()) > newMove.Distance(Vector3()))
											move = newMove;
									}

									//left
									if (gameObject->transform.position.x > (*otherGameObject)->transform.position.x)
									{
										Vector3 newMove = Vector3(abs(selfMin.x - otherMax.x), 0, 0);

										if (move == Vector3() || move.Distance(Vector3()) > newMove.Distance(Vector3()))
											move = newMove;
									}

									//forward
									if (gameObject->transform.position.z < (*otherGameObject)->transform.position.z)
									{
										Vector3 newMove = Vector3(0, 0, -abs(otherMin.z - selfMax.z));

										if (move == Vector3() || move.Distance(Vector3()) > newMove.Distance(Vector3()))
											move = newMove;
									}

									if (move != Vector3())
									{
										gameObject->transform.position += move;
										checkCountLeft--;

										if (checkCountLeft == 0)
										{
											gameObject->transform.position = lastPosition;
										}
										else
										{
											checkAgain = true;
											break;
										}
									}

									if (onHit != nullptr)
										onHit(otherCollider->gameObject);

									if (otherCollider->onHit != nullptr)
										otherCollider->onHit(gameObject);
								}
							}
							else
							{
								if (onTrigger != nullptr)
									onTrigger(otherCollider->gameObject);

								if (otherCollider->onTrigger != nullptr)
									otherCollider->onTrigger(gameObject);
							}
						}
					}
				}
			}

			otherGameObject++;
		}
	}
	lastCenter = center;
	lastSize = size;
	lastPosition = gameObject->transform.position;
}
void Collider::Draw2(Scene * scene)
{
	if (!Collider::showWireframe)
		return;

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