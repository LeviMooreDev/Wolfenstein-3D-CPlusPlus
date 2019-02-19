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
	GameObject * introCameraGameObject;
	Camera * introCameraComponent;
	UIImage * introBackground;

	//game
	bool skipNextFrameAndResetGame;
	bool loadLevel;
	static bool gameOver;
	Scene * gameScene;
	GameObject * player;
	Player * playerCom;
	GameObject * freeCamera;

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
	static void WinGame();
	static void LoseGame();
};