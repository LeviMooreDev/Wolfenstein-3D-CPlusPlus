/*
Welcome to the land of spaghetti code.
*/
#include "Game.h"
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
#include "EndGame.h"

typedef std::basic_string<char> string;

template<typename T>
void safe_delete(T*& a)
{
	delete a;
	a = nullptr;
}

bool Game::gameOver = false;
Scene * Game::winScene;
Scene * Game::deadScene;

Game::Game() {};
Game::~Game() {};


void Game::FreeMemory()
{
	safe_delete(introScene);
	safe_delete(gameScene);
	safe_delete(winScene);
	safe_delete(deadScene);
}
void Game::ResetGame()
{
	FreeMemory();

	introScene = new Scene();
	GameObject * cameraGameObject = new GameObject();
	Camera * cameraComponent = new Camera();
	introScene->activeCamera = cameraComponent;
	cameraGameObject->AddComponent(cameraComponent);
	introScene->AddGameObject(cameraGameObject);

	UIImage * background = new UIImage();
	background->SetTexture("intro", new float[8]{ 0, 0, 0, 1, 1, 1, 1, 0, });
	background->size = Vector2(800, 600);
	background->position = Vector2(0, 0);
	introScene->AddUIElement(background);

	Engine::I()->activeScene = introScene;
	gameOver = false;
	skipNextFrameAndResetGame = true;
}

void Game::LoadAssets()
{
	Textures::AddTexture("player", "player");

	Textures::AddTexture("floor", "floor");

	Textures::AddTexture("door", "door");
	Textures::AddTexture("door frame", "door_frame");

	Textures::AddTexture("stone wall 1", "stone_wall_1");
	Textures::AddTexture("stone wall 2", "stone_wall_2");
	Textures::AddTexture("stone wall 3", "stone_wall_3");

	Textures::AddTexture("wood wall 1", "wood_wall_1");
	Textures::AddTexture("wood wall 2", "wood_wall_2");
	Textures::AddTexture("wood wall 3", "wood_wall_3");

	Textures::AddTexture("blue wall 1", "blue_wall_1");

	Textures::AddTexture("end game", "end_game");

	Textures::AddTexture("pistol animation", "pistol");
	Textures::AddTexture("knife animation", "knife");

	Textures::AddTexture("guard idle", "guard_idle");
	Textures::AddTexture("guard dead", "guard_dead");
	Textures::AddTexture("guard hit", "guard_hit");
	Textures::AddTexture("guard fire", "guard_fire");

	Textures::AddTexture("object 1", "object_1");
	Textures::AddTexture("object 2", "object_2");
	Textures::AddTexture("object 3", "object_3");
	Textures::AddTexture("object 4", "object_4");
	Textures::AddTexture("object 5", "object_5");

	Textures::AddTexture("gold 1", "gold_1");
	Textures::AddTexture("gold 2", "gold_2");
	Textures::AddTexture("gold 3", "gold_3");
	Textures::AddTexture("gold 4", "gold_4");

	Textures::AddTexture("health", "health_pickup");

	Textures::AddTexture("hud", "hud");
	Textures::AddTexture("hud knife", "hud knife");
	Textures::AddTexture("hud pistol", "hud pistol");
	Textures::AddTexture("hud numbers", "numbers");

	Textures::AddTexture("intro", "intro");
	Textures::AddTexture("win background", "win_background");
	Textures::AddTexture("dead background", "dead_background");

	Audio::Add("player hit 1", "player_hit_1");
	Audio::Add("player hit 2", "player_hit_1");
	Audio::Add("player dead", "player_dead");

	Audio::Add("silence", "silence");
	Audio::Add("win", "yeeeah");
	Audio::Add("pistol", "pistol");
	Audio::Add("knife", "knife");
	Audio::Add("enemy hit", "enemy_hit");
	Audio::Add("enemy death 1", "enemy_death_1");
	Audio::Add("enemy death 2", "enemy_death_2");
	Audio::Add("pickup", "pickup");
	Audio::Add("health", "health");
	Audio::Add("door", "door");
	Audio::Play("silence");
}

