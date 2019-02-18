#include "Tile.h"

Tile::Tile(Renderer* _renderer, int _tileId, float _width, float _height) : Shape(_renderer)
{
	tileId = _tileId;
	tileWidht = (1.0f / _width);
	tileHeight = (1.0f / _height);
	horizontalTiles = _width;
	verticalTiles = _height;

	vertexCount = 4;
	dispouse = false;
	vertex = new float[12]
	{
		-1.0f, 1.0f , 0.0f ,
		1.0f, 1.0f , 0.0f ,
		-1.0f, -1.0f , 0.0f ,
		1.0f, -1.0f , 0.0f
	};

	CalculateUVTile();

	SetVertexBuffer(vertex, 4);
	SetTileTexture(textureUVvertex, 4);
}

Tile::~Tile()
{
}

void Tile::SetTileTexture(float* vertex, int cant)
{

	if (dispouse)
	{
		renderer->DestroyBuffer(UVBufferId);
		dispouse = false;
	}
	UVBufferId = renderer->GenerateBuffer(vertex,sizeof(float)* cant * 2);
	dispouse = true;

}

void Tile::LoadTileTexture(const char* name)
{
	header = TextureImporter::LoadBMP(name);
	textureBufferId = renderer->GenerateTextureBuffer(header.width, header.height, header.data);


}

void Tile::Draw()
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
	renderer->DrawArrayBuffers(vertexCount, PRIMITIVE_TRIANGLE_STRIP);
	renderer->DisableVertexAttribute(0);
	renderer->DisableVertexAttribute(1);



}

void Tile::CalculateUVTile()
{
	textureUVvertex = new float[8];

	textureUVvertex[0] = 0.0f;
	textureUVvertex[1] = 1.0f;

	textureUVvertex[2] = tileWidht;
	textureUVvertex[3] = 1.0f;

	textureUVvertex[4] = 0.0f;
	textureUVvertex[5] = 1.0f - tileHeight;

	textureUVvertex[6] = tileWidht;
	textureUVvertex[7] = 1.0f - tileHeight;

	int row = 0;
	int column = tileId;

	while (column >= horizontalTiles)
	{
		column -= horizontalTiles;
		row++;
	}

	textureUVvertex[0] += tileWidht * column;
	textureUVvertex[1] -= tileHeight * row;

	textureUVvertex[2] += tileWidht * column;
	textureUVvertex[3] -= tileHeight * row;

	textureUVvertex[4] += tileWidht * column;
	textureUVvertex[5] -= tileHeight * row;

	textureUVvertex[6] += tileWidht * column;
	textureUVvertex[7] -= tileHeight * row;
}

int Tile::GetTileId()
{
	return tileId;
}