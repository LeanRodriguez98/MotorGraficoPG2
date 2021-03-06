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
			cout << "Fall� al inicializar GLEW\n" << endl;
			return -1;
		}

		glGenVertexArrays(1, &VertexArray);
		glBindVertexArray(VertexArray);

		viewMatrix = lookAt(
			vec3(0, 0, 3),
			vec3(0, 0, 0),
			vec3(0, 1, 0)
		);
		modelMatrix = mat4(1.0f);

		UpdateModelViewProjectionMatrix();

		cout << "Renderer::Start()" << endl;
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		return true;
	}

	return false;

}
bool Renderer::Stop() {
	cout << "Renderer::Stop()" << endl;
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

unsigned int Renderer::GenerateIndexBuffer(unsigned int* buffer, int size)
{
	unsigned int indexbuffer;
	glGenBuffers(1, &indexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(unsigned int), &buffer[0], GL_STATIC_DRAW);

	return indexbuffer;
}

unsigned int Renderer::GenerateIndexBuffer(vector<unsigned int> index)
{
	unsigned int indexbuffer;
	glGenBuffers(1, &indexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(unsigned int), &index[0], GL_STATIC_DRAW);

	return indexbuffer;
}

unsigned int Renderer::GenerateMeshBuffer(unsigned int * indices, int size) {
	unsigned int elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	return elementbuffer;
}

void Renderer::BindMeshBuffer(unsigned int indexbuffer)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);

}

void Renderer::DrawArrayBuffers(int size, int drawType)
{
	glDrawArrays(drawType, 0, size);
}

void Renderer::DrawIndexBuffer(int indexcount)
{
	glDrawElements(
		GL_TRIANGLES,
		indexcount,
		GL_UNSIGNED_INT,
		(void*)0
	);
}


void Renderer::DrawIndexMesh(int size, unsigned int indexBuffer) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glDrawElements(
		GL_TRIANGLES,		
		size,				
		GL_UNSIGNED_INT,	
		(void*)0			
	);
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
		3,																// tama�o
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
		3,																// tama�o
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
		2,																// tama�o
		GL_FLOAT,														// tipo
		GL_FALSE,														// normalizado?
		0,																// Paso
		(void*)0														// desfase del buffer
	);
}




void Renderer::BindTexture(unsigned int texture, unsigned int textureID) 
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(textureID, 0);
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
	modelMatrix = mat4(1.0f);
}
void Renderer::UpdateModelViewProjectionMatrix()
{
	modelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
}

mat4& Renderer::GetModelViewProjectionMatrix()
{
	return modelViewProjectionMatrix;
}

mat4 Renderer::GetViewMatrix()
{
	return viewMatrix;
}

mat4 Renderer::GetModelMatrix()
{
	return modelMatrix;
}

mat4 Renderer::GetProjectionMatrix()
{
	return projectionMatrix;
}

void Renderer::MultiplyWorldMatrix(mat4 mat)
{
	modelMatrix *= mat;
	UpdateModelViewProjectionMatrix();
}
void Renderer::MultiplyModelMatrix(mat4 mat)
{
	modelMatrix = mat;
	UpdateModelViewProjectionMatrix();
}

void Renderer::CameraFollow(vec3 _playerPosition)
{
	viewMatrix = lookAt(_playerPosition - vec3(0.0f, 0.0f, -1.0f), _playerPosition, vec3(0.0f, 1.0f, 0.0f));
}

void Renderer::SetProjectionOrtho(float _left, float _right, float _bottom, float _top, float _zNear, float _zFar)
{
	projectionMatrix = ortho(_left, _right, _bottom, _top, _zNear, _zFar);
	UpdateModelViewProjectionMatrix();

}

void Renderer::SetProjectionPerspective(float _fovy, float _aspect, float _zNear, float _zFar)
{
	projectionMatrix = perspective(_fovy, _aspect, _zNear, _zFar);
	UpdateModelViewProjectionMatrix();
}

void Renderer::SetViewMatrix(vec3 _eye, vec3 _center, vec3 _up)
{
	viewMatrix = lookAt(_eye, _center, _up);
}

void Renderer::SetViewMatrix(mat4 _viewMatrix) 
{
	viewMatrix = _viewMatrix;
	UpdateModelViewProjectionMatrix();
}

void  Renderer::SetModelMatrix(mat4 _modelMatrix)
{
	modelMatrix = _modelMatrix;
}
void  Renderer::SetProjectionMatrix(mat4 _projectionMatrix) 
{
	projectionMatrix = _projectionMatrix;
}