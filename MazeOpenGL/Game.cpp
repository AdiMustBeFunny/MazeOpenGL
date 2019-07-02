#include "Game.h"

#include<glfw3.h>

Game::Game(int width,int height):Width(width),Height(height),Level(width,height,32,32)
{
	for (auto &iter : Keys)
	{
		iter = false;
	}
}


Game::~Game()
{
	delete Player;
}

void Game::Init()
{
	Renderer.InitRenderData();

	ResourceManager::LoadShader("spriteDefault.vs", "spriteDefault.fs", "spriteDefault");
	ResourceManager::LoadShader("surfaceDefault.vs", "surfaceDefault.fs", "surfaceDefault");

	ResourceManager::LoadTexture("MazeBlock.png", "wall");

	ResourceManager::CreateSurface(Width, Height, "surfaceDefault");


	glm::mat4 proj = glm::ortho(.0f, (float)Width, (float)Height, 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("spriteDefault").Use().setMat4fv("projection", proj);
	
	Level.Init();
	Player = new GameObject(ResourceManager::GetTexture("wall"), glm::vec2(32, 32), glm::vec2(32, 32), glm::vec3(0.2, 0.5, 0.2));
	Player->Velocity = 200.0f;
}

void Game::Render()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);


	//ResourceManager::GetSurface("surfaceDefault").Bind();
	//Renderer.DrawSprite(ResourceManager::GetTexture("wall"), glm::vec2(100, 100), glm::vec2(32, 32));
	//ResourceManager::GetSurface("surfaceDefault").UnBind();
	//Renderer.DrawSurface(ResourceManager::GetSurface("surfaceDefault"));
	
	Level.Draw(Renderer);

	Player->Draw(Renderer);
}

