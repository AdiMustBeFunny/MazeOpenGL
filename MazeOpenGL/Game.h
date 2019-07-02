#pragma once
#ifndef GAME_H
#define GAME_H



#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GameLevel.h"
class Game
{
public:
	Game(int width, int height);
	~Game();

	void Init();
	void Update(float dt);
	void ProcessKeyboard(int key, int action,float dt);
	void Render();

private:
	int Width, Height;
	SpriteRenderer Renderer;
	GameLevel Level;
	GameObject *Player;

	bool Keys[1024];

	void processPlayer(float dt);
};


#endif // GAME_H