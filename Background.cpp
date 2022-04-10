#include "Background.h"
#include <math.h>


void Background::init(string s, glm::vec2 position, glm::vec2 dimension,int speed, ShaderProgram& shaderProgram){
	this->position.x = position.x * 32;
	this->position.y = position.y * 32;
	this->speed = speed;
	y = position.y;
	spritesheet.loadFromFile(s, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(dimension, glm::vec2(1, 1), &spritesheet, &shaderProgram);
	sprite->setPosition(position);
}

void Background::updateX() {
	this->position.x += speed;
}

void Background::updateYSnow() {
	position.y = A * sin(w * position.x) + y * 32;
}

void Background::update(int deltaTime) {
	if(position.x > 512) position.x = (rand() % 600) - 800;
	sprite->setPosition(position);
	sprite->update(deltaTime);
}

void Background::render() {
	sprite->render();
}

void Background::setA(int A) {
	this->A = A;
}

void Background::setW(float w) {
	this->w = w;
}
