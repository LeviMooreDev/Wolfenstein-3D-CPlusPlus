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
#include "EndGameLever.h"

typedef std::basic_string<char> string;

//used to "safely" delete a pointer
template<typename T>
void safe_delete(T*& p)
{
	delete p;
	p = nullptr;
}

//declare static fields
bool Game::gameOver = false;
Scene * Game::winScene;
Scene * Game::deadScene;

Game::~Game()
{
	FreeMemory();
};

void Game::Start()
{
	//hide cursor
	Input::HideCursor();
	
	//load assets and reset the game
	LoadAssets();
	ResetGame();
}
void Game::GameLoop()
{
	//if we want to skip this frame and reset the game, set loadLevelNextUpdate to true and stop here
	if (skipNextFrameAndResetGame)
	{
		skipNextFrameAndResetGame = false;
		loadLevelNextUpdate = true;
		return;
	}

	//if we want to load the level this frame
	if (loadLevelNextUpdate)
	{
		loadLevelNextUpdate = false;

		//create new game scene and setup the free camera, ui and level
		gameScene = new Scene();
		SetupGameUI();
		SetupFreeCamera();
		SetupLevel(1);

		//set the active scene to the game scene
		Engine::I()->activeScene = gameScene;

	}
	//if the game is over
	else if (Game::gameOver)
	{
		//if the player presses enter reset the game
		if (Input::KeyDown(Input::Keys::ENTER))
			ResetGame();

		//if the player presses escape close the game
		if (Input::KeyDown(Input::Keys::ESCAPE))
			Engine::I()->Close();
	}
	//if this is a normal game loop
	else
	{
		//if the player presses 1 set game camera as active
		if (Input::KeyDown(Input::Keys::N1))
		{
			player->GetComponent(PlayerComponentName)->enabled = true;
			gameScene->activeCamera = ((Camera *)player->GetComponent(Camera().GetName()));

			freeCamera->enabled = false;
		}

		//if the player presses 2 set free camera as active
		if (Input::KeyDown(Input::Keys::N2))
		{
			player->GetComponent(PlayerComponentName)->enabled = false;

			freeCamera->enabled = true;
			gameScene->activeCamera = ((Camera *)freeCamera->GetComponent(Camera().GetName()));
		}

		//if the player presses 3 toggle collider wireframe
		if (Input::KeyDown(Input::Keys::N3))
			Collider::showWireframe = !Collider::showWireframe;

		//if the player presses 4 toggle player collider component
		if (Input::KeyDown(Input::Keys::N4))
			player->GetComponent(Collider().GetName())->enabled = !player->GetComponent(Collider().GetName())->enabled;

		//if the player presses 4 reset the game
		if (Input::KeyDown(Input::Keys::N5))
			ResetGame();

		//if the player presses escape toggle cursor visibility
		if (Input::KeyDown(Input::Keys::ESCAPE))
		{
			showCursor = !showCursor;

			if (showCursor)
				Input::ShowCursor();
			else
				Input::HideCursor();
		}
	}
}

