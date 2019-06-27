#include "Renderer.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>



Renderer::Renderer()
{
}
Renderer::~Renderer()
{
}
bool Renderer::Start(Window * windowPTR) {


	if (windowPTR != NULL)
	{
		window = windowPTR;
		glfwMakeContextCurrent((GLFWwindow*)window->GetWindow());

		if (glewInit() != GLEW_OK) {
			cout << "Falló al inicializar GLEW\n" << endl;
			return -1;
		}

		glGenVertexArrays(1, &VertexArray);
		glBindVertexArray(VertexArray);

		projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.f);
		viewMatrix = glm::lookAt(
			glm::vec3(0, 0, 3),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0)
		);
		modelMatrix = glm::mat4(1.0f);

		UpdateModelViewProjectionMatrix();

		//cout << "Renderer::Start()" << endl;
		return true;
	}

	return false;

}
bool Renderer::Stop() {
	//cout << "Renderer::Stop()" << endl;
	return false;
}

void Renderer::ClearWindow()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Renderer::SwapBuffer()
{
	glfwSwapBuffers((GLFWwindow*)window->GetWindow());
}

unsigned int Renderer::GenerateBuffer(float* buffer, int size)
{
	unsigned int vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);

	return vertexbuffer;
}

unsigned int Renderer::GenerateColorBuffer(float* buffer, int size)
{
	unsigned int colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);

	return colorbuffer;
}

unsigned int Renderer::GenerateTextureBuffer(int width, int height, unsigned char* data)
{
	unsigned int  texturebuffer;
	glGenTextures(1, &texturebuffer);

	glBindTexture(GL_TEXTURE_2D, texturebuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);


	return texturebuffer;
}

void Renderer::DrawArrayBuffers(int size, int drawType)
{
	glDrawArrays(drawType, 0, size);
}

void Renderer::DestroyBuffer(unsigned int buffer)
{
	glDeleteBuffers(1, &buffer);
}

void Renderer::BindBuffer(unsigned int vtxbuffer, unsigned int atribId)
{
	glBindBuffer(GL_ARRAY_BUFFER, vtxbuffer);
	glVertexAttribPointer(
		atribId,														// Le paso la ubicacion de donde se guardo la mempria del vertice
		3,																// tamaño
		GL_FLOAT,														// tipo
		GL_FALSE,														// normalizado?
		0,																// Paso
		(void*)0														// desfase del buffer
	);

}
void Renderer::BindColorBuffer(unsigned int clrbuffer, unsigned int atribId)
{
	glBindBuffer(GL_ARRAY_BUFFER, clrbuffer);
	glVertexAttribPointer(
		atribId,														// Le paso la ubicacion de donde se guardo la mempria del vertice
		3,																// tamaño
		GL_FLOAT,														// tipo
		GL_FALSE,														// normalizado?
		0,																// Paso
		(void*)0														// desfase del buffer
	);

}

void Renderer::BindTextureBuffer(unsigned int txtrebuffer, unsigned int atribId)
{
	glBindBuffer(GL_ARRAY_BUFFER, txtrebuffer);
	glVertexAttribPointer(
		atribId,														// Le paso la ubicacion de donde se guardo la mempria del vertice
		2,																// tamaño
		GL_FLOAT,														// tipo
		GL_FALSE,														// normalizado?
		0,																// Paso
		(void*)0														// desfase del buffer
	);
}



void Renderer::EnableVertexAttribute(unsigned int atribId)
{
	glEnableVertexAttribArray(atribId);
}
void Renderer::DisableVertexAttribute(unsigned int atribId)
{
	glDisableVertexAttribArray(atribId);
}
void Renderer::LoadIdentityMatrix()
{
	modelMatrix = glm::mat4(1.0f);
}
void Renderer::UpdateModelViewProjectionMatrix()
{
	modelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
}
glm::mat4& Renderer::GetModelViewProjectionMatrix()
{
	return modelViewProjectionMatrix;
}
void Renderer::MultiplyWorldMatrix(glm::mat4 mat)
{
	modelMatrix *= mat;
	UpdateModelViewProjectionMatrix();
}
void Renderer::MultiplyModelMatrix(glm::mat4 mat)
{
	modelMatrix = mat;
	UpdateModelViewProjectionMatrix();
}

void Renderer::CameraFollow(vec3 _playerPosition)
{
	viewMatrix = glm::lookAt(_playerPosition - glm::vec3(0.0f, 0.0f, -1.0f), _playerPosition, glm::vec3(0.0f, 1.0f, 0.0f));
}