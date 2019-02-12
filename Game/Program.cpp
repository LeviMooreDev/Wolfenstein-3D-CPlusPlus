#include <iostream>
#include <Windows.h>
#include <Engine.h>
#include <Scene.h>
#include <GameObject.h>
#include <Debug.h>
#include <MeshRenderer.h>


Scene * testScene;
GameObject * go;

//runs once when the game start
void Start(Engine * engine)
{
	testScene = new Scene();
	engine->activeScene = testScene;
	
	go = new GameObject();
	go->AddComponent(new MeshRenderer());

	testScene->AddGameObject(go);


	Vector3 v1 = Vector3(0, 0, 0);
	Vector3 v2 = Vector3(0, 1, 1);


	Debug::Log(v1.Distance(v2));
}

//runs every frame
void GameLoop(Engine * engine)
{
	go->transform.rotation.MoveTowards(Vector3(0, 90, 0), .1);
}

//where the program enters
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	new Engine("Game Name", 800, 600, &Start, &GameLoop);
	return 0;
}