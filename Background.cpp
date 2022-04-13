#include "Background.h"
#include <math.h>


Background::~Background()
{
}

void Background::init(string s, glm::vec2 position, glm::vec2 dimension,int speed, ShaderProgram& shaderProgram){
	this->position.x = position.x * 32;
	this->position.y = position.y * 32;
	this->speed = speed;
	y = position.y;
	this->dimension = dimension;
	shader = shaderProgram;
	spritesheet.loadFromFile(s, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(dimension, glm::vec2(1, 1), &spritesheet, &shaderProgram);
	sprite->setPosition(position);
}


void Background::createParticles(string s, glm::vec2 position, ShaderProgram& shaderProgram) {
	this->position.x = position.x * 32;
	this->position.y = position.y * 32;
	y = position.y;
	shader = shaderProgram;
	spritesheet.loadFromFile(s, TEXTURE_PIXEL_FORMAT_RGBA);
	if (s == "images/muerte2.png") sprite = Sprite::createSprite(glm::vec2(160, 160), glm::vec2(1. / 4, 1), &spritesheet, &shaderProgram);
	else sprite = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(1. / 4, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(0, 4);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(0, glm::vec2(1. / 4, 0.f));
	sprite->addKeyframe(0, glm::vec2(2. / 4, 0.f));
	sprite->addKeyframe(0, glm::vec2(3. / 4, 0.f));
	sprite->setPosition(position);
	sprite->changeAnimation(0);
}

void Background::setTicks(int tick)
{
	this->ticks = ticks;
}

int Background::addTicks()
{
	ticks++;
	return ticks;
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

void Background::changeColor(string s) {
	spritesheet.loadFromFile(s, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(dimension, glm::vec2(1, 1), &spritesheet, &shader);
}

void Background::updateParticles(int deltaTime) {
	sprite->update(deltaTime);
}