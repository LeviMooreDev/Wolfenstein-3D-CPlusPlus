#include "Raycast.h"
#include "GameObject.h"
#include <unordered_set>
#include "Engine.h"
#include "Collider.h"
#include "Vector2.h"
#include "Vector3.h"

GameObject * Raycast::Send(Vector3 origin, Vector3 direction, Vector3 & point, GameObject * ignore)
{
	//websites that explain raycasting
	//https://en.wikipedia.org/wiki/Ray_casting
	//https://lodev.org/cgtutor/raycasting.html
	//http://antongerdelan.net/opengl/raycasting.html

	//normalize the direction vector
	direction.Normalize();

	//the game object we are going to return
	GameObject * nearestHit = nullptr;

	//if there is no active scene return nullptr
	if (Engine::I()->activeScene == nullptr)
		return nearestHit;

	//loop game objects in active scene
	std::vector<GameObject *>::iterator gameObject = Engine::I()->activeScene->GetAllGameObjects()->begin();
	while (gameObject != Engine::I()->activeScene->GetAllGameObjects()->end())
	{
		//ignore if we are told
		if ((*gameObject) == ignore)
			goto endloop;

		//ignore if the game object is not enabled
		if (!(*gameObject)->enabled)
			goto endloop;

		//ignore if the game object does not have a collider component
		if (!(*gameObject)->HasColliders())
			goto endloop;

		//we use a scope here so we can bypass the code using goto
		{
			//get the game objects collider component
			Collider * collider = (Collider *)(*gameObject)->GetComponent(ColliderComponentName);

			if (!collider->enabled)
				goto endloop;

			if (!collider->solid)
				goto endloop;

			//find the min and max x,y,z values for the collider
			Vector3 min = collider->Min();
			Vector3 max = collider->Max();

			//vectors to hold the t values
			Vector3 t1, t2; 

			double t_near = -DBL_MAX;
			double t_far = DBL_MAX;

			//0 = x, 1 = y, 2 = z
			for (int i = 0; i < 3; i++)
			{
				//check if we will ever be able to hit the game object
				if (direction[i] == 0)
				{
					if ((origin[i] < min[i]) || (origin[i] > max[i]))
						goto endloop;
					else
						continue;
				}

				//calculate new t values
				t1[i] = (min[i] - origin[i]) / direction[i];
				t2[i] = (max[i] - origin[i]) / direction[i];

				if (t1[i] > t2[i])
					std::swap(t1, t2);
				if (t1[i] > t_near)
					t_near = t1[i];
				if (t2[i] < t_far)
					t_far = t2[i];

				if ((t_near > t_far) || (t_far < 0))
					goto endloop;
			}

			//if this is the first object we hit
			//or if it is closer than the current nearest hit
			if (nearestHit == nullptr || origin.Distance((*gameObject)->transform.position) < origin.Distance(nearestHit->transform.position))
			{
				//replace nearest hit and calculate hit point
				nearestHit = (*gameObject);
				point = origin + direction * t_near;
			}
		}

	endloop:
		gameObject++;
	}

	return nearestHit;
}