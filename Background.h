#include "Texture.h"
#include "Sprite.h"
#include <glm/glm.hpp>

#pragma once
class Background
{
public:
	Background();
	void init(glm::vec2 position, ShaderProgram& shaderProgram);
	glm::vec2 getPosition();
	void setPosition(glm::vec2 position);
	void update(int deltaTime);
	void render();

private:
	Texture spritesheet;
	Sprite* sprite;
	glm::vec2 position;
};

