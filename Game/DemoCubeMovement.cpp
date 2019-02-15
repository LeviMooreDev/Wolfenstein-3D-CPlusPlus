#include "DemoCubeMovement.h"
#include "Input.h"
#include "Vector3.h"
#include "GameObject.h"
#include "Time.h"

DemoCubeMovement::DemoCubeMovement()
{
}
DemoCubeMovement::~DemoCubeMovement()
{
}

void DemoCubeMovement::Update(Scene * scene)
{
	if (Input::KeyDown(Input::Keys::N1))
		targetScale = 1;
	if (Input::KeyDown(Input::Keys::N2))
		targetScale = .5f;
	if (Input::KeyUp(Input::Keys::N3))
		moveCube = !moveCube;

	gameObject->transform.scale = gameObject->transform.scale.Lerp(Vector3::One(targetScale), Time::GetDeltaTime() * 2);

	if (moveCube)
	{
		gameObject->transform.position = Vector3(sin(Time::GetTimeSinceStart()) * 1.5f, cos(Time::GetTimeSinceStart() * 3) * 1, 0);
		gameObject->transform.rotation += Vector3::Up(90) * Time::GetDeltaTime();
		gameObject->transform.rotation += Vector3::Right(130) * Time::GetDeltaTime();
		gameObject->transform.rotation += Vector3::Forward(100) * Time::GetDeltaTime();
	}
}
