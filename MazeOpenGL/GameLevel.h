#pragma once

#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include<vector>
#include<stack>

#include"GameLevelCell.h"
#include"SpriteRenderer.h"

class GameLevel
{
public:
	GameLevel(int width,int height,int tileWidth, int tileHeight);
	~GameLevel();

	void Draw(SpriteRenderer& Renderer);
	void Init();
	void RestartMaze();

	int TileWidth;
	int TileHeight;
	GameLevelCell **Maze;
	int StartLocationX;
	int StartLocationY;
	int EndLocationY;
	int EndLocationX;
private:

	int LevelWidthT;
	int LevelHeightT;
	int CellCount;
	

	void ClearMaze();
	void CreateMaze();
};




#endif // !GAME_LEVEL_H