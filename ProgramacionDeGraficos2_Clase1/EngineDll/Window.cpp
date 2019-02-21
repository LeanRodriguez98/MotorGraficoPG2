#include "Window.h"
#include <GLFW\glfw3.h>


Window::Window()
{
}

Window::~Window()
{
}
bool Window::Start(int w, int h, const char* n) {
	//Inicializar GLFW

	/*Initialize the library*/
	if (!glfwInit())
		return -1;

	/*Create a window and create its OpenGL context*/
	window = glfwCreateWindow(w, h, n, NULL, NULL);

	if (window == NULL) {
		cout << "Failed to open GLFW window" << endl;
		glfwTerminate();
		return false;
	}

	return true;
}
bool Window::Stop() {
	if (window != NULL)
		glfwDestroyWindow((GLFWwindow*)window);

	window = NULL;

	glfwTerminate();

	return true;
}
bool Window::ShouldClose() {
	if (window)
		return glfwWindowShouldClose((GLFWwindow*)window);

	return true;
}
void Window::PollEvents() {
	glfwPollEvents();
}
void* Window::GetWindow() {
	return window;
}
