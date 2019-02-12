#include "Transform.h"

Transform::Transform()
{
	position = new Vector3(0, 0, 0);
	scale = new Vector3(1, 1, 1);
	rotating = new Vector3(0, 0, 0);
}
Transform::~Transform()
{
	delete position;
	delete scale;
	delete rotating;
}

void Transform::SetPosition(Vector3 * vector)
{
	delete position;
	position = vector;
}
Vector3 Transform::GetPosition()
{
	return *position;
}

void Transform::SetScale(Vector3 * vector)
{
	delete scale;
	scale = vector;
}
Vector3 Transform::GetScale()
{
	return *scale;
}

void Transform::SetRotating(Vector3 * vector)
{
	delete rotating;
	rotating = vector;
}
Vector3 Transform::GetRotating()
{
	return *rotating;
}