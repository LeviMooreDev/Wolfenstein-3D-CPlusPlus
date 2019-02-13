#include <iostream>
#include <Windows.h>
#include <Engine.h>
#include <Scene.h>
#include <GameObject.h>
#include <Debug.h>
#include <MeshRenderer.h>
#include <Time.h>
#include <Input.h>


Scene * mainScene;
GameObject * gameObject;

float targetScale = 1;

//runs once when the game start
void Start(Engine * engine)
{
	mainScene = new Scene();
	engine->activeScene = mainScene;
	
	gameObject = new GameObject();

	float * vertices = new float[72]
	{
		-1, -1, -1,   -1, -1,  1,   -1,  1,  1,   -1,  1, -1,
		 1, -1, -1,    1, -1,  1,    1,  1,  1,    1,  1, -1,
		-1, -1, -1,   -1, -1,  1,    1, -1,  1,    1, -1, -1,
		-1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,
		-1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,
		-1, -1,  1,   -1,  1,  1,    1,  1,  1,    1, -1,  1
	};
	float * colors = new float[72]
	{
		0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
		1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
		0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
		0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1

	};
	MeshRenderer * meshRenderer = new MeshRenderer(vertices, colors);

	gameObject->AddComponent(meshRenderer);
	mainScene->AddGameObject(gameObject);
}

//runs every frame
void GameLoop(Engine * engine)
{
	gameObject->transform.scale = gameObject->transform.scale.Lerp(Vector3::One(targetScale), Time::GetDeltaTime() * 2);
	gameObject->transform.position = Vector3(sin(Time::GetTimeSinceStart()) * 1.5f, cos(Time::GetTimeSinceStart() * 3) * 1, 0);
	gameObject->transform.rotation += Vector3::Up(90) * Time::GetDeltaTime();
	gameObject->transform.rotation += Vector3::Right(130) * Time::GetDeltaTime();
	gameObject->transform.rotation += Vector3::Forward(100) * Time::GetDeltaTime();

	if (Input::KeyDown(Input::Keys::N1))
	{
		targetScale = 1;
	}
	if (Input::KeyDown(Input::Keys::N2))
	{
		targetScale = .5f;
	}
	if (Input::KeyDown(Input::Keys::N3))
	{
		targetScale = .5f;
	}
	if (Input::KeyDown(Input::Keys::ESCAPE))
	{
		engine->Close();
	}
}

//where the program enters
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	new Engine("Robotenstein 3D", 800, 600, &Start, &GameLoop);
	return 0;
}