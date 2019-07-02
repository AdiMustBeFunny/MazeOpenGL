#include<iostream>
#include<time.h>

#include<glad\glad.h>
#include<glfw3.h>


#define STB_IMAGE_IMPLEMENTATION


#include"Game.h"
using namespace std;


const int SCREEN_WIDTH = 672;
const int SCREEN_HEIGHT = 672;

Game MazeGame(SCREEN_WIDTH, SCREEN_HEIGHT);

float lastFrame = 0,deltaTime = 0;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
{

	srand(time(NULL));

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Maze",nullptr,nullptr);

	if (!window)
	{
		cout << "Failed to create window" << endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "GLAD was not glad during initialization :(" << endl;
		glfwTerminate();
		exit(-2);
	}


	glfwSetKeyCallback(window, key_callback);


	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	
	MazeGame.Init();

	while (glfwWindowShouldClose(window) == false)
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		



		MazeGame.Update(deltaTime);
		
		MazeGame.Render();


		glfwSwapBuffers(window);
	}

	ResourceManager::Clear();

	glfwTerminate();

	system("pause");
	return 0;
}



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	MazeGame.ProcessKeyboard(key, action,deltaTime);

}