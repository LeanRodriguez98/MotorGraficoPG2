#include "Window.h"
#include <GLFW/glfw3.h>

Window::Window(int _whith,int _height,  char * _windowName)
{
	height = _height;
	whith = _whith;
	windowName = _windowName;
	name = windowName.c_str();
}


Window::~Window()
{
}

bool Window::start()
{
	cout << "Started Window" << endl;

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return false;
	}

	window = glfwCreateWindow(whith,height,  name,NULL,NULL);

	if (window == NULL)
	{
		fprintf(stderr, "Failed to create GLFW window");
		glfwTerminate();
		return true;
	}

	return true;
}

bool Window::stop()
{
	std::cout << "Closed Window" << std::endl;

	if (window != NULL)
	{
		glfwDestroyWindow((GLFWwindow *)window);
	}

	return false;
}

bool Window::ShouldClose() 
{
	if (window != NULL)
	{
		return glfwWindowShouldClose((GLFWwindow *)window);
	}
	return true;
}

void Window::PollEvents() 
{
	glfwPollEvents();
}

void * Window::GetWindowPtr() 
{
	return window;
}