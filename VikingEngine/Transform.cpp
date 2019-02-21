#include "Transform.h"
#include "Vector3.h"
#include "Debug.h"

Vector3 Transform::Up()
{
	return Vector3(0, 1, 0).Rotate(Vector3::Right(), rotation.x).Rotate(Vector3::Up(), rotation.y).Rotate(Vector3::Forward(), rotation.z);
}
Vector3 Transform::Down()
{
	return Vector3(0, -1, 0).Rotate(Vector3::Right(), rotation.x).Rotate(Vector3::Up(), rotation.y).Rotate(Vector3::Forward(), rotation.z);
}
Vector3 Transform::Right()
{
	return Vector3(1, 0, 0).Rotate(Vector3::Right(), rotation.x).Rotate(Vector3::Up(), rotation.y).Rotate(Vector3::Forward(), rotation.z);
}
Vector3 Transform::Left()
{
	return Vector3(-1, 0, 0).Rotate(Vector3::Right(), rotation.x).Rotate(Vector3::Up(), rotation.y).Rotate(Vector3::Forward(), rotation.z);
}
Vector3 Transform::Forward()
{
	return Vector3(0, 0, 1).Rotate(Vector3::Right(), rotation.x).Rotate(Vector3::Up(), rotation.y).Rotate(Vector3::Forward(), rotation.z);
}
Vector3 Transform::Back()
{
	return Vector3(0, 0, -1).Rotate(Vector3::Right(), rotation.x).Rotate(Vector3::Up(), rotation.y).Rotate(Vector3::Forward(), rotation.z);
}

