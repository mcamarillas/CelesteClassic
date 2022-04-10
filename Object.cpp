#include "Object.h"



Object::Object(int id, int type, glm::vec2 position, string s, glm::vec2 d, ShaderProgram& shaderProgram) {
	this->id = id;
	this->position.x = position.x * 32;
	this->position.y = position.y * 32;
	spritesheet.loadFromFile(s, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), d, &spritesheet, &shaderProgram);
	sprite->setPosition(position);
}

glm::vec2 Object::getPosition() {
	return position;
}

void Object::setPosition(glm::vec2 position) {
	this->position = position;
}

void Object::update(int deltaTime) {
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
	int playerTileX = playerPos.x / 32;
	int playerTileY = playerPos.y / 32;
	int playerTileX3 = (playerPos.x + 30) / 32;
	
	int objTileX = position.x / 32;
	int objTileY = position.y / 32;
	if ((playerTileX == objTileX && playerTileY == objTileY) || (playerTileX3 == objTileX && playerTileY == objTileY)) {
		goalEffects->play2D("sound/strawBerry.wav", false);
		return true;

	}

	return false;
}


