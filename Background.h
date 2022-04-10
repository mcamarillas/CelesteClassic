#include "Texture.h"
#include "Sprite.h"
#include <glm/glm.hpp>
#include <stdlib.h>
#include <time.h>

#pragma once
class Background
{
public:
	void init(string s, glm::vec2 position, glm::vec2 dimension,int speed, ShaderProgram& shaderProgram);
	void updateX();
	void updateYSnow();
	void update(int deltaTime);
	void render();
	void setA(int A);
	void setW(float w);
	void changeColor(string s);

private:
	int speed;
	int A;
	float w;
	int y;
	glm::vec2 dimension;
	ShaderProgram shader;
	Texture spritesheet;
	Sprite* sprite;
	glm::vec2 position;
};

