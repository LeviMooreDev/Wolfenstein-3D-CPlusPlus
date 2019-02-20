#include "EndGameLever.h"
#include "Scene.h"
#include "Input.h"
#include "GameObject.h"
#include "Audio.h"
#include "Game.h"

EndGameLever::EndGameLever(GameObject * player)
{
	(*this).player = player;
}

void EndGameLever::Update(Scene * scene)
{
	//when the player presses E, check if the player is close enough to use the lever
	//if yes, call Game::WindGame()
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
