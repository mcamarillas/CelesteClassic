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
	Object(int id,int type, glm::vec2 position, string s, glm::vec2 d, ShaderProgram& shaderProgram);
	~Object();
	glm::vec2 getPosition();
	void setPosition(glm::vec2 position);
	void update(int deltaTime);
	void render();
	int getID();
	bool hasCollisioned(glm::vec2 playerPos);
	int getType();

private:
	int type; // 0 -> POINTABLE , 1 -> KEYS, 2 -> BALLON, 3 -> BANDERA, 4 -> NUBE
	int id;
	float angle = 0;
	int anim = 0;
	bool open = false;
	bool dash = false;
	Texture spritesheet;
	Sprite* sprite;
	glm::vec2 position;
	ISoundEngine* goalEffects = createIrrKlangDevice();
};

#endif 