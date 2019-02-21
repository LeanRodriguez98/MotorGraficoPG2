#include "Sprite.h"

Sprite::Sprite(Renderer* renderer, int _cantFrames) : Shape(renderer)
{

	textureUVvertex = NULL;
	UVBufferId = -1;
	textureBufferId = -1;
	animation = new Animation(_cantFrames);
	dispouse = false;
	vertex = new float[12]
	{
		-1.0f,-1.0f , 0.0f ,
		1.0f,-1.0f , 0.0f ,
		-1.0f, 1.0f , 0.0f ,
		1.0f, 1.0f , 0.0f
	};

	SetVertexBuffer(vertex, 4);

	textureUVvertex = animation->UpdateFrame();
	
	SetTextureVertices(textureUVvertex, 4);

}


Sprite::~Sprite()
{
}

void Sprite::SetTextureVertices(float* _vertex, int _cant)
{
	if (dispouse)
	{
		renderer->DestroyBuffer(UVBufferId);
		dispouse = false;
	}

	UVBufferId = renderer->GenerateBuffer(_vertex, sizeof(float)* _cant * 2);
	dispouse = true;
}

void Sprite::LoadTexture(const char* _name)
{
	header = TextureImporter::LoadBMP(_name);
	textureBufferId = renderer->GenerateTextureBuffer(header.width, header.height, header.data);
}




void Sprite::DrawMesh(int drawType)
{
	renderer->LoadIdentityMatrix();
	renderer->MultiplyModelMatrix(model);

	if (material != NULL) {
		material->Bind();
		material->SetMatrixProperty("WVP", renderer->GetModelViewProjectionMatrix());
		material->BindTexture("myTextureSampler", textureBufferId);
	}

	renderer->EnableVertexAttribute(0);
	renderer->EnableVertexAttribute(1);
	renderer->BindBuffer(vertexBufferID, 0);
	renderer->BindTextureBuffer(UVBufferId, 1);
	renderer->DrawArrayBuffers(vertexCount, drawType);
	renderer->DisableVertexAttribute(0);
	renderer->DisableVertexAttribute(1);
}

void Sprite::Draw()
{
	DrawMesh(PRIMITIVE_TRIANGLE_STRIP);
}

void Sprite::Update() 
{
	textureUVvertex = animation->UpdateFrame();

	SetTextureVertices(textureUVvertex, 4);

}

