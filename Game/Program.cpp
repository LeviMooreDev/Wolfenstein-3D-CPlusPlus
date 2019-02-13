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

Scene * mainScene;
GameObject * cube;
GameObject * camera;

float cameraSpeed = 15;
float targetScale = 1;
bool moveCube = true;

//runs once when the game start
void Start(Engine * engine)
{
	mainScene = new Scene();
	engine->activeScene = mainScene;
	
	cube = new GameObject();

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
	cube->AddComponent(meshRenderer);
	mainScene->AddGameObject(cube);

	camera = new GameObject();
	camera->transform.position = Vector3(0, 0, -7);
	camera->AddComponent(new Camera(true));
	mainScene->AddGameObject(camera);
}

void Input(Engine * engine)
{
	//cube
	if (Input::KeyDown(Input::Keys::N1))
		targetScale = 1;
	if (Input::KeyDown(Input::Keys::N2))
		targetScale = .5f;
	if (Input::KeyUp(Input::Keys::N3))
		moveCube = !moveCube;

	//camera
	if (Input::KeyHold(Input::Keys::Q))
		camera->transform.position += Vector3::Up() * cameraSpeed * Time::GetDeltaTime();
	if (Input::KeyHold(Input::Keys::E))
		camera->transform.position += Vector3::Down() * cameraSpeed * Time::GetDeltaTime();
	if (Input::KeyHold(Input::Keys::W))
		camera->transform.position += Vector3::Forward() * cameraSpeed * Time::GetDeltaTime();
	if (Input::KeyHold(Input::Keys::S))
		camera->transform.position += Vector3::Back() * cameraSpeed * Time::GetDeltaTime();
	if (Input::KeyHold(Input::Keys::A))
		camera->transform.position += Vector3::Left() * cameraSpeed * Time::GetDeltaTime();
	if (Input::KeyHold(Input::Keys::D))
		camera->transform.position += Vector3::Right() * cameraSpeed * Time::GetDeltaTime();

	//close
	if (Input::KeyDown(Input::Keys::ESCAPE))
		engine->Close();
}

//runs every frame
void GameLoop(Engine * engine)
{
	if (moveCube)
	{
		cube->transform.scale = cube->transform.scale.Lerp(Vector3::One(targetScale), Time::GetDeltaTime() * 2);
		cube->transform.position = Vector3(sin(Time::GetTimeSinceStart()) * 1.5f, cos(Time::GetTimeSinceStart() * 3) * 1, 0);
		cube->transform.rotation += Vector3::Up(90) * Time::GetDeltaTime();
		cube->transform.rotation += Vector3::Right(130) * Time::GetDeltaTime();
		cube->transform.rotation += Vector3::Forward(100) * Time::GetDeltaTime();
	}

	Input(engine);
}

//where the program enters
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	new Engine("Robotenstein 3D", 800, 600, &Start, &GameLoop);
	return 0;
}