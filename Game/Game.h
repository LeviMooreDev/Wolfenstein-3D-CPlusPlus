#pragma once
#include "UINumber.h"
#include <Scene.h>
#include <GameObject.h>
#include "UIImage.h"
#include "Player.h"

//this is you know like where the whole game thing is going on
class Game
{
public:
	//true if the cursor is shown
	bool showCursor;

	//scene for while loading
	Scene * loadingScene;
	//main game scene
	Scene * gameScene;
	//scene for when winning
	static Scene * winScene;
	//scene for when dead
	static Scene * deadScene;

	//true if we want to reset the game next frame
	//we use this so the loading scene has a chance to render a frame
	//if we dont use this all we would see when resetting is white and we all know that nobody likes white in 2019
	bool skipNextFrameAndResetGame;
	
	//true if we want to load level next game loop
	bool loadLevelNextUpdate;
	//true if the game is over. is used for both winning and losing
	static bool gameOver;
	//the player object
	GameObject * player;
	//the player component on the player game object
	Player * playerComponent;
	//the free camera game object
	GameObject * freeCamera;

	//the ui image showing player hands
	UIImage * handImage;
	//the ui image showing what weapon the player have equipped
	UIImage * hudWeapon;
	//the ui number showing how much gold the player have
	UINumber * hudGold;
	//the ui number showing how much health the player have
	UINumber * hudHealth;

	~Game();

	//called when the game first starts
	void Start();

	//called every game loop
	void GameLoop();

	//reset the game
	void ResetGame();
	//load game assets. only call this once
	void LoadAssets();
	//free up memory used by the game
	void FreeMemory();

	//setup the free camera
	void SetupFreeCamera();
	//load and setup level
	//levelNumber: postfix of the level file we want to use
	void SetupLevel(int levelNumber);
	//setup ui
	void SetupGameUI();
	
	//call when we win the game
	static void WinGame();
	
	//call when we lose the game
	static void LoseGame();
};