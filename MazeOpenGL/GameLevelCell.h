#pragma once
#ifndef GAME_LEVEL_CELL_H
#define GAME_LEVEL_CELL_H

#include "GameObject.h"
#include "ResourceManager.h"



enum CellType
{
	Wall,
	Empty,
	End
};

struct LevelGenInfo
{
	bool visited = false;
	CellType Type = Wall;
};


class GameLevelCell :public GameObject
{
public:
	GameLevelCell( 
		glm::vec2 pos = glm::vec2(0,0),
		glm::vec2 size = glm::vec2(32,32),
		glm::vec3 color= glm::vec3(1.0),
		Texture2D = ResourceManager::GetTexture("wall"),
		Shader = ResourceManager::GetShader("spriteDefault"));
	~GameLevelCell();

	LevelGenInfo GenInfo;
};

#endif // !GAME_LEVEL_CELL