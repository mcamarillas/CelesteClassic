#ifndef _OBJECT_INCLUDE
#define _OBJECT_INCLUDE

#include "Texture.h"
#include "Sprite.h"
#include <glm/glm.hpp>
#include <irrKlang.h>
using namespace irrklang;

#pragma 
class Object
{
public:
	Object(int id, glm::vec2 position, string s, glm::vec2 d, ShaderProgram& shaderProgram);
	glm::vec2 getPosition();
	void setPosition(glm::vec2 position);
	void update(int deltaTime);
	void render();
	int getID();
	bool hasCollisioned(glm::vec2 playerPos);

private:
	int id;
	Texture spritesheet;
	Sprite* sprite;
	glm::vec2 position;
	ISoundEngine* goalEffects = createIrrKlangDevice();
};

#endif 