#include "ImputManager.h"
#include "Window.h"
#include <GLFW\glfw3.h>


ImputManager* ImputManager::instance = 0;

ImputManager* ImputManager::GetInstance()
{
	if (instance == 0)
	{
		instance = new ImputManager();
	}
	return instance;
}


void ImputManager::SetWindow(Window* _window) 
{
	window = _window;
}

bool ImputManager::GetKeyDown(Key _key) 
{
	return (glfwGetKey((GLFWwindow*)window->GetWindow(), _key) == GLFW_PRESS);
}



ImputManager::ImputManager()
{
}


ImputManager::~ImputManager()
{
}
