#include "FreeCameraMovement.h"
#include "Input.h"
#include "Vector3.h"
#include "GameObject.h"
#include "Time.h"
#include "Debug.h"


void FreeCameraMovement::Update(Scene * scene)
{
	Move();
	Look();
}

void FreeCameraMovement::Move()
{
	//if left shift is down fly faster
	if (Input::KeyHold(Input::Keys::LEFT_SHIFT))
		currentSpeed = fastSpeed;
	else
		currentSpeed = normalSpeed;

	//move up and down relative to the world
	if (Input::KeyHold(Input::Keys::Q))
		gameObject->transform.position += Vector3::Up() * currentSpeed * Time::GetDeltaTime();
	if (Input::KeyHold(Input::Keys::E))
		gameObject->transform.position += Vector3::Down() * currentSpeed * Time::GetDeltaTime();

	//move foward, back, left and right relative to self
	if (Input::KeyHold(Input::Keys::W))
		gameObject->transform.position += gameObject->transform.Forward() * currentSpeed * Time::GetDeltaTime();

	if (Input::KeyHold(Input::Keys::S))
		gameObject->transform.position += gameObject->transform.Back() * currentSpeed * Time::GetDeltaTime();

	if (Input::KeyHold(Input::Keys::A))
		gameObject->transform.position += gameObject->transform.Left() * currentSpeed * Time::GetDeltaTime();

	if (Input::KeyHold(Input::Keys::D))
		gameObject->transform.position += gameObject->transform.Right() * currentSpeed * Time::GetDeltaTime();
}

void FreeCameraMovement::Look()
{
	//rotate on y axis. left, right
	gameObject->transform.rotation += Vector3::Up() * Input::MouseMoveDirection().x * lookSpeed * Time::GetDeltaTime();

	//rotate on x axis. up, down.
	gameObject->transform.rotation += Vector3::Left() * Input::MouseMoveDirection().y * lookSpeed * Time::GetDeltaTime();
}