void Game::SetupFreeCamera()
{
	freeCamera = new GameObject();
	freeCamera->enabled = false;
	freeCamera->AddComponent(new Camera());
	freeCamera->AddComponent(new FreeCameraMovement());
	gameScene->AddGameObject(freeCamera);
}
void Game::SetupLevel(int levelNumber)
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
	for (auto const& data : cleanData)
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
	float cellSize = 3;
	float wallHeight = 3;
	float enemyHeight = 2.75f;
	float objectHeight = 3;

	player = new GameObject();
	player->tag = "Player";
	playerCom = new Player(handImage, hudWeapon, hudGold, hudHealth);
	player->AddComponent(playerCom);
	for (int x = 0; x < size; x++)
	{
		for (int z = 0; z < size; z++)
		{
			char c = levelCells[x][z];

			if (c == ' ')
				continue;

			//walls
			if (c == 's' || c == 'w' || c == 'b' || c == 'x')
			{
				GameObject * wall = new GameObject();

				//transform
				wall->transform.position = Vector3(x * cellSize, wallHeight / 2.0f, z * cellSize);
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
				{
					string textures[10] = { "stone wall 1", "stone wall 1", "stone wall 1", "stone wall 1", "stone wall 1", "stone wall 1", "stone wall 1", "stone wall 1", "stone wall 2", "stone wall 3" };
					meshRenderer->SetTextureRandom(textures, 10, allUVs->data(), false);
				}
				else if (c == 'w')
				{
					string textures[10] = { "wood wall 1", "wood wall 1", "wood wall 1", "wood wall 1", "wood wall 1", "wood wall 1", "wood wall 1", "wood wall 1", "wood wall 2", "wood wall 3" };
					meshRenderer->SetTextureRandom(textures, 10, allUVs->data(), false);
				}
				else if (c == 'b')
				{
					meshRenderer->SetTexture("blue wall 1", allUVs->data(), false);
				}
				else if (c == 'x')
				{
					meshRenderer->SetTexture("end game", allUVs->data(), false);
					wall->AddComponent(new EndGame(player));
				}

				wall->AddComponent(meshRenderer);

				//add or remove wall
				if (verticesCount == 0)
				{
					delete allVertices;
					delete allUVs;
					delete wall;
				}
				else
				{
					gameScene->AddGameObject(wall);
				}
			}

			//enemy
			if (c == 'e' || c == 'k')
			{
				GameObject * enemy = new GameObject();
				enemy->distanceToCameraIsImportant = true;
				enemy->tag = "Enemy";
				enemy->transform.position = Vector3(x * cellSize, enemyHeight / 2.0f, z * cellSize);
				enemy->transform.scale = Vector3::One() * enemyHeight;

				MeshRenderer * meshRenderer = new MeshRenderer();
				meshRenderer->SetVertices(new float[12]{ .5, -.5, 0,   -.5, -.5, 0, -.5, .5, 0,    .5, .5, 0 }, 4);
				enemy->AddComponent(meshRenderer);

				Collider * collider = new Collider();
				collider->size = Vector3(1, 2, 1);
				enemy->AddComponent(collider);

				enemy->AddComponent(new LookAt(player));

				Enemy * enemyCom = new Enemy(player, meshRenderer);
				enemy->AddComponent(enemyCom);
				if (c == 'e')
				{
					float rx = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					float rz = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

					enemyCom->lookDir = Vector3(rx, 0.0f, rz).Normalized();
				}
				else
				{
					enemyCom->ignorePlayer = true;
					enemyCom->lookDir = Vector3::Right();
					enemyCom->hp = 1;
				}

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
				string textures[5] = { "object 1", "object 2", "object 3", "object 4", "object 5" };
				meshRenderer->SetTextureRandom(textures, 5, new float[8]{ 0,0,  1,0, 1,1,  0,1, }, true);
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
				meshRenderer->SetTextureRandom(textures, 4, new float[8]{ 0,0, 1,0, 1,1, 0,1, }, true);
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
				meshRenderer->SetTexture("health", new float[8]{ 0,0, 1,0, 1,1, 0,1, }, true);
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
					meshRenderer->SetVertices(new float[12]{ .5, -.5, 0,   -.5, -.5, 0, -.5, .5, 0,    .5, .5, 0, }, 4);
					if (flipDoor)
						meshRenderer->SetTexture("door", new float[8]{ 0,0, 1,0, 1,1, 0,1, }, false);
					else
						meshRenderer->SetTexture("door", new float[8]{ 1,0, 0,0, 0,1, 1,1, }, false);
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
					meshRenderer->SetVertices(new float[24]{ .495f,  .5, -.5,   .495f,  .5,  .5,
															 .495f, -.5,  .5,   .495f, -.5, -.5,

															-.495f, -.5, -.5,  -.495f, -.5,  .5,
															-.495f,  .5,  .5,  -.495f,  .5, -.5, }, 8);
					meshRenderer->SetTexture("door frame", new float[16]{ 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1 }, false);
					frame->AddComponent(meshRenderer);

					gameScene->AddGameObject(frame);
				}
			}

			//player
			if (c == 'p')
			{
				player->transform.position = Vector3(x * cellSize, 1.5, z * cellSize);
				player->transform.rotation = Vector3(0, 90, 0);

				Camera * camera = new Camera(true);
				camera->backgroundColor = Color(BYTE(55));
				gameScene->activeCamera = camera;
				player->AddComponent(camera);

				MeshRenderer * meshRenderer = new MeshRenderer();
				meshRenderer->SetVertices(new float[12]{ -.2f, .5f, -.2f , .2f, .5f, -.2f , .2f,  .5f, .2f ,-.2f, .5f, .2f }, 4);
				meshRenderer->SetTexture("player", new float[8] {1,0, 0,0, 0,1, 1,1}, false);
				player->AddComponent(meshRenderer);

				Collider * collider = new Collider();
				collider->size = Vector3(1, 2, 1);

				player->AddComponent(collider);

				gameScene->AddGameObject(player);
			}
		}
	}
	//floor
	floor = new GameObject();
	floor->transform.position = Vector3(size / 2 * cellSize, 0, size / 2 * cellSize);
	floor->transform.scale = Vector3(size * cellSize, 1, size * cellSize);

	MeshRenderer * meshRenderer = new MeshRenderer();
	meshRenderer->SetVertices(new float[12]
		{
			-.5, 0,-.5,    .5, 0,-.5,
			 .5, 0, .5,   -.5, 0, .5
		}, 4);
	meshRenderer->SetTexture("floor", new float[8]{ 1,0, 0,0, 0,1, 1,1 }, false);
	floor->AddComponent(meshRenderer);

	gameScene->AddGameObject(floor);

	for (int i = 0; i < size; i++)
		delete[] levelCells[i];
	delete[] levelCells;
}
void Game::SetupGameUI()
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

