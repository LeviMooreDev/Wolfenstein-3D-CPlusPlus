#include "Collider.h"
#include "Scene.h"
#include <GLFW\glfw3.h>
#include <iostream>
#include "Debug.h"
#include "Raycast.h"
typedef std::basic_string<char> string;

//declare static fields
bool Collider::showWireframe = false;

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
	return Vector3(gameObject->transform.position.x - centerOffset.x - size.x / 2.0f,
				   gameObject->transform.position.y - centerOffset.y - size.y / 2.0f,
				   gameObject->transform.position.z - centerOffset.z - size.z / 2.0f);
}
Vector3 Collider::Max()
{
	return Vector3(gameObject->transform.position.x + centerOffset.x + size.x / 2.0f,
				   gameObject->transform.position.y + centerOffset.y + size.y / 2.0f,
				   gameObject->transform.position.z + centerOffset.z + size.z / 2.0f);
}

void Collider::Update(Scene * scene)
{
	//if we have not changed position, center offset or size we dont need to check for collision
	if (lastCenterOffset == centerOffset && lastSize == size && lastValidPosition == gameObject->transform.position)
		return;

	//true if we need to check for collision
	bool checkForCollision = true;
	//the amount of times we are allowed to recheck for collision
	int checkCountLeft = 5;

	//if we want to check for a collision
	while (checkForCollision)
	{
		checkForCollision = false;

		//we are going to use min and max x,y,z a lot so we store them here for faster access later
		Vector3 selfMin = Min();
		Vector3 selfMax = Max();

		//loop through all game objects in the scene
		std::vector<GameObject *>::iterator otherGameObject = scene->GetAllGameObjects()->begin();
		while (otherGameObject != scene->GetAllGameObjects()->end())
		{
			//if the game object we are at is not ourself and it is enabled
			if ((*otherGameObject) != gameObject && (*otherGameObject)->enabled)
			{
				//if it has a collider on it
				if ((*otherGameObject)->HasColliders())
				{
					//get the collider component and check if it is enabled
					Collider * otherCollider = (Collider *)(*otherGameObject)->GetComponent(ColliderComponentName);
					if (otherCollider->enabled)
					{
						//get the min and max x,y,z value of the other collider
						Vector3 otherMin = otherCollider->Min();
						Vector3 otherMax = otherCollider->Max();

						//if our box is inside the other box
						if ((selfMax.x > otherMin.x && selfMin.x < otherMax.x && selfMax.y > otherMin.y && selfMin.y < otherMax.y && selfMax.z > otherMin.z && selfMin.z < otherMax.z))
						{
							//if the other box is solid
							if (otherCollider->solid)
							{
								//if we are solid
								if (solid)
								{
									//                  ------------------
									//		   ---------|------          |
									//		   |    minX|     |          |
									//	       |        |< w >|  other   |
									//		   |  self  |     |maxX      |
									//		   |        ------|-----------
									//		   ----------------
									//w = abs(minX - maxX)
									//self.position -= w
									//                  ----------------
									//  ----------------|              |
									//	|              ||              |
									//	|              ||    other     |
									//	|    self      ||              |
									//	|              |----------------
									//	----------------

									//the amount we want to move our game object to avoid being inside the other game object
									Vector3 move = Vector3();

									//if we are to the right of the other game object subtract the amount we are inside the other game object to our x position
									//see the beautiful drawing above for visual explanation
									//#to the right
									if (gameObject->transform.position.x < (*otherGameObject)->transform.position.x)
									{
										Vector3 newMove = Vector3(-abs(selfMax.x - otherMin.x), 0, 0);

										//only set move to newMove if the amount we want to move is less than what we already want to move
										//we only use the smallest move amount for every collision check to avoid being pushed into another game collider that then do the same
										if (move == Vector3() || move.Distance(Vector3()) > newMove.Distance(Vector3()))
											move = newMove;
									}

									//left, right, forward and back checks are almost the same

									//# behind
									if (gameObject->transform.position.z > (*otherGameObject)->transform.position.z)
									{
										Vector3 newMove = Vector3(0, 0, abs(otherMax.z - selfMin.z));

										if (move == Vector3() || move.Distance(Vector3()) > newMove.Distance(Vector3()))
											move = newMove;
									}

									//# to the right
									if (gameObject->transform.position.x > (*otherGameObject)->transform.position.x)
									{
										Vector3 newMove = Vector3(abs(selfMin.x - otherMax.x), 0, 0);

										if (move == Vector3() || move.Distance(Vector3()) > newMove.Distance(Vector3()))
											move = newMove;
									}

									//# infront
									if (gameObject->transform.position.z < (*otherGameObject)->transform.position.z)
									{
										Vector3 newMove = Vector3(0, 0, -abs(otherMin.z - selfMax.z));

										if (move == Vector3() || move.Distance(Vector3()) > newMove.Distance(Vector3()))
											move = newMove;
									}

									//if we want to move the game object
									if (move != Vector3())
									{
										//move the game object
										gameObject->transform.position += move;
										
										//remove a collision check
										checkCountLeft--;

										//if we have no more collision checks left, reset the game object position to the last known valid position
										//this should not happen except if the game object is placed in a closed area smaller then itself
										if (checkCountLeft == 0)
										{
											gameObject->transform.position = lastValidPosition;
										}
										//if we are allowed to use more collision checks, stop the code here and return to the beginning
										else
										{
											checkForCollision = true;
											break;
										}
									}

									//call the onHit method on our self and the other game object
									if (onHit != nullptr)
										onHit(otherCollider->gameObject);

									if (otherCollider->onHit != nullptr)
										otherCollider->onHit(gameObject);
								}
							}
							else
							{
								//call the onTrigger method on our self and the other game object
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

	//set last center offset, size and valid position
	lastCenterOffset = centerOffset;
	lastSize = size;
	lastValidPosition = gameObject->transform.position;
}

void Collider::Draw2(Scene * scene)
{
	//if we dont want to draw a wireframe for our collision box return.
	if (!Collider::showWireframe)
		return;

	glPushMatrix();

	//set position
	glTranslatef(gameObject->transform.position.x + centerOffset.x, gameObject->transform.position.y + centerOffset.y, -gameObject->transform.position.z - centerOffset.z);

	//set scale
	glScalef(size.x, size.y, size.z);

	//set polygon mode to line to give the wireframe effect
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//disable depth test. we want to see all colliders even if they are behind other things
	glDisable(GL_DEPTH_TEST);

	//enable drawing by vertex and color arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, wireframeVertices);

	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, colors);

	//draw
	glDrawArrays(GL_QUADS, 0, 24);

	//cleanup
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();
}