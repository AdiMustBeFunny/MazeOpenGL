#include "GameLevel.h"

using std::vector; 
using std::stack;

GameLevel::GameLevel(int width, int height, int tileWidth, int tileHeight)
	:TileWidth(tileWidth),TileHeight(tileHeight)
{
	LevelWidthT = width / tileWidth;
	LevelHeightT = height / tileHeight;
	CellCount = ((LevelWidthT - 1) / 2) * ((LevelHeightT - 1) / 2); //valid cells for maze generation
	
}


GameLevel::~GameLevel()
{

	for (int i = 0; i < LevelHeightT; i++)
	{
		delete[] Maze[i];
	}
	delete[] Maze;

}


void GameLevel::Draw(SpriteRenderer& Renderer)
{
	for (int i = 0; i < LevelHeightT; i++)
	{
		for (int j = 0; j < LevelWidthT; j++)
		{
			if(Maze[i][j].GenInfo.Type != Empty)
			Maze[i][j].Draw(Renderer);

		}
	}
}


void GameLevel::Init()
{

	Maze = new GameLevelCell*[LevelHeightT];
	for (int i = 0; i < LevelWidthT; i++)
	{
		Maze[i] = new GameLevelCell[LevelWidthT];
	}

	for (int i = 0; i < LevelHeightT; i++)
	{
		for (int j = 0; j < LevelWidthT; j++)
		{
			Maze[i][j].Position = glm::vec2(j*TileWidth, i*TileHeight);
			Maze[i][j].Size = glm::vec2(TileWidth, TileHeight);
		}
	}


	CreateMaze();
}


void GameLevel::CreateMaze()
{
	
	int VisitedCellCount = 1;
	stack<GameLevelCell*> Cells;
	Maze[1][1].GenInfo.visited = true;
	Maze[1][1].GenInfo.Type = Empty;
	Cells.push(&Maze[1][1]);

	while (VisitedCellCount != CellCount)
	{

		GameLevelCell* CurrentCell = Cells.top();

		vector<GameLevelCell*> neighbours;

		if ((int)CurrentCell->Position.x / TileWidth > 1
			&& Maze[((int)CurrentCell->Position.y / TileHeight)][((int)CurrentCell->Position.x / TileWidth) - 2].GenInfo.visited == false)
			neighbours.push_back(&Maze[((int)CurrentCell->Position.y / TileHeight)][((int)CurrentCell->Position.x / TileWidth) - 2]);

		std::cout << ((int)CurrentCell->Position.x / TileWidth) <<' '<< ((int)CurrentCell->Position.y / TileHeight)<< std::endl;

		if ((int)CurrentCell->Position.x / TileWidth < LevelWidthT - 2
			&& Maze[((int)CurrentCell->Position.y / TileHeight)][((int)CurrentCell->Position.x / TileWidth) + 2].GenInfo.visited == false)
			neighbours.push_back(&Maze[((int)CurrentCell->Position.y / TileHeight)][((int)CurrentCell->Position.x / TileWidth) + 2]);

		if ((int)CurrentCell->Position.y / TileHeight > 1
			&& Maze[((int)CurrentCell->Position.y / TileHeight) - 2][((int)CurrentCell->Position.x / TileWidth)].GenInfo.visited == false)
			neighbours.push_back(&Maze[((int)CurrentCell->Position.y / TileHeight) - 2][((int)CurrentCell->Position.x / TileWidth)]);

		if ((int)CurrentCell->Position.y / TileHeight < LevelHeightT - 2
			&& Maze[((int)CurrentCell->Position.y / TileHeight) + 2][((int)CurrentCell->Position.x / TileWidth)].GenInfo.visited == false)
			neighbours.push_back(&Maze[((int)CurrentCell->Position.y / TileHeight) + 2][((int)CurrentCell->Position.x / TileWidth)]);

		if (!neighbours.empty())
		{
			VisitedCellCount += 1;
			
			int rndIndex = rand()%neighbours.size();

			neighbours[rndIndex]->GenInfo.visited = true;
			neighbours[rndIndex]->GenInfo.Type = Empty;

			Cells.push(neighbours[rndIndex]);

			//delete wall in between

			if (CurrentCell->Position.x > neighbours[rndIndex]->Position.x)
				Maze[((int)CurrentCell->Position.y / TileHeight)][((int)CurrentCell->Position.x / TileWidth) - 1].GenInfo.Type = Empty;

			else if (CurrentCell->Position.x < neighbours[rndIndex]->Position.x)
				Maze[((int)CurrentCell->Position.y / TileHeight)][((int)CurrentCell->Position.x / TileWidth) + 1].GenInfo.Type = Empty;

			else if (CurrentCell->Position.y > neighbours[rndIndex]->Position.y)
				Maze[((int)CurrentCell->Position.y / TileHeight) - 1][((int)CurrentCell->Position.x / TileWidth)].GenInfo.Type = Empty;

			else if (CurrentCell->Position.y < neighbours[rndIndex]->Position.y)
				Maze[((int)CurrentCell->Position.y / TileHeight) + 1][((int)CurrentCell->Position.x / TileWidth)].GenInfo.Type = Empty;
		}
		else
		{
			Cells.pop();
		}
	}//maze generated

	
	StartLocationX = 1;
	StartLocationY = 1;
	 
	EndLocationX = (LevelWidthT / 2)+rand() % (LevelWidthT / 2);
	EndLocationY = (LevelHeightT / 2)+rand() % (LevelHeightT / 2);

	while (Maze[EndLocationY][EndLocationX].GenInfo.Type != Empty)
	{
		EndLocationX = (LevelWidthT / 2) + rand() % (LevelWidthT / 2);
		EndLocationY = (LevelHeightT / 2) + rand() % (LevelHeightT / 2);
	}

	Maze[EndLocationY][EndLocationX].Color = glm::vec3(.7, 0, .2);
	Maze[EndLocationY][EndLocationX].GenInfo.Type = End;
}


void GameLevel::ClearMaze()
{

	for (int i = 0; i < LevelHeightT; i++)
	{
		for (int j = 0; j < LevelWidthT; j++)
		{
			Maze[i][j].GenInfo.visited = false;
			Maze[i][j].GenInfo.Type = Wall;
		}
	}

	Maze[EndLocationY][EndLocationX].Color = glm::vec3(1.0);
}

void GameLevel::RestartMaze()
{
	ClearMaze();
	CreateMaze();
}