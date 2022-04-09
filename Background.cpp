#include "Background.h"

Background::Background() {
	
}

void Background::init(glm::vec2 position, ShaderProgram& shaderProgram){
	this->position.x = position.x * 32;
	this->position.y = position.y * 32;
	spritesheet.loadFromFile("images/Blue.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(128, 32), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	sprite->setPosition(position);
}

void Background::update(int deltaTime) {
	sprite->setPosition(position);
	sprite->update(deltaTime);
}

void Background::render() {
	sprite->render();
}