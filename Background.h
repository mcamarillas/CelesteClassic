#include "Texture.h"
#include "Sprite.h"
#include <glm/glm.hpp>
#include <stdlib.h>
#include <time.h>

#pragma once
class Background
{
public:
	~Background();
	void init(string s, glm::vec2 position, glm::vec2 dimension,int speed, ShaderProgram& shaderProgram);
	void updateX();
	void updateYSnow();
	void update(int deltaTime);
	void render();
	void setA(int A);
	void setW(float w);
	void changeColor(string s);
	void updateParticles(int deltaTime);
	void createParticles(string s, glm::vec2 position, ShaderProgram& shaderProgram);
	void setTicks(int tick);
	int addTicks();

private:
	int speed;
	int A;
	float w;
	int y;
	int ticks;
	glm::vec2 dimension;
	ShaderProgram shader;
	Texture spritesheet;
	Sprite* sprite;
	glm::vec2 position;
};