//runs once when the game start
void Game::Start()
{
	LoadAssets();
	ResetGame();
}

//runs every frame
void Game::GameLoop()
{
	if (skipNextFrameAndResetGame)
	{
		skipNextFrameAndResetGame = false;
		loadLevel = true;
		return;
	}
	if (loadLevel)
	{
		loadLevel = false;

		gameScene = new Scene();
		SetupGameUI();
		SetupFreeCamera();
		SetupLevel(1);
		Engine::I()->activeScene = gameScene;

	}
	else if (Game::gameOver)
	{
		if (Input::KeyDown(Input::Keys::ENTER))
		{
			ResetGame();
		}
		if (Input::KeyDown(Input::Keys::ESCAPE))
		{
			Engine::I()->Close();
		}
	}
	else
	{
		if (Input::KeyDown(Input::Keys::N1))
		{
			player->GetComponent(Player().GetName())->enabled = true;
			gameScene->activeCamera = ((Camera *)player->GetComponent(Camera().GetName()));

			freeCamera->enabled = false;
		}

		if (Input::KeyDown(Input::Keys::N2))
		{
			player->GetComponent(Player().GetName())->enabled = false;

			freeCamera->enabled = true;
			gameScene->activeCamera = ((Camera *)freeCamera->GetComponent(Camera().GetName()));
		}

		if (Input::KeyDown(Input::Keys::N3))
			Collider::showWireframe = !Collider::showWireframe;

		if (Input::KeyDown(Input::Keys::N4))
			player->GetComponent(Collider().GetName())->enabled = !player->GetComponent(Collider().GetName())->enabled;

		if (Input::KeyDown(Input::Keys::N5))
			ResetGame();

		if (Input::KeyDown(Input::Keys::ESCAPE))
		{
			showCursor = !showCursor;
			if(showCursor)
				Input::ShowCursor();
			else
				Input::HideCursor();
		}
	}
}

void Game::WinGame()
{
	winScene = new Scene();
	GameObject * cameraGameObject = new GameObject();
	Camera * cameraComponent = new Camera();
	winScene->activeCamera = cameraComponent;
	cameraGameObject->AddComponent(cameraComponent);
	winScene->AddGameObject(cameraGameObject);

	UIImage * background = new UIImage();
	background->SetTexture("win background", new float[8]{ 0, 0, 0, 1, 1, 1, 1, 0, });
	background->size = Vector2(800, 600);
	background->position = Vector2(0, 0);
	winScene->AddUIElement(background);

	Engine::I()->activeScene = winScene;
	Game::gameOver = true;
}
void Game::LoseGame()
{
	deadScene = new Scene();
	GameObject * cameraGameObject = new GameObject();
	Camera * cameraComponent = new Camera();
	deadScene->activeCamera = cameraComponent;
	cameraGameObject->AddComponent(cameraComponent);
	deadScene->AddGameObject(cameraGameObject);

	UIImage * background = new UIImage();
	background->SetTexture("dead background", new float[8]{ 0, 0, 0, 1, 1, 1, 1, 0, });
	background->size = Vector2(800, 600);
	background->position = Vector2(0, 0);
	deadScene->AddUIElement(background);

	Engine::I()->activeScene = deadScene;
	Game::gameOver = true;
}