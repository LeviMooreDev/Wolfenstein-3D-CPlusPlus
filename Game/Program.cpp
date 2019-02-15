#include <iostream>
#include <Windows.h>
#include <Engine.h>
#include <Scene.h>
#include <GameObject.h>
#include <MeshRenderer.h>
#include <Debug.h>
#include <Time.h>
#include <Input.h>
#include <Color.h>
#include "CameraMovement.h"
#include "DemoCubeMovement.h"

Scene * mainScene;
GameObject * cube;
GameObject * camera;

//runs once when the game start
void Start()
{
	mainScene = new Scene();
	Engine::I()->activeScene = mainScene;

	cube = new GameObject();
	cube->transform.position = Vector3(0, 4, 0);
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
	cube->AddComponent(new MeshRenderer(vertices, colors, 24));
	cube->AddComponent(new DemoCubeMovement());
	mainScene->AddGameObject(cube);

	GameObject * floor = new GameObject();
	float * floorVertices = new float[12]
	{
		-10, 0, -10,   -10, 0,  10,   10,  0,  10,   10,  0, -10
	};
	float * floorColors = new float[12]
	{
		0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0
	};
	floor->AddComponent(new MeshRenderer(floorVertices, floorColors, 4));
	mainScene->AddGameObject(floor);

	camera = new GameObject();
	camera->transform.position = Vector3(0, 1, -7);
	camera->AddComponent(new Camera(true));
	camera->AddComponent(new CameraMovement());
	mainScene->AddGameObject(camera);
}

//runs every frame
void GameLoop()
{
	if (Input::KeyDown(Input::Keys::ESCAPE))
		Engine::I()->Close();
}

//where the program enters
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	new Engine("Robotenstein 3D", 800, 600, &Start, &GameLoop);
	return 0;
}