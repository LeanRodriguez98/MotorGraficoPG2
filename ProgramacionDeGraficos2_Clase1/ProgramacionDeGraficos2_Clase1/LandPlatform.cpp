#include "LandPlatform.h"



LandPlatform::LandPlatform(Renderer * _renderer, b2World * _world, vec2 _position, vec2 _scale) :GroundChunk(_renderer, _world, _position, _scale)
{

}


LandPlatform::~LandPlatform()
{
}
