#include "Renderer.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

bool Renderer::Start(Window * window)
{
	_window = window;
	glfwMakeContextCurrent((GLFWwindow *)window->GetWindowPtr());
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Falló al inicializar GLEW\n");
		return -1;
	}

	glGenVertexArrays(1, (GLuint *)&VertexArray);
	glBindVertexArray((GLuint)VertexArray);

	projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);

	viewMatrix = lookAt(
		vec3(0, 0, 3),
		vec3(0, 0, 0),
		vec3(0, 1, 0)
	);

	modelMatrix = mat4(1.0f);

	UpdateModelViewProjectionMatrix();

	cout << "Started renderer" << endl;
	return true;
}

bool Renderer::Stop()
{
	cout << "Finished renderer" << endl;
	return true;
}

void Renderer::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Renderer::SwapBuffer()
{
	glfwSwapBuffers((GLFWwindow *)_window->GetWindowPtr());
}

void Renderer::ClearWindow()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

unsigned int Renderer::GenerateVertexBuffer(float * buffer, int size)
{
	unsigned int vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
	return vertexbuffer;
}

unsigned int Renderer::GenerateColorBuffer(float * buffer, int size)
{
	unsigned int colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
	return colorbuffer;
}

void Renderer::EnableVertexAttribute(unsigned int attribute) 
{
	glEnableVertexAttribArray(attribute);
}

void Renderer::BindBuffer(unsigned int buffer, unsigned int attribute)
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexAttribPointer(
		attribute,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
}
void Renderer::DrawArrayBuffers(int drawSystem,int size) 
{
	glDrawArrays((GLenum)drawSystem, 0, size);
}

void Renderer::DisableVertexAttribute(unsigned int attribute) 
{
	glDisableVertexAttribArray(attribute);
}

void Renderer::UpdateModelViewProjectionMatrix()
{
	modelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
}

mat4& Renderer::GetModelViewProjectionMatrix()
{
	return modelViewProjectionMatrix;
}

void Renderer::SetModel(mat4 model)
{
	modelMatrix = model;
	UpdateModelViewProjectionMatrix();
}

void Renderer::MultiplyModel(mat4 model)
{
	modelMatrix *= model;
	UpdateModelViewProjectionMatrix();
}

void Renderer::LoadIdentityMatrix()
{
	modelMatrix = mat4(1.0f);
}