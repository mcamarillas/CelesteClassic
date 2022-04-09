#include "Texture.h"
#include "Sprite.h"
#include <glm/glm.hpp>
#include <stdlib.h>
#include <time.h>

#pragma once
class Background
{
public:
	Background();
	void init(string s, glm::vec2 position, glm::vec2 dimension,int speed, ShaderProgram& shaderProgram);
	void updateX();
	void updateYSnow();
	void update(int deltaTime);
	void render();

private:
	int speed;
	int A;
	int y;
	Texture spritesheet;
	Sprite* sprite;
	glm::vec2 position;
};

