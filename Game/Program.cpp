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
#include "FreeCameraMovement.h"
#include "DemoCubeMovement.h"
#include "FloorBuilder.h"
#include "Textures.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <iterator>
#include <string_view>
#include "Player.h"
#include "Collider.h"
#include "UIImage.h"
#include "Enemy.h"
#include "Audio.h"

typedef std::basic_string<char> string;

Scene * mainScene;
GameObject * player;
GameObject * freeCamera;

void LoadAssets()
{
	Textures::AddTexture("stone wall", "stone wall");
	Textures::AddTexture("handgun frame 1", "handgun_1");
	Textures::AddTexture("handgun frame 2", "handgun_2");
	Textures::AddTexture("handgun frame 3", "handgun_3");
	Textures::AddTexture("handgun frame 4", "handgun_4");
	Textures::AddTexture("handgun frame 5", "handgun_5");
	Textures::AddTexture("guard idle", "guard_idle");
	Textures::AddTexture("guard dead", "guard_dead");
	Audio::Add("pistol", "pistol");
	Audio::Add("enemy hit", "enemy_hit");
	Audio::Add("enemy death 1", "enemy_death_1");
	Audio::Add("enemy death 2", "enemy_death_2");
}

void SetupFreeCamera()
{
	freeCamera = new GameObject();
	freeCamera->enabled = false;
	freeCamera->AddComponent(new Camera());
	freeCamera->AddComponent(new FreeCameraMovement());
	mainScene->AddGameObject(freeCamera);
}
void SetupLevel(int levelNumber)
{
	char **levelCells = nullptr;

	//load file
	std::ifstream file("Levels/level" + std::to_string(levelNumber) + ".l");
	string rawData;
	std::getline(file, rawData);

	//split string by ,
	std::vector<std::string> cleanData;
	std::string tmp;
	std::istringstream splitStream(rawData);
	while (std::getline(splitStream, tmp, ','))
	{
		cleanData.push_back(tmp);
	}

	//place data into 2d array
	bool readSize = true;
	int size = 0;
	int xPosition = 0;
	int zPosition = 0;
	for(auto const& data: cleanData)
	{
		if (readSize)
		{
			size = std::stoi(data);
			levelCells = new char*[size];
			for (int i = 0; i < size; i++)
				levelCells[i] = new char[size];

			readSize = false;
		}
		else
		{
			levelCells[xPosition][zPosition] = data[0];

			xPosition++;
			if (xPosition == size)
			{
				xPosition = 0;
				zPosition++;
			}
		}
	}

	//turn 2d array into game objects
	int cellSize = 3;
	int wallHeight = 4;
	float enemyHeight = 3;

	player = new GameObject();
	for (int x = 0; x < size; x++)
	{
		for (int z = 0; z < size; z++)
		{
			char c = levelCells[x][z];

			//wall
			if (c == 'w')
			{
				GameObject * wall = new GameObject();
				wall->name = "Wall";

				//transform
				wall->transform.position = Vector3(x * cellSize, wallHeight / 2.0, z * cellSize);
				wall->transform.scale = Vector3(cellSize, wallHeight, cellSize);

				//collider
				Collider * collider = new Collider();
				collider->size = Vector3(cellSize, wallHeight, cellSize);
				wall->AddComponent(collider);

				//mesh
				MeshRenderer * meshRenderer = new MeshRenderer();

				std::vector<float> * allVertices = new std::vector<float>();
				int verticesCount = 0;

				std::vector<float> * allUVs = new std::vector<float>();
				
				//left
				if (x != 0 && levelCells[x - 1][z] != 'w')
				{
					verticesCount += 4;
					float newVertices[12] =
					{
						-.5, .5, -.5,   -.5, .5,  .5,
						-.5,  -.5,  .5,   -.5,  -.5, -.5
					};
					allVertices->insert(allVertices->begin(), std::begin(newVertices), std::end(newVertices));

					float uv[8] = { 0, 1, .5, 1, .5, 0, 0, 0, };
					allUVs->insert(allUVs->begin(), std::begin(uv), std::end(uv));
				}

				//right
				if (x != size - 1 && levelCells[x + 1][z] != 'w')
				{
					verticesCount += 4;
					float newVertices[12] =
					{
						.5, -.5, -.5,    .5, -.5,  .5,   
						.5,  .5,  .5,    .5,  .5, -.5,
					};
					allVertices->insert(allVertices->begin(), std::begin(newVertices), std::end(newVertices));

					float uv[8] = { .5, 0, 0, 0, 0, 1, .5, 1, };
					allUVs->insert(allUVs->begin(), std::begin(uv), std::end(uv));
				}

				//forward
				if (z != size - 1 && levelCells[x][z + 1] != 'w')
				{
					verticesCount += 4;
					float newVertices[12] =
					{
						 .5,  .5,  -.5,   -.5,  .5,  -.5,
						 -.5, -.5,  -.5,    .5, -.5,  -.5
					};
					allVertices->insert(allVertices->begin(), std::begin(newVertices), std::end(newVertices));

					float uv[8] = { .5, 1, 1, 1, 1, 0, .5, 0, };
					allUVs->insert(allUVs->begin(), std::begin(uv), std::end(uv));
				}

				//back
				if (z != 0 && levelCells[x][z - 1] != 'w')
				{
					verticesCount += 4;
					float newVertices[12] =
					{
						 .5, -.5,  .5,   -.5, -.5,  .5,
						 -.5,  .5,  .5,    .5,  .5,  .5
					};
					allVertices->insert(allVertices->begin(), std::begin(newVertices), std::end(newVertices));

					float uv[8] = { 1, 0, .5, 0, .5, 1, 1, 1, };
					allUVs->insert(allUVs->begin(), std::begin(uv), std::end(uv));
				}

				meshRenderer->SetVertices(allVertices->data(), verticesCount);
				meshRenderer->SetTexture("stone wall", allUVs->data(), false);
				wall->AddComponent(meshRenderer);

				//add or remove wall
				if (verticesCount == 0)
				{
					delete allVertices;
					delete allUVs;
					delete collider;
					delete meshRenderer;
					delete wall;
				}
				else
				{
					mainScene->AddGameObject(wall);
				}
			}
			
			//floor
			else
			{
				GameObject * floor = new GameObject();
				floor->name = "Floor";

				floor->transform.position = Vector3(x * cellSize, 0, z * cellSize);
				floor->transform.scale = Vector3(cellSize, 0, cellSize);

				MeshRenderer * meshRenderer = new MeshRenderer();
				meshRenderer->SetVertices(new float[12]
					{
						.5,  0, -.5,   .5,  0,  .5,
						-.5, -0,  .5,   -.5, 0, -.5,
					}, 4);
				meshRenderer->SetColor(0.2);
				floor->AddComponent(meshRenderer);

				mainScene->AddGameObject(floor);
			}

			//enemy
			if (c == 'e')
			{
				GameObject * enemy = new GameObject();
				enemy->tag = "Enemy";
				enemy->transform.position = Vector3(x * cellSize, enemyHeight / 2, z * cellSize);
				enemy->transform.scale = Vector3::One() * enemyHeight;

				MeshRenderer * meshRenderer = new MeshRenderer();
				meshRenderer->SetVertices(new float[12]{ .5, -.5, 0,   -.5, -.5, 0, -.5, .5, 0,    .5, .5, 0 }, 4);
				meshRenderer->SetColor(255, 0, 0);
				enemy->AddComponent(meshRenderer);

				Collider * collider = new Collider();
				collider->size = Vector3(1, 2, 1);
				enemy->AddComponent(collider);

				enemy->AddComponent(new Enemy(player, meshRenderer));

				mainScene->AddGameObject(enemy);
			}

			//player start position
			if (c == 'p')
			{
				player->transform.position = Vector3(x * cellSize, 1.5, z * cellSize);

				player->AddComponent(new Camera(true));

				Player * playerCom = new Player();
				player->AddComponent(playerCom);

				MeshRenderer * meshRenderer = new MeshRenderer();
				meshRenderer->SetVertices(new float[12]{ -.2, .5, -.2 , .2, .5, -.2 , .2,  .5, .2 ,-.2, .5, .2 }, 4);
				meshRenderer->SetColor(0, 255, 0);
				player->AddComponent(meshRenderer);

				Collider * collider = new Collider();

				player->AddComponent(collider);
				collider->ListenForTrigger(std::bind(&Player::OnWallHit, playerCom, std::placeholders::_1));

				mainScene->AddGameObject(player);
			}
		}
	}

	delete[] levelCells;
}
void SetupUI()
{
	UIImage * image = new UIImage();
	mainScene->AddUIElement(image);
}

static int a;

//runs once when the game start
void Start()
{
	mainScene = new Scene();
	Engine::I()->activeScene = mainScene;

	LoadAssets();
	SetupFreeCamera();
	SetupLevel(0);
	SetupUI();
}

//runs every frame
void GameLoop()
{
	if (Input::KeyDown(Input::Keys::N1))
	{
		player->GetComponent(Player().GetName())->enabled = true;
		((Camera *)player->GetComponent(Camera().GetName()))->Use();

		freeCamera->enabled = false;
	}

	if (Input::KeyDown(Input::Keys::N2))
	{
		player->GetComponent(Player().GetName())->enabled = false;

		freeCamera->enabled = true;
		((Camera *)freeCamera->GetComponent(Camera().GetName()))->Use();
	}

	if (Input::KeyDown(Input::Keys::N3))
		Collider::showWireframe = !Collider::showWireframe;

	if (Input::KeyDown(Input::Keys::N4))
		MeshRenderer::showWireframe = !MeshRenderer::showWireframe;

	if (Input::KeyDown(Input::Keys::ESCAPE))
		Engine::I()->Close();
}

//where the program enters
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	new Engine("Robotenstein 3D", 800, 600, &Start, &GameLoop);
	return 0;
}