void Game::FreeMemory()
{
	safe_delete(loadingScene);
	safe_delete(gameScene);
	safe_delete(winScene);
	safe_delete(deadScene);
}
void Game::ResetGame()
{
	FreeMemory();

	//create loading scene scene
	loadingScene = new Scene();
	
	//setup loading scene camera
	GameObject * cameraGameObject = new GameObject();
	Camera * cameraComponent = new Camera();
	loadingScene->activeCamera = cameraComponent;
	cameraGameObject->AddComponent(cameraComponent);
	loadingScene->AddGameObject(cameraGameObject);

	//setup loading scene background
	UIImage * background = new UIImage();
	background->SetTexture("loading", new float[8]{ 0, 0, 0, 1, 1, 1, 1, 0, });
	background->size = Vector2(800, 600);
	background->position = Vector2(0, 0);
	loadingScene->AddUIElement(background);

	//set loading scene as active
	Engine::I()->activeScene = loadingScene;

	//tell the game to skip next frame and reset the game for real this time
	skipNextFrameAndResetGame = true;

	gameOver = false;
}
void Game::LoadAssets()
{
#pragma region Textures
	//player
	Textures::AddTexture("player", "player");

	//floor
	Textures::AddTexture("floor", "floor");

	//door
	Textures::AddTexture("door", "door");
	Textures::AddTexture("door frame", "door_frame");

	//walls
	Textures::AddTexture("stone wall 1", "stone_wall_1");
	Textures::AddTexture("stone wall 2", "stone_wall_2");
	Textures::AddTexture("stone wall 3", "stone_wall_3");

	Textures::AddTexture("wood wall 1", "wood_wall_1");
	Textures::AddTexture("wood wall 2", "wood_wall_2");
	Textures::AddTexture("wood wall 3", "wood_wall_3");

	Textures::AddTexture("blue wall 1", "blue_wall_1");

	Textures::AddTexture("end game", "end_game");

	//backgrounds
	Textures::AddTexture("win background", "win_background");
	Textures::AddTexture("dead background", "dead_background");
	Textures::AddTexture("loading", "loading");

	//weapons
	Textures::AddTexture("pistol animation", "pistol");
	Textures::AddTexture("knife animation", "knife");

	//guard
	Textures::AddTexture("guard idle", "guard_idle");
	Textures::AddTexture("guard dead", "guard_dead");
	Textures::AddTexture("guard hit", "guard_hit");
	Textures::AddTexture("guard fire", "guard_fire");

	//objects
	Textures::AddTexture("object 1", "object_1");
	Textures::AddTexture("object 2", "object_2");
	Textures::AddTexture("object 3", "object_3");
	Textures::AddTexture("object 4", "object_4");
	Textures::AddTexture("object 5", "object_5");

	//gold
	Textures::AddTexture("gold 1", "gold_1");
	Textures::AddTexture("gold 2", "gold_2");
	Textures::AddTexture("gold 3", "gold_3");
	Textures::AddTexture("gold 4", "gold_4");

	//health pickup
	Textures::AddTexture("health", "health_pickup");

	//ui
	Textures::AddTexture("hud", "hud");
	Textures::AddTexture("hud knife", "hud knife");
	Textures::AddTexture("hud pistol", "hud pistol");
	Textures::AddTexture("hud numbers", "numbers");
#pragma endregion
#pragma region Audio
	//player
	Audio::Add("player hit 1", "player_hit_1");
	Audio::Add("player hit 2", "player_hit_1");
	Audio::Add("player dead", "player_dead");
	Audio::Add("win", "yeeeah");

	//weapons
	Audio::Add("pistol", "pistol");
	Audio::Add("knife", "knife");

	//enemy
	Audio::Add("enemy hit", "enemy_hit");
	Audio::Add("enemy death 1", "enemy_death_1");
	Audio::Add("enemy death 2", "enemy_death_2");

	//pickups
	Audio::Add("pickup", "pickup");
	Audio::Add("health", "health");

	//door
	Audio::Add("door", "door");

	//we load and play a silent audio clip to make the sound engine initialize fully before the game starts
	//the reason we want this is that the first time the engine plays a sound it tries a lot of different ways of playing to find the best one which in some cases can make the game stutter and we dont want that
	Audio::Add("silence", "silence");
	Audio::Play("silence");
#pragma endregion
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
	//2d array representing all the cells in the level
	char **levelCells = nullptr;

	//#1 load the level file as raw date into a string
	std::ifstream file("Levels/level" + std::to_string(levelNumber) + ".l");
	string rawData;
	std::getline(file, rawData);

	//#2 split raw date level by ,
	std::vector<std::string> cleanData;
	std::string tmp;
	std::istringstream splitStream(rawData);
	while (std::getline(splitStream, tmp, ','))
	{
		cleanData.push_back(tmp);
	}

	//#3 place level data into 2d array
	bool readSize = true;	//true if the next thing we are going to read is the size of the level
	int size = 0;			// size of the level
	int xPosition = 0;		// current x position
	int zPosition = 0;		// current z position

	for (auto const& data : cleanData)
	{
		//if the next we read is the size of the level
		if (readSize)
		{
			//set level size
			size = std::stoi(data);
			
			//setup levelCells 2d array
			levelCells = new char*[size];
			for (int i = 0; i < size; i++)
				levelCells[i] = new char[size];

			readSize = false;
		}
		else
		{
			//place data into 2d array at the current x and z position
			levelCells[xPosition][zPosition] = data[0];

			//increase x position
			xPosition++;

			//if we are at the end of the row, reset x position and increase z position by 1
			if (xPosition == size)
			{
				xPosition = 0;
				zPosition++;
			}
		}
	}

	//#4 turn 2d array into game objects
	float cellSize = 3;			//size of a cell
	float wallHeight = 3;		//height of a wall
	float enemyHeight = 2.75f;	//height of a enemy
	float objectHeight = 3;		//height of a object

	//the reason we create the player game object and component here is because some of the game objects in the scene needs to know about the player
	//and we can not guarantee in what order the level is loaded. by creating the player here it does not matter when the player position is loaded in

	//create player game object
	player = new GameObject();
	player->tag = "Player";

	//add player component to player game objet
	playerComponent = new Player(handImage, hudWeapon, hudGold, hudHealth);
	player->AddComponent(playerComponent);
	
	//loop through level 2d array
	for (int x = 0; x < size; x++)
	{
		for (int z = 0; z < size; z++)
		{
			//current cell
			char cell = levelCells[x][z];

			//if the cell is empty continue to next one
			if (cell == ' ')
				continue;

			//if the cell is a wall
			//s = stone
			//w = wood
			//b = blue
			//x = end lever. why x? I don't know!
			if (cell == 's' || cell == 'w' || cell == 'b' || cell == 'x')
			{
				//create wall game object
				GameObject * wall = new GameObject();

				//set wall position and scale
				wall->transform.position = Vector3(x * cellSize, wallHeight / 2.0f, z * cellSize);
				wall->transform.scale = Vector3(cellSize, wallHeight, cellSize);

				//create and add collider to wall
				Collider * collider = new Collider();
				collider->size = Vector3(cellSize, wallHeight, cellSize);
				wall->AddComponent(collider);

				//create wall mesh renderer
				MeshRenderer * meshRenderer = new MeshRenderer();

				//collection of vertices we are going to add to wall mesh renderer
				std::vector<float> * allVertices = new std::vector<float>();
				//the count of vertices
				int verticesCount = 0;
				//collection of uvs used by the wall mesh renderer 
				std::vector<float> * allUVs = new std::vector<float>();

				//we only want to show the sides of the wall the player can see
				//we can only add one set of vertices to the mesh renderer, when we add a new set the mesh renderer will remove the old one
				//because of the way the mesh renderer work we can not add a new side as soon as we have checked if it is visible
				//we have to add it to allVertices that we can then add to the mesh renderer at the end when we have checked for all sides

				//the way we check and add each side is almost the same except for changes to the x and z values.
				//#left
				//if the wall is to the very left of the level, or there is another wall to the left
				if (x != 0 && levelCells[x - 1][z] != 'w' && levelCells[x - 1][z] != 'b' && levelCells[x - 1][z] != 's')
				{
					//increase the vertice count by 4
					verticesCount += 4;

					//add wall vertices to allVertices
					float newVertices[12] =
					{
						-.5, .5, -.5,   -.5, .5,  .5,
						-.5, -.5, .5,   -.5,-.5, -.5
					};
					allVertices->insert(allVertices->begin(), std::begin(newVertices), std::end(newVertices));

					//add wall uvs to allUVs
					float uv[8] = { 0, 1, .5, 1, .5, 0, 0, 0, };
					allUVs->insert(allUVs->begin(), std::begin(uv), std::end(uv));
				}

				//#right
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

				//#forward
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

				//#back
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

				//if no side was visible free up some memory and continue to the next cell
				if (verticesCount == 0)
				{
					delete allVertices;
					delete allUVs;
					delete wall;
				}
				else
				{
					//set mesh renderer vertices
					meshRenderer->SetVertices(allVertices->data(), verticesCount);
					
					//if the wall is stone add a random stone wall texture
					if (cell == 's')
					{
						string textures[10] = { "stone wall 1", "stone wall 1", "stone wall 1", "stone wall 1", "stone wall 1", "stone wall 1", "stone wall 1", "stone wall 1", "stone wall 2", "stone wall 3" };
						meshRenderer->SetTextureRandom(textures, 10, allUVs->data(), false);
					}
					//if the wall is wood add a random wood wall texture
					else if (cell == 'w')
					{
						string textures[10] = { "wood wall 1", "wood wall 1", "wood wall 1", "wood wall 1", "wood wall 1", "wood wall 1", "wood wall 1", "wood wall 1", "wood wall 2", "wood wall 3" };
						meshRenderer->SetTextureRandom(textures, 10, allUVs->data(), false);
					}
					//if the wall is blue add a random blue wall texture
					else if (cell == 'b')
					{
						meshRenderer->SetTexture("blue wall 1", allUVs->data(), false);
					}
					//if the wall is the end game lever add end game lever texture
					else if (cell == 'x')
					{
						meshRenderer->SetTexture("end game", allUVs->data(), false);
						wall->AddComponent(new EndGameLever(player));
					}

					//add the mesh renderer to the wall game object
					wall->AddComponent(meshRenderer);

					//add the wall to the scene
					gameScene->AddGameObject(wall);
				}
			}

			//if the cell is a enemy
			//e = normal enemy
			//k = the first enemy you see. why k? I still don't know!
			if (cell == 'e' || cell == 'k')
			{
				//create enemy game object
				GameObject * enemy = new GameObject();

				//give the enemy a tag and mark its distance to the camera as important
				enemy->distanceToCameraIsImportant = true;
				enemy->tag = "Enemy";

				//set enemy position and roation
				enemy->transform.position = Vector3(x * cellSize, enemyHeight / 2.0f, z * cellSize);
				enemy->transform.scale = Vector3::One() * enemyHeight;

				//add a mesh renderer component
				//we don't set a texture here as the enemy component is responsible for that
				MeshRenderer * meshRenderer = new MeshRenderer();
				meshRenderer->SetVertices(new float[12]{ .5, -.5, 0,   -.5, -.5, 0, -.5, .5, 0,    .5, .5, 0 }, 4);
				enemy->AddComponent(meshRenderer);

				//add a collider component
				Collider * collider = new Collider();
				collider->size = Vector3(1, 2, 1);
				enemy->AddComponent(collider);

				//add a look at component and set its target to the player
				enemy->AddComponent(new LookAt(player));

				//add a enemy component 
				Enemy * enemyCom = new Enemy(player, meshRenderer);
				enemy->AddComponent(enemyCom);

				//if it is a normal enemy give it a random look direction
				if (cell == 'e')
				{
					float rx = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					float rz = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

					enemyCom->lookDirection = Vector3(rx, 0.0f, rz).Normalized();
				}
				//if it is the first enemy the player see make it ignore the player, look to the right and have 1 hp
				else
				{
					enemyCom->ignorePlayer = true;
					enemyCom->lookDirection = Vector3::Right();
					enemyCom->hp = 1;
				}

				//add the enemy to the scene
				gameScene->AddGameObject(enemy);
			}

			//if the cell is a object
			if (cell == 'o')
			{
				//create object game object
				GameObject * object = new GameObject();

				//mark the objects distance to the camera as important
				object->distanceToCameraIsImportant = true;

				//set position and scale
				object->transform.position = Vector3(x * cellSize, objectHeight / 2.0f, z * cellSize);
				object->transform.scale = Vector3::One() * objectHeight;

				//add a mesh renderer component
				MeshRenderer * meshRenderer = new MeshRenderer();
				meshRenderer->SetVertices(new float[12]{ .5, -.5, 0,   -.5, -.5, 0, -.5, .5, 0,    .5, .5, 0 }, 4);
				
				//give the object a random texture
				string textures[5] = { "object 1", "object 2", "object 3", "object 4", "object 5" };
				meshRenderer->SetTextureRandom(textures, 5, new float[8]{ 0,0,  1,0, 1,1,  0,1, }, true);
				object->AddComponent(meshRenderer);

				//add a collider component and make sure the collider is low enough so the player can shoot over it
				Collider * collider = new Collider();
				collider->center = Vector3(0, -.75f, 0);
				collider->size = Vector3(1, .5f, 1);
				object->AddComponent(collider);

				//add a look at component and set its target to the player
				object->AddComponent(new LookAt(player));

				//add the object to the scene
				gameScene->AddGameObject(object);
			}

			//if the cell is gold
			if (cell == 'g')
			{
				//create gold game object
				GameObject * gold = new GameObject();

				//mark the golds distance to the camera as important
				gold->distanceToCameraIsImportant = true;

				//set position and scale
				gold->transform.position = Vector3(x * cellSize, objectHeight / 2.0f, z * cellSize);
				gold->transform.scale = Vector3::One() * objectHeight;

				//add a mesh renderer component
				MeshRenderer * meshRenderer = new MeshRenderer();
				meshRenderer->SetVertices(new float[12]{ .5, -.5, 0,   -.5, -.5, 0, -.5, .5, 0,    .5, .5, 0 }, 4);

				//give the gold a random texture
				string textures[4] = { "gold 1", "gold 1", "gold 3", "gold 4" };
				meshRenderer->SetTextureRandom(textures, 4, new float[8]{ 0,0, 1,0, 1,1, 0,1, }, true);
				gold->AddComponent(meshRenderer);

				//add gold component
				Gold * goldCom = new Gold();
				gold->AddComponent(goldCom);

				//add a collider component and make it not solid so the player can go through it
				Collider * collider = new Collider();
				collider->solid = false;
				collider->size = Vector3(1, 2, 1);

				//call the gold components hit method when the collider triggers
				collider->ListenForTrigger(std::bind(&Gold::Hit, goldCom, std::placeholders::_1));
				gold->AddComponent(collider);

				//add a look at component and set its target to the player
				gold->AddComponent(new LookAt(player));

				//add the gold to the scene
				gameScene->AddGameObject(gold);
			}

			//if the cell is a health pickup
			if (cell == 'h')
			{
				//create health pickup game object
				GameObject * health = new GameObject();

				//mark the health pickups distance to the camera as important
				health->distanceToCameraIsImportant = true;

				//set position and scale
				health->transform.position = Vector3(x * cellSize, objectHeight / 2.0f, z * cellSize);
				health->transform.scale = Vector3::One() * objectHeight;

				//add a mesh renderer component
				MeshRenderer * meshRenderer = new MeshRenderer();
				meshRenderer->SetVertices(new float[12]{ .5, -.5, 0,   -.5, -.5, 0, -.5, .5, 0,    .5, .5, 0 }, 4);
				meshRenderer->SetTexture("health", new float[8]{ 0,0, 1,0, 1,1, 0,1, }, true);
				health->AddComponent(meshRenderer);

				//add health component
				Health * healthCom = new Health();
				health->AddComponent(healthCom);

				//add a collider component and make it not solid so the player can go through it
				Collider * collider = new Collider();
				collider->solid = false;
				collider->size = Vector3(1, 2, 1);

				//call the health components hit method when the collider triggers
				collider->ListenForTrigger(std::bind(&Health::Hit, healthCom, std::placeholders::_1));
				health->AddComponent(collider);

				//add a look at component and set its target to the player
				health->AddComponent(new LookAt(player));

				//add the health pickup to the scene
				gameScene->AddGameObject(health);
			}

			//if the cell is a door
			if (cell == 'd')
			{
				//if there is a wall in front or behind the door set rotateDoor to true so we rotate it 90 degrees
				bool rotateDoor = ((z != size - 1 && levelCells[x][z + 1] == 's') || (z != 0 && levelCells[x][z - 1] == 's')) ||
								((z != size - 1 && levelCells[x][z + 1] == 'w') || (z != 0 && levelCells[x][z - 1] == 'w')) ||
								((z != size - 1 && levelCells[x][z + 1] == 'b') || (z != 0 && levelCells[x][z - 1] == 'b'));
				
				//the only reason we use a scope here is that i am too lazy to add a door and frame prefix to the local variables
				
				//door game object
				{
					//create door game object
					GameObject * door = new GameObject();

					//set position and scale
					door->transform.position = Vector3(x * cellSize, wallHeight / 2.0f, z * cellSize);
					door->transform.scale = Vector3(cellSize, wallHeight, cellSize);

					//rotate door if needed
					if (rotateDoor)
						door->transform.rotation = Vector3(0, 90, 0);

					//create a mesh renderer component
					MeshRenderer * meshRenderer = new MeshRenderer();
					meshRenderer->SetVertices(new float[12]{ .5, -.5, 0,   -.5, -.5, 0, -.5, .5, 0,    .5, .5, 0, }, 4);

					//flip uvs if the door is rotated
					if (rotateDoor)
						meshRenderer->SetTexture("door", new float[8]{ 0,0, 1,0, 1,1, 0,1, }, false);
					else
						meshRenderer->SetTexture("door", new float[8]{ 1,0, 0,0, 0,1, 1,1, }, false);

					//make the mesh renderer render both sides of the door
					meshRenderer->doubleSided = true;

					//add the mesh renderer component
					door->AddComponent(meshRenderer);

					//add a collider component
					Collider * collider = new Collider();
					collider->size = Vector3(cellSize, wallHeight, 0.6f);
					if (rotateDoor)
						collider->size = Vector3(0.6f, wallHeight, cellSize);
					door->AddComponent(collider);

					//add door component
					door->AddComponent(new Door(player, collider));

					//add door to scene
					gameScene->AddGameObject(door);
				}

				//door frame game object
				{
					//create door frame game object
					GameObject * frame = new GameObject();

					//set position and scale
					frame->transform.position = Vector3(x * cellSize, wallHeight / 2.0f, z * cellSize);
					frame->transform.scale = Vector3(cellSize, wallHeight, cellSize);

					//rotate frame if needed
					if (rotateDoor)
						frame->transform.rotation = Vector3(0, 90, 0);

					//add mesh renderer component
					MeshRenderer * meshRenderer = new MeshRenderer();
					meshRenderer->SetVertices(new float[24]{ .495f,  .5, -.5,   .495f,  .5,  .5,
															 .495f, -.5,  .5,   .495f, -.5, -.5,

															-.495f, -.5, -.5,  -.495f, -.5,  .5,
															-.495f,  .5,  .5,  -.495f,  .5, -.5, }, 8);
					meshRenderer->SetTexture("door frame", new float[16]{ 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1 }, false);
					frame->AddComponent(meshRenderer);

					//add frame to scene
					gameScene->AddGameObject(frame);
				}
			}

			//if the cell is a where the player starts
			if (cell == 'p')
			{
				//set player position and rotation
				player->transform.position = Vector3(x * cellSize, 1.5, z * cellSize);
				player->transform.rotation = Vector3(0, 90, 0);

				//added player camera
				Camera * camera = new Camera(true);
				camera->backgroundColor = Color(BYTE(55));
				gameScene->activeCamera = camera;
				player->AddComponent(camera);

				//add mesh renderer. is only visible by the free camera as a P when looked at from above
				MeshRenderer * meshRenderer = new MeshRenderer();
				meshRenderer->SetVertices(new float[12]{ -.2f, .5f, -.2f , .2f, .5f, -.2f , .2f,  .5f, .2f ,-.2f, .5f, .2f }, 4);
				meshRenderer->SetTexture("player", new float[8] {1,0, 0,0, 0,1, 1,1}, false);
				player->AddComponent(meshRenderer);

				//add a collider component
				Collider * collider = new Collider();
				collider->size = Vector3(1, 2, 1);
				player->AddComponent(collider);

				//add player to the scene
				gameScene->AddGameObject(player);
			}
		}
	}

	//create floor game object
	GameObject * floor = new GameObject();
	
	//set floor position and scale
	floor->transform.position = Vector3(size / 2 * cellSize, 0, size / 2 * cellSize);
	floor->transform.scale = Vector3(size * cellSize, 1, size * cellSize);

	//add mesh renderer component
	MeshRenderer * meshRenderer = new MeshRenderer();
	meshRenderer->SetVertices(new float[12]
								{
									-.5, 0,-.5,    .5, 0,-.5,
										.5, 0, .5,   -.5, 0, .5
								}, 4);
	meshRenderer->SetTexture("floor", new float[8]{ 1,0, 0,0, 0,1, 1,1 }, false);
	floor->AddComponent(meshRenderer);

	//add floor to scene
	gameScene->AddGameObject(floor);

	//free up memory used by 2d array
	for (int i = 0; i < size; i++)
		delete[] levelCells[i];
	delete[] levelCells;
}
void Game::SetupGameUI()
{
	//hud background
	UIImage * hud = new UIImage();
	hud->size = Vector2(800, 90);
	hud->position = Vector2(Engine::I()->GetWindowSize().x / 2 - hud->size.x / 2, 0);
	hud->SetTexture("hud", new float[8]{ 0, 0, 0, 1, 1, 1, 1, 0, });
	gameScene->AddUIElement(hud);

	//player hands
	handImage = new UIImage();
	handImage->size = Vector2(400, 400);
	handImage->position = Vector2(Engine::I()->GetWindowSize().x / 2 - handImage->size.x / 2, hud->size.y);
	gameScene->AddUIElement(handImage);

	//selected weapon
	hudWeapon = new UIImage();
	hudWeapon->size = Vector2(160, 80);
	hudWeapon->position = Vector2(Engine::I()->GetWindowSize().x - hudWeapon->size.x, 5);
	gameScene->AddUIElement(hudWeapon);

	//player health
	hudHealth = new UINumber("hud numbers");
	hudHealth->number = 100;
	hudHealth->size = Vector2(20, 40);
	hudHealth->position = Vector2(455, 10);
	hudHealth->order = 0.1f;
	gameScene->AddUIElement(hudHealth);

	//player gold
	hudGold = new UINumber("hud numbers");
	hudGold->number = 0;
	hudGold->size = Vector2(20, 40);
	hudGold->position = Vector2(190, 10);
	hudGold->order = 0.1f;
	gameScene->AddUIElement(hudGold);
}

void Game::WinGame()
{
	//create win scene
	winScene = new Scene();
	
	//setup scene camera
	GameObject * cameraGameObject = new GameObject();
	Camera * cameraComponent = new Camera();
	winScene->activeCamera = cameraComponent;
	cameraGameObject->AddComponent(cameraComponent);
	winScene->AddGameObject(cameraGameObject);

	//setup scene background
	UIImage * background = new UIImage();
	background->SetTexture("win background", new float[8]{ 0, 0, 0, 1, 1, 1, 1, 0, });
	background->size = Vector2(800, 600);
	background->position = Vector2(0, 0);
	winScene->AddUIElement(background);

	//set win scene to active
	Engine::I()->activeScene = winScene;

	Game::gameOver = true;
}
void Game::LoseGame()
{
	//create dead scene
	deadScene = new Scene();

	//setup scene camera
	GameObject * cameraGameObject = new GameObject();
	Camera * cameraComponent = new Camera();
	deadScene->activeCamera = cameraComponent;
	cameraGameObject->AddComponent(cameraComponent);
	deadScene->AddGameObject(cameraGameObject);

	//setup scene background
	UIImage * background = new UIImage();
	background->SetTexture("dead background", new float[8]{ 0, 0, 0, 1, 1, 1, 1, 0, });
	background->size = Vector2(800, 600);
	background->position = Vector2(0, 0);
	deadScene->AddUIElement(background);

	//set dead scene to active
	Engine::I()->activeScene = deadScene;

	Game::gameOver = true;
}