#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <Windows.h>
#include "MMSystem.h"
#include "Game.h"
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define DASH_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define SPEEDX 4
#define DASH_SPEED 6


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT, WALL_LEFT
};


void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	specialMove = 0;
	isDashing = false;
	underGround = false;
	//checkCollisions();
	spritesheet.loadFromFile("images/Madeline.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
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
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Player::moveLeft()
{
	posPlayer -= SPEEDX;
	if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
	{
		posPlayer += SPEEDX;
		sprite->changeAnimation(JUMP_LEFT);
		specialMove = 0;
	}
	if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32),&posPlayer.y))
	{
		specialMove = 0;
		sprite->changeAnimation(STAND_LEFT);
	}
}
void Player::moveRight()
{
	posPlayer += SPEEDX;
	if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
	{
		posPlayer -= SPEEDX;
		sprite->changeAnimation(JUMP_RIGHT);
		specialMove = 0;
	}
	if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
	{
		specialMove = 0;
		sprite->changeAnimation(STAND_RIGHT);
	}
}

void Player::checkCollisions() {
	glm::ivec2 aux = posPlayer;
	aux.x -= SPEEDX;
	if (map->collisionMoveLeft(aux, glm::ivec2(32, 32))) leftCol = true;
	else leftCol = false;
	aux.x += SPEEDX;

	aux.x += SPEEDX;
	if (map->collisionMoveRight(aux, glm::ivec2(32, 32))) rightCol = true;
	else rightCol = false;
	aux.x -= SPEEDX;

	int py = int(startY - 96 * sin(3.14159 * jumpAngle / 180.f));

	aux.y += FALL_STEP;
	
	if (map->collisionMoveDown(aux, glm::ivec2(32, 32), &aux.y)) downCol = true;
	else downCol = false;

	if (map->collisionMoveUp(posPlayer, glm::ivec2(32, 32), &py)) upCol = true;
	else upCol = false;
}

void Player::rightJump() {
		//PlaySound(TEXT("Suu"), NULL, SND_FILENAME | SND_ASYNC);
		specialMove = 1;
		if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT)
			sprite->changeAnimation(JUMP_LEFT);
		else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT)
			sprite->changeAnimation(JUMP_RIGHT);
		bJumping = true;
		jumpAngle = 0;
		startY = posPlayer.y;
}

void Player::leftJump() {
	//PlaySound(TEXT("Suu"), NULL, SND_FILENAME | SND_ASYNC);
	specialMove = 2;
	if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT)
		sprite->changeAnimation(JUMP_LEFT);
	else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT)
		sprite->changeAnimation(JUMP_RIGHT);
	bJumping = true;
	jumpAngle = 0;
	startY = posPlayer.y;
}

void Player::updateJump()
{
	//UPDATE JUMP DISTANCE
	jumpAngle += JUMP_ANGLE_STEP;
	//IF JUMP ENDED REINITIALIZE VARIABLES (CREATE FUNCTION)
	if (jumpAngle == 180)
	{
		bJumping = false;
		posPlayer.y = startY;
	}
	else if (jumpAngle >= 90) {
		specialMove = 0;		
	}
	//ACTIVATE SPECIAL LEFT JUMP
	posPlayer.x += SPEEDX;
	bool rCol = map->collisionMoveRight(posPlayer, glm::ivec2(32, 32));
	posPlayer.x -= SPEEDX;
	posPlayer.x -= SPEEDX;
	bool lCol = map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32));
	posPlayer.x += SPEEDX;
	if (Game::instance().getSpecialKey(GLUT_KEY_UP) && rCol && jumpAngle > 32) rightJump();
	//ACTIVATE SPECIAL RIGHT JUMP	
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP) && lCol && jumpAngle > 32) leftJump();
	
	
}

bool Player::getUnderground() {
	return underGround;
}

void Player::respawn() {
	underGround = false;
}

void Player::dash()
{
	dashAngle += DASH_ANGLE_STEP;
	if (dashX == 1) {
		posPlayer.x -= DASH_SPEED;
		bool lCol = map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32));
		if (lCol) {
			posPlayer.x += DASH_SPEED;
			specialMove = 0;
		}
	}
	else if (dashX == 2) {
		posPlayer.x += DASH_SPEED;
		bool rCol = map->collisionMoveRight(posPlayer, glm::ivec2(32, 32));
		if (rCol) {
			posPlayer.x -= DASH_SPEED;
			specialMove = 0;
		}
	}
	else {
		
	}

	if (dashY == 1) {
		posPlayer.y -= DASH_SPEED;
		if (map->collisionMoveUp(posPlayer, glm::ivec2(32, 32), &posPlayer.y)) {
			specialMove = 0;
		}
	}
	else if (dashY == 2) {
		posPlayer.y += DASH_SPEED;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y)) {
			specialMove = 0;
		}
	}
	else {

	}
	if (dashAngle >= 60) {
		specialMove = 0;
	}
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (posPlayer.y >= 512) underGround = true;
	else {
		checkCollisions();
		//LEFT MOVEMENT
		if (Game::instance().getKey('x') && !isDashing)
		{
			if (Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				dashY = 1;
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
			{
				dashY = 2;
			}
			else dashY = 0;
			if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
			{
				dashX = 1;
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
			{
				dashX = 2;
			}
			else if (dashY == 0) {
				if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT) dashX = 1;
				else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT) dashX = 2;
			}
			else dashX = 0;
			specialMove = 3;
			isDashing = true;
			bJumping = false;
			dashAngle = 0;
		}
		int py = int(startY - 96 * sin(3.14159 * jumpAngle / 180.f));
		if (specialMove != 0)
		{
			switch (specialMove) {
			case 1:
				moveLeft();
				break;
			case 2:
				moveRight();
				break;
			case 3:
				dash();
				break;
			}
		}
		else
		{


			//LEFT MOVEMENT
			if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
			{
				if (sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
				posPlayer.x -= SPEEDX;
				if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
				{
					posPlayer.x += SPEEDX;
					sprite->changeAnimation(STAND_LEFT);
				}
			}
			//RIGHT MOVEMENT
			else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
			{
				if (sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
				posPlayer.x += SPEEDX;
				if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
				{
					posPlayer.x -= SPEEDX;
					sprite->changeAnimation(STAND_RIGHT);
				}

			}
			//TRATAR ANIMACION PARADO
			else
			{
				if (sprite->animation() == MOVE_LEFT) sprite->changeAnimation(STAND_LEFT);
				else if (sprite->animation() == MOVE_RIGHT)	sprite->changeAnimation(STAND_RIGHT);
			}

		}
		//TRATAR EL SALTO ACTIVO
		if (map->collisionMoveUp(posPlayer, glm::ivec2(32, 32), &py) && bJumping) {
			bJumping = false;
			specialMove = 0;
		}
		else if (bJumping)posPlayer.y = py;
		// CUANDO ESTAS CAYENDO		
		if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y)) {
			bJumping = false;
			specialMove = 0;
		}
		if (bJumping) updateJump();
		//TRATAR POSIBLE ACTIVACION DE SALTO
		else if (specialMove != 3)
		{
			// CUANDO ESTAS CAYENDO
			posPlayer.y += FALL_STEP;
			if (!map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y)) {

				if (Game::instance().getSpecialKey(GLUT_KEY_UP) && rightCol && !upCol) rightJump();
				else if (Game::instance().getSpecialKey(GLUT_KEY_UP) && leftCol && !upCol) leftJump();
			}
			// CUANDO ESTAS EN EL SUELO
			else {
				isDashing = false;
				posPlayer.x -= SPEEDX;
				if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
				{
					posPlayer.x += SPEEDX;
					sprite->changeAnimation(STAND_LEFT);
				}
				posPlayer.x += SPEEDX;
				if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
				{
					posPlayer.x -= SPEEDX;
					sprite->changeAnimation(STAND_RIGHT);
				}
				if (Game::instance().getSpecialKey(GLUT_KEY_UP))
				{
					//PlaySound(TEXT("Suu"), NULL, SND_FILENAME | SND_ASYNC);
					if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT)
						sprite->changeAnimation(JUMP_LEFT);
					else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT)
						sprite->changeAnimation(JUMP_RIGHT);
					bJumping = true;
					specialMove = 0;
					jumpAngle = 0;
					startY = posPlayer.y;
				}
			}
		}
	}	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}




