#pragma once
#include "UINumber.h"
#include <Scene.h>
#include <GameObject.h>
#include "UIImage.h"
#include "Player.h"

class Game
{
public:
	bool showCursor;

	//intro
	Scene * introScene;
	Scene * gameScene;
	static Scene * winScene;
	static Scene * deadScene;

	//game
	bool skipNextFrameAndResetGame;
	bool loadLevel;
	static bool gameOver;
	GameObject * player;
	Player * playerCom;
	GameObject * freeCamera;
	GameObject * floor;

	UIImage * handImage;
	UIImage * hudWeapon;
	UINumber * hudGold;
	UINumber * hudHealth;

	Game();
	~Game();

	void ResetGame();
	void LoadAssets();
	void SetupFreeCamera();
	void SetupLevel(int levelNumber);
	void SetupGameUI();
	void Start();
	void GameLoop();
	void FreeMemory();
	static void WinGame();
	static void LoseGame();
};