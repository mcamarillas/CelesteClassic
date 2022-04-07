#include "Object.h"

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT, WALL_LEFT
};

Object::Object(int x, int y, Texture t, ShaderProgram& shaderProgram) {
	position.x = x;
	position.y = y;
	Texture j;
	j.loadFromFile("images/Madeline.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &t, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25, 0.5f));

	sprite->setAnimationSpeed(JUMP_RIGHT, 8);
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.5f, 0.25f));

	sprite->setAnimationSpeed(JUMP_LEFT, 8);
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.75f, 0.25f));

	sprite->setAnimationSpeed(WALL_LEFT, 8);
	sprite->addKeyframe(WALL_LEFT, glm::vec2(0.5f, 0.75));
	sprite->changeAnimation(0);
	
}

glm::ivec2 Object::getPosition() {
	return position;
}

void Object::setPosition(int x, int y) {
	position.x = x;
	position.y = y;
}

void Object::update(int deltaTime) {
	sprite->update(deltaTime);
	sprite->setPosition(position);
}

void Object::render() {
	sprite->render();
}

void Object::setObject(int x, int y, Texture t, ShaderProgram& shaderProgram) {
	position.x = x;
	position.y = y;
	Texture j;
	j.loadFromFile("images/Madeline.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &t, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25, 0.5f));

	sprite->setAnimationSpeed(JUMP_RIGHT, 8);
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.5f, 0.25f));

	sprite->setAnimationSpeed(JUMP_LEFT, 8);
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.75f, 0.25f));

	sprite->setAnimationSpeed(WALL_LEFT, 8);
	sprite->addKeyframe(WALL_LEFT, glm::vec2(0.5f, 0.75));
	sprite->changeAnimation(0);

}