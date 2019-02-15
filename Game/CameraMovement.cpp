#include "CameraMovement.h"
#include "Input.h"
#include "Vector3.h"
#include "GameObject.h"
#include "Time.h"
#include "Debug.h"

CameraMovement::CameraMovement()
{
	Input::HideCursor();
}
CameraMovement::~CameraMovement()
{
}

void CameraMovement::Update(Scene * scene)
{
	Move();
	Look();
}

void CameraMovement::Move()
{
	if (Input::KeyHold(Input::Keys::LEFT_ALT))
	{
		if (Input::KeyHold(Input::Keys::Q))
			gameObject->transform.position += Vector3::Up() * cameraSpeed * Time::GetDeltaTime();

		if (Input::KeyHold(Input::Keys::E))
			gameObject->transform.position += Vector3::Down() * cameraSpeed * Time::GetDeltaTime();

		if (Input::KeyHold(Input::Keys::W))
			gameObject->transform.position += gameObject->transform.Forward() * cameraSpeed * Time::GetDeltaTime();

		if (Input::KeyHold(Input::Keys::S))
			gameObject->transform.position += gameObject->transform.Back() * cameraSpeed * Time::GetDeltaTime();

		if (Input::KeyHold(Input::Keys::A))
			gameObject->transform.position += gameObject->transform.Left() * cameraSpeed * Time::GetDeltaTime();

		if (Input::KeyHold(Input::Keys::D))
			gameObject->transform.position += gameObject->transform.Right() * cameraSpeed * Time::GetDeltaTime();
	}
}

void CameraMovement::Look()
{
	if (Input::KeyHold(Input::Keys::LEFT_ALT))
	{
		gameObject->transform.rotation += Vector3::Up() * Input::MouseMoveDirection().x * lookSpeed * Time::GetDeltaTime();
		gameObject->transform.rotation += Vector3::Left() * Input::MouseMoveDirection().y * lookSpeed * Time::GetDeltaTime();
	}
}