float acc = 0;
void Game::ProcessKeyboard(int key, int action, float dt)
{

	if (action == GLFW_PRESS)
	{
		Keys[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		Keys[key] = false;
	}
	
}


void Game::Update(float dt)
{
	//pass condition
	if (abs(Level.EndLocationX*Level.TileWidth - (Player->Position.x)) < 10 && abs(Level.EndLocationY*Level.TileHeight - (Player->Position.y)) < 10)
	{
		Player->Position = glm::vec2(32, 32);
		Level.RestartMaze();
	}
	processPlayer(dt);
	
}






void Game::processPlayer(float dt)
{

	float HorizontalSpeed = 0;
	float VerticalSpeed = 0;

	if (Keys[GLFW_KEY_D])
	{
		HorizontalSpeed += dt * Player->Velocity;
	}

	if (Keys[GLFW_KEY_A])
	{
		HorizontalSpeed -= dt * Player->Velocity;
	}
	if (Keys[GLFW_KEY_W])
	{
		VerticalSpeed -= dt * Player->Velocity;
	}

	if (Keys[GLFW_KEY_S])
	{
		VerticalSpeed += dt * Player->Velocity;
	}

	float currentX = Player->Position.x;

	//Right Collision
	if (HorizontalSpeed > 0.0f
		&& (Level.Maze[(int)Player->Position.y / Level.TileHeight][((int)(Player->Position.x + Player->Size.x + HorizontalSpeed - 1) / Level.TileWidth)].GenInfo.Type == Wall
			|| Level.Maze[((int)(Player->Position.y + Player->Size.y - 1)) / Level.TileHeight][((int)(Player->Position.x + Player->Size.x + HorizontalSpeed - 1) / Level.TileWidth)].GenInfo.Type == Wall))
	{
		//std::cout << Player->Position.x << ' ' << Player->Position.y << std::endl;

		if ((int)Player->Position.x % Level.TileWidth != 0)
		{
			Player->Position.x = (int)(Player->Position.x - (int)Player->Position.x % Level.TileWidth) + Level.TileWidth; //(Player->Position.x + Player->Size.x) - ((int)(Player->Position.x + Player->Size.x) % Level.TileWidth) + Level.TileWidth;

		}
		//hack so as to avoid getting stuck on every edge
		if (Level.Maze[((int)(Player->Position.y + Player->Size.y / 2)) / Level.TileHeight][((int)(Player->Position.x + Player->Size.x + HorizontalSpeed - 1) / Level.TileWidth)].GenInfo.Type != Wall)
		{
			if ((int)(Player->Position.y + Player->Size.y - 1) % Level.TileHeight < Level.TileHeight / 4)
			{
				Player->Position.y = ((int)(Player->Position.y) / Level.TileHeight) * Level.TileHeight;
			}

			else if ((int)(Player->Position.y) % Level.TileHeight > 3 * Level.TileHeight / 4)
			{
				Player->Position.y = ((int)(Player->Position.y) / Level.TileHeight + 1) * Level.TileHeight;
			}

		}

		HorizontalSpeed = 0;
	}

	//Left Collision
	if (HorizontalSpeed < 0.0f
		&& (Level.Maze[(int)Player->Position.y / Level.TileHeight][((int)(Player->Position.x + HorizontalSpeed) / Level.TileWidth)].GenInfo.Type == Wall
			|| Level.Maze[((int)(Player->Position.y + Player->Size.y - 1)) / Level.TileHeight][((int)(Player->Position.x + HorizontalSpeed) / Level.TileWidth)].GenInfo.Type == Wall))
	{

		if ((int)Player->Position.x % Level.TileWidth != 0)
			Player->Position.x = (((int)(Player->Position.x + Player->Size.x / 2)) / Level.TileWidth) * Level.TileWidth;//(int)(Player->Position.x- (int)Player->Position.x % Level.TileWidth) + Level.TileWidth - .2;

		if (Level.Maze[((int)(Player->Position.y + Player->Size.y / 2)) / Level.TileHeight][((int)(Player->Position.x + HorizontalSpeed) / Level.TileWidth)].GenInfo.Type != Wall)
		{
			if ((int)(Player->Position.y) % Level.TileHeight < Level.TileHeight / 4)
			{
				Player->Position.y = ((int)(Player->Position.y) / Level.TileHeight) * Level.TileHeight;
			}

			else if ((int)(Player->Position.y) % Level.TileHeight > 3 * Level.TileHeight / 4)
			{

				Player->Position.y = ((int)(Player->Position.y) / Level.TileHeight + 1) * Level.TileHeight;
			}
		}
		HorizontalSpeed = 0;
	}

	//Top Collision

	if (VerticalSpeed < 0.0f
		&& (Level.Maze[((int)(Player->Position.y + VerticalSpeed)) / Level.TileHeight][((int)(Player->Position.x) / Level.TileWidth)].GenInfo.Type == Wall
			|| Level.Maze[((int)(Player->Position.y + VerticalSpeed)) / Level.TileHeight][((int)(Player->Position.x + Player->Size.x - 1) / Level.TileWidth)].GenInfo.Type == Wall))
	{
		if ((int)Player->Position.y % Level.TileHeight != 0)
			Player->Position.y = (((int)(Player->Position.y + Player->Size.y / 2)) / Level.TileHeight) * Level.TileHeight;

		if (Level.Maze[((int)(Player->Position.y + VerticalSpeed)) / Level.TileHeight][((int)(Player->Position.x + Player->Size.x / 2) / Level.TileWidth)].GenInfo.Type != Wall)
		{
			if ((int)(Player->Position.x) % Level.TileWidth > 3 * Level.TileWidth / 4)
			{
				Player->Position.x = ((int)(Player->Position.x) / Level.TileWidth + 1) * Level.TileWidth;
			}
			if ((int)(Player->Position.x) % Level.TileWidth < Level.TileWidth / 4)
			{
				Player->Position.x = ((int)(Player->Position.x) / Level.TileWidth) * Level.TileWidth;
			}

		}
		VerticalSpeed = 0;
	}

	//Bottom Collision

	if (VerticalSpeed > 0.0f
		&& (Level.Maze[((int)(Player->Position.y + Player->Size.y + VerticalSpeed)) / Level.TileHeight][((int)(Player->Position.x) / Level.TileWidth)].GenInfo.Type == Wall
			|| Level.Maze[((int)(Player->Position.y + Player->Size.y + VerticalSpeed)) / Level.TileHeight][((int)(Player->Position.x + Player->Size.x - 1) / Level.TileWidth)].GenInfo.Type == Wall))
	{
		if ((int)Player->Position.y % Level.TileHeight != 0)
			Player->Position.y = (int)(Player->Position.y - (int)Player->Position.y % Level.TileHeight) + Level.TileHeight;

		if (Level.Maze[((int)(Player->Position.y + Player->Size.y + VerticalSpeed - 1)) / Level.TileHeight][((int)(Player->Position.x + Player->Size.x / 2) / Level.TileWidth)].GenInfo.Type != Wall)
		{
			if ((int)(Player->Position.x) % Level.TileWidth > 3 * Level.TileWidth / 4)
			{
				Player->Position.x = ((int)(Player->Position.x) / Level.TileWidth + 1) * Level.TileWidth;
			}
			if ((int)(Player->Position.x) % Level.TileWidth < Level.TileWidth / 4)
			{
				Player->Position.x = ((int)(Player->Position.x) / Level.TileWidth) * Level.TileWidth;
			}
		}

		VerticalSpeed = 0;
	}



	if (abs(currentX - Player->Position.x) > Player->Size.x / 2)Player->Position.x -= Player->Size.x;




	Player->Position.x += HorizontalSpeed;
	Player->Position.y += VerticalSpeed;

}