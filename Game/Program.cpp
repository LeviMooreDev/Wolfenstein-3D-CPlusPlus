/*
Welcome to the land of spaghetti code.
*/

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
#include "LookAt.h"
#include "Gold.h"
#include "Door.h"
#include "Health.h"
#include "UINumber.h"

typedef std::basic_string<char> string;

//intro
Scene * introScene;
GameObject * introCameraGameObject;
Camera * introCameraComponent;
UIImage * introBackground;

//game
bool loadGame = true;
Scene * gameScene;
GameObject * player;
Player * playerCom;
GameObject * freeCamera;

UIImage * handImage;
UIImage * hudWeapon;
UINumber * hudGold;
UINumber * hudHealth;

void LoadAssets()
{
	Textures::AddTexture("door", "door");
	Textures::AddTexture("door frame", "door_frame");
	Textures::AddTexture("stone wall", "stone wall");
	Textures::AddTexture("wood wall", "wood wall");
	Textures::AddTexture("blue wall", "blue wall");
	Textures::AddTexture("pistol animation", "pistol");
	Textures::AddTexture("knife animation", "knife");
	Textures::AddTexture("guard idle", "guard_idle");
	Textures::AddTexture("guard dead", "guard_dead");
	Textures::AddTexture("object 1", "object_1");
	Textures::AddTexture("object 2", "object_2");
	Textures::AddTexture("object 3", "object_3");
	Textures::AddTexture("gold 1", "gold_1");
	Textures::AddTexture("gold 2", "gold_2");
	Textures::AddTexture("gold 3", "gold_3");
	Textures::AddTexture("gold 4", "gold_4");
	Textures::AddTexture("health", "health_pickup");
	Textures::AddTexture("hud", "hud");
	Textures::AddTexture("hud knife", "hud knife");
	Textures::AddTexture("hud pistol", "hud pistol");
	Textures::AddTexture("hud numbers", "numbers");
	Audio::Add("pistol", "pistol");
	Audio::Add("knife", "knife");
	Audio::Add("enemy hit", "enemy_hit");
	Audio::Add("enemy death 1", "enemy_death_1");
	Audio::Add("enemy death 2", "enemy_death_2");
	Audio::Add("pickup", "pickup");
	Audio::Add("health", "health");
	Audio::Add("door", "door");
}

void SetupFreeCamera()
{
	freeCamera = new GameObject();
	freeCamera->enabled = false;
	freeCamera->AddComponent(new Camera());
	freeCamera->AddComponent(new FreeCameraMovement());
	gameScene->AddGameObject(freeCamera);
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
	int wallHeight = 3;
	float enemyHeight = 2.75f;
	float objectHeight = 3;

	player = new GameObject();
	playerCom = new Player(handImage, hudWeapon, hudGold, hudHealth);
	for (int x = 0; x < size; x++)
	{
		for (int z = 0; z < size; z++)
		{
			char c = levelCells[x][z];

			if (c == ' ')
				continue;

			//wall
			if (c == 's' || c == 'w'|| c == 'b')
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
				if (x != 0 && levelCells[x - 1][z] != 'w' && levelCells[x - 1][z] != 'b' && levelCells[x - 1][z] != 's')
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
				if (x != size - 1 && levelCells[x + 1][z] != 'w' && levelCells[x + 1][z] != 'b' && levelCells[x + 1][z] != 's')
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
				if (z != size - 1 && levelCells[x][z + 1] != 'w' && levelCells[x][z + 1] != 'b' && levelCells[x][z + 1] != 's')
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
				if (z != 0 && levelCells[x][z - 1] != 'w' && levelCells[x][z - 1] != 'b' && levelCells[x][z - 1] != 's')
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
				if (c == 's')
					meshRenderer->SetTexture("stone wall", allUVs->data(), false);
				if (c == 'w')
					meshRenderer->SetTexture("wood wall", allUVs->data(), false);
				if (c == 'b')
					meshRenderer->SetTexture("blue wall", allUVs->data(), false);
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
					gameScene->AddGameObject(wall);
				}
			}
			
			//enemy
			if (c == 'e')
			{
				GameObject * enemy = new GameObject();
				enemy->distanceToCameraIsImportant = true;
				enemy->tag = "Enemy";
				enemy->transform.position = Vector3(x * cellSize, enemyHeight / 2.0f, z * cellSize);
				enemy->transform.scale = Vector3::One() * enemyHeight;

				MeshRenderer * meshRenderer = new MeshRenderer();
				meshRenderer->SetVertices(new float[12]{ .5, -.5, 0,   -.5, -.5, 0, -.5, .5, 0,    .5, .5, 0 }, 4);
				meshRenderer->SetColor(255, 0, 0);
				enemy->AddComponent(meshRenderer);

				Collider * collider = new Collider();
				collider->size = Vector3(1, 2, 1);
				enemy->AddComponent(collider);

				enemy->AddComponent(new LookAt(player));
				enemy->AddComponent(new Enemy(player, meshRenderer));

				gameScene->AddGameObject(enemy);
			}

			//objects
			if (c == 'o')
			{
				GameObject * object = new GameObject();
				object->distanceToCameraIsImportant = true;
				object->transform.position = Vector3(x * cellSize, objectHeight / 2.0f, z * cellSize);
				object->transform.scale = Vector3::One() * objectHeight;

				MeshRenderer * meshRenderer = new MeshRenderer();
				meshRenderer->SetVertices(new float[12]{ .5, -.5, 0,   -.5, -.5, 0, -.5, .5, 0,    .5, .5, 0 }, 4);
				string textures[3] = { "object 1", "object 1", "object 3" };
				float * uv = new float [8]{ 0,0,  1,0,
											1,1,  0,1, };
				meshRenderer->SetTextureRandom(textures, 3, uv, true);
				object->AddComponent(meshRenderer);

				Collider * collider = new Collider();
				collider->center = Vector3(0, -.75f, 0);
				collider->size = Vector3(1, .5f, 1);
				object->AddComponent(collider);

				object->AddComponent(new LookAt(player));

				gameScene->AddGameObject(object);
			}

			//gold
			if (c == 'g')
			{
				GameObject * gold = new GameObject();
				gold->distanceToCameraIsImportant = true;
				gold->transform.position = Vector3(x * cellSize, objectHeight / 2.0f, z * cellSize);
				gold->transform.scale = Vector3::One() * objectHeight;

				MeshRenderer * meshRenderer = new MeshRenderer();
				meshRenderer->SetVertices(new float[12]{ .5, -.5, 0,   -.5, -.5, 0, -.5, .5, 0,    .5, .5, 0 }, 4);
				string textures[4] = { "gold 1", "gold 1", "gold 3", "gold 4" };
				float * uv = new float[8]{ 0,0, 1,0, 1,1, 0,1,};
				meshRenderer->SetTextureRandom(textures, 4, uv, true);
				gold->AddComponent(meshRenderer);

				Gold * goldCom = new Gold(player);
				gold->AddComponent(goldCom);

				Collider * collider = new Collider();
				collider->solid = false;
				collider->size = Vector3(1, 2, 1);
				collider->ListenForTrigger(std::bind(&Gold::Hit, goldCom, std::placeholders::_1));
				gold->AddComponent(collider);

				gold->AddComponent(new LookAt(player));

				gameScene->AddGameObject(gold);
			}

			//health
			if (c == 'h')
			{
				GameObject * health = new GameObject();
				health->distanceToCameraIsImportant = true;
				health->transform.position = Vector3(x * cellSize, objectHeight / 2.0f, z * cellSize);
				health->transform.scale = Vector3::One() * objectHeight;

				MeshRenderer * meshRenderer = new MeshRenderer();
				meshRenderer->SetVertices(new float[12]{ .5, -.5, 0,   -.5, -.5, 0, -.5, .5, 0,    .5, .5, 0 }, 4);
				float * uv = new float[8]{ 0,0, 1,0, 1,1, 0,1, };
				meshRenderer->SetTexture("health", uv, true);
				health->AddComponent(meshRenderer);

				Health * healthCom = new Health(player);
				health->AddComponent(healthCom);

				Collider * collider = new Collider();
				collider->solid = false;
				collider->size = Vector3(1, 2, 1);
				collider->ListenForTrigger(std::bind(&Health::Hit, healthCom, std::placeholders::_1));
				health->AddComponent(collider);

				health->AddComponent(new LookAt(player));

				gameScene->AddGameObject(health);
			}

			//door
			if (c == 'd')
			{
				bool flipDoor = ((z != size - 1 && levelCells[x][z + 1] == 's') || (z != 0 && levelCells[x][z - 1] == 's')) ||
								((z != size - 1 && levelCells[x][z + 1] == 'w') || (z != 0 && levelCells[x][z - 1] == 'w')) ||
								((z != size - 1 && levelCells[x][z + 1] == 'b') || (z != 0 && levelCells[x][z - 1] == 'b'));
				{//door
					GameObject * door = new GameObject();
					door->transform.position = Vector3(x * cellSize, wallHeight / 2.0f, z * cellSize);
					door->transform.scale = Vector3(cellSize, wallHeight, cellSize);

					if (flipDoor)
						door->transform.rotation = Vector3(0, 90, 0);

					MeshRenderer * meshRenderer = new MeshRenderer();
					meshRenderer->SetVertices(new float[12]{ .5, -.5, 0,   -.5, -.5, 0, -.5, .5, 0,    .5, .5, 0,}, 4);
					if (flipDoor)
					{
						float * uv = new float[8]{ 0,0, 1,0, 1,1, 0,1, };
						meshRenderer->SetTexture("door", uv, false);
					}
					else
					{
						float * uv = new float[8]{ 1,0, 0,0, 0,1, 1,1, };
						meshRenderer->SetTexture("door", uv, false);
					}
					meshRenderer->doubleSided = true;
					door->AddComponent(meshRenderer);

					//collider
					Collider * collider = new Collider();
					collider->size = Vector3(cellSize, wallHeight, 0.6f);

					if (flipDoor)
						collider->size = Vector3(0.6f, wallHeight, cellSize);

					door->AddComponent(collider);

					door->AddComponent(new Door(player, collider));

					gameScene->AddGameObject(door);
				}
			
				{//frame
					GameObject * frame = new GameObject();
					frame->transform.position = Vector3(x * cellSize, wallHeight / 2.0f, z * cellSize);
					frame->transform.scale = Vector3(cellSize, wallHeight, cellSize);

					if (flipDoor)
						frame->transform.rotation = Vector3(0, 90, 0);

					MeshRenderer * meshRenderer = new MeshRenderer();
					meshRenderer->SetVertices(new float[24]{ .495,  .5, -.5,   .495,  .5,  .5,
															 .495, -.5,  .5,   .495, -.5, -.5,

															-.495, -.5, -.5,  -.495, -.5,  .5,
															-.495,  .5,  .5,  -.495,  .5, -.5, }, 8);
					float * uv = new float[16]{ 0,0, 1,0, 1,1, 0,1,
												0,0, 1,0, 1,1, 0,1 };
					meshRenderer->SetTexture("door frame", uv, false);
					frame->AddComponent(meshRenderer);

					gameScene->AddGameObject(frame);
				}
			}

			//player
			if (c == 'p')
			{
				player->transform.position = Vector3(x * cellSize, 1.5, z * cellSize);

				Camera * camera = new Camera(true);
				camera->backgroundColor = Color(BYTE(55));
				//camera->backgroundColorTop = Color(BYTE(55));
				//camera->backgroundColorBot = Color(BYTE(112));
				player->AddComponent(camera);

				player->AddComponent(playerCom);

				MeshRenderer * meshRenderer = new MeshRenderer();
				meshRenderer->SetVertices(new float[12]{ -.2, .5, -.2 , .2, .5, -.2 , .2,  .5, .2 ,-.2, .5, .2 }, 4);
				meshRenderer->SetColor(0, 255, 0);
				player->AddComponent(meshRenderer);

				Collider * collider = new Collider();
				collider->size = Vector3(1, 2, 1);

				player->AddComponent(collider);
				
				gameScene->AddGameObject(player);
			}
		}
	}
	//floor
	GameObject * floor = new GameObject();

	floor->transform.position = Vector3(size / 2 * cellSize, 0, size / 2 * cellSize);
	floor->transform.scale = Vector3(size * cellSize, 1, size * cellSize);

	MeshRenderer * meshRenderer = new MeshRenderer();
	meshRenderer->SetVertices(new float[12]
	{
		-.5, 0,-.5,    .5, 0,-.5,
		 .5, 0, .5,   -.5, 0, .5
	}, 4);
	meshRenderer->SetColor(0.44f);
	floor->AddComponent(meshRenderer);

	gameScene->AddGameObject(floor);


	delete[] levelCells;
}
void SetupGameUI()
{
	UIImage * hud = new UIImage();
	hud->size = Vector2(800, 90);
	hud->position = Vector2(Engine::I()->GetWindowSize().x / 2 - hud->size.x / 2, 0);
	hud->SetTexture("hud", new float[8]{ 0, 0, 0, 1, 1, 1, 1, 0, });
	gameScene->AddUIElement(hud);

	hudWeapon = new UIImage();
	hudWeapon->size = Vector2(160, 80);
	hudWeapon->position = Vector2(Engine::I()->GetWindowSize().x - hudWeapon->size.x, 5);
	gameScene->AddUIElement(hudWeapon);

	handImage = new UIImage();
	handImage->size = Vector2(400, 400);
	handImage->position = Vector2(Engine::I()->GetWindowSize().x / 2 - handImage->size.x / 2, hud->size.y);
	gameScene->AddUIElement(handImage);

	hudHealth = new UINumber("hud numbers");
	hudHealth->number = 100;
	hudHealth->size = Vector2(20, 40);
	hudHealth->position = Vector2(455, 10);
	hudHealth->order = 0.1f;
	gameScene->AddUIElement(hudHealth);

	hudGold = new UINumber("hud numbers");
	hudGold->number = 0;
	hudGold->size = Vector2(20, 40);
	hudGold->position = Vector2(190, 10);
	hudGold->order = 0.1f;
	gameScene->AddUIElement(hudGold);
}

static int a;

//runs once when the game start
void Start()
{
	Textures::AddTexture("intro", "intro");
	introScene = new Scene();
	introCameraGameObject = new GameObject();
	introCameraComponent = new Camera();
	introCameraComponent->Use();
	introCameraGameObject->AddComponent(introCameraComponent);
	introScene->AddGameObject(introCameraGameObject);

	introBackground = new UIImage();
	introBackground->SetTexture("intro", new float[8]{ 0, 0, 0, 1, 1, 1, 1, 0, });
	introBackground->size = Vector2(800, 600);
	introBackground->position = Vector2(0, 0);
	introScene->AddUIElement(introBackground);

	Engine::I()->activeScene = introScene;
}

//runs every frame
void GameLoop()
{
	if (loadGame)
	{
		loadGame = false;
		gameScene = new Scene();
		LoadAssets();
		SetupGameUI();
		SetupFreeCamera();
		SetupLevel(1);
		Engine::I()->activeScene = gameScene;
		
		delete introScene;
		delete introCameraGameObject;
		delete introCameraComponent;
		delete introBackground;

		loadGame = false;
	}
	else
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
}

//where the program enters
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	new Engine("Wolfenstein Real 3D", 800, 600, &Start, &GameLoop);
	return 0;
}