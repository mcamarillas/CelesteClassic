#include "Object.h"
#include <math.h>


Object::Object(int id, int type, glm::vec2 position, string s, glm::vec2 d, ShaderProgram& shaderProgram) {
	this->id = id;
	this->position.x = position.x * 32;
	this->position.y = position.y * 32;
	this->type = type;
	spritesheet.loadFromFile(s, TEXTURE_PIXEL_FORMAT_RGBA);
	if(type == 2) sprite = Sprite::createSprite(glm::ivec2(32, 64), d, &spritesheet, &shaderProgram);
	else if (type == 4) sprite = Sprite::createSprite(glm::ivec2(64, 32), d, &spritesheet, &shaderProgram);
	else if (type == 5) sprite = Sprite::createSprite(glm::ivec2(224, 112), d, &spritesheet, &shaderProgram);
	else sprite = Sprite::createSprite(glm::ivec2(32, 32), d, &spritesheet, &shaderProgram);
	if (type == 1 || type == 3 || type == 2) { // KEYS BANDERA Y GLOBO NUBES
		sprite->setNumberAnimations(3);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
		sprite->setAnimationSpeed(1, 8);
		sprite->addKeyframe(1, glm::vec2(1./3, 0.f));
		sprite->setAnimationSpeed(2, 8);
		sprite->addKeyframe(2, glm::vec2(2./3, 0.f));
	}
	sprite->setPosition(position);
}

Object::~Object()
{
	int x;
}

glm::vec2 Object::getPosition() {
	return position;
}

void Object::setPosition(glm::vec2 position) {
	this->position = position;
}

void Object::update(int deltaTime) {
	if (type == 0) { // POINTS
		position.y = position.y + 0.6 * sin(angle);
		angle += 0.05;
	}
	else if (type == 1 || type == 3 || type == 2) {
		anim++;
		anim %= 24;
		if (anim <= 7) sprite->changeAnimation(0);
		else if(anim <= 15) sprite->changeAnimation(1);
		else sprite->changeAnimation(2);
	}
	else if (type == 4) {
		if (id % 2 == 0) {
			position.x += 2;
			if (position.x > 512) position.x = -64;
		}
		else {
			position.x -= 2;
			if (position.x < -64) position.x = 512;
		}
		
	}
	sprite->setPosition(position);
	sprite->update(deltaTime);
}

void Object::render() {
	sprite->render();
}

int Object::getID() {
	return id;
}


bool Object::hasCollisioned(glm::vec2 playerPos) {
	int rangX0 = position.x - 30;
	int rangX1 = position.x + 30;
	int rangY0 = position.y + 62;
	int rangY1 = position.y;
	if (type != 4) {
		if (playerPos.x > rangX0 && playerPos.x < rangX1 && playerPos.y < rangY0 && playerPos.y > rangY1) {
			if (type == 1) {
				goalEffects->play2D("sound/key.wav", false);
			}
			else if (type == 0) {
				goalEffects->play2D("sound/strawBerry.wav", false);
			}
			else if (type == 2) {
				goalEffects->play2D("sound/balloon.wav", false);
			}
			else if (type == 3) {
				return true;
			}
			return true;
		}
	}
	return false;
}

int Object::getType() {
	return type;
}




