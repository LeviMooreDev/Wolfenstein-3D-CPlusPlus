#include "EndGame.h"
#include "Scene.h"
#include "Input.h"
#include "GameObject.h"
#include "Audio.h"
#include "Game.h"

EndGame::EndGame(GameObject * player)
{
	(*this).player = player;
}
EndGame::~EndGame()
{
}

void EndGame::Update(Scene * scene)
{
	if (Input::KeyDown(Input::Keys::E))
	{
		Vector3 d = gameObject->transform.position;
		d.y = 0;
		Vector3 p = player->transform.position;
		p.y = 0;

		if (d.Distance(p) < 3)
		{
			Audio::Play("win");
			Game::WinGame();
		}
	}
}
