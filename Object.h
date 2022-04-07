#ifndef _OBJECT_INCLUDE
#define _OBJECT_INCLUDE

#include "Texture.h"
#include "Sprite.h"
#include <glm/glm.hpp>

#pragma 
class Object
{
public:
	Object(int x, int y, Texture t, ShaderProgram& shaderProgram);
	glm::ivec2 getPosition();
	void setPosition(int x, int y);
	void update(int deltaTime);
	void render();
	void setObject(int x, int y, Texture t, ShaderProgram& shaderProgram); 

private:
	Sprite* sprite;
	glm::vec2 position;
};

#endif 