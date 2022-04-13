#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define DASH_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define SPEEDX 4
#define DASH_SPEED 6

#define OFFSETX 0
#define OFFSETY 0

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT, WALL_LEFT, STAND_UP, STAND_UP2, STAND_DOWN, STAND_DOWN2, DESLIZANDO, DESLIZANDO2
};


void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	specialMove = 0;
	isDashing = false;
	underGround = false;
	nextLvl = false;
	isMolla = false;
	god = false;
	infiniteDash = false;
	//checkCollisions();
	spritesheet.loadFromFile("images/Madeline.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(13);

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
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.5f, 0.0f));

	sprite->setAnimationSpeed(JUMP_LEFT, 8);
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.75f, 0.0f));

	sprite->setAnimationSpeed(STAND_UP, 8);
	sprite->addKeyframe(STAND_UP, glm::vec2(0.5f, 0.5f));

	sprite->setAnimationSpeed(STAND_UP2, 8);
	sprite->addKeyframe(STAND_UP2, glm::vec2(0.75f, 0.5f));

	sprite->setAnimationSpeed(STAND_DOWN, 8);
	sprite->addKeyframe(STAND_DOWN, glm::vec2(0.5f, 0.25f));

	sprite->setAnimationSpeed(STAND_DOWN2, 8);
	sprite->addKeyframe(STAND_DOWN2, glm::vec2(0.75f, 0.25f));

	sprite->setAnimationSpeed(DESLIZANDO, 8);
	sprite->addKeyframe(DESLIZANDO, glm::vec2(0.5f, 0.75f));

	sprite->setAnimationSpeed(DESLIZANDO2, 8);
	sprite->addKeyframe(DESLIZANDO2, glm::vec2(0.75f, 0.75f));

	sprite->setAnimationSpeed(WALL_LEFT, 8);
	sprite->addKeyframe(WALL_LEFT, glm::vec2(0.5f, 0.75));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Player::initStrawberries() {
	for (int i = 0; i < 10; i++) strawberries[i] = false;
}

void Player::setLvl(int lvl) {
	this->lvl = lvl;
}

int Player::getPolvillo()
{
	return polvillo;
}

void Player::updateSB() {
	strawberries[lvl-1] = true;
}
void Player::moveLeft()
{
	posPlayer.x -= SPEEDX;
	if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
	{
		posPlayer.x += SPEEDX;
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
		{
			//posPlayer.y -= FALL_STEP / 2;
			sprite->changeAnimation(DESLIZANDO);
		}
		specialMove = 0;
	}
	else sprite->changeAnimation(JUMP_LEFT);
	if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
	{
		specialMove = 0;
		if(!downCol)sprite->changeAnimation(STAND_LEFT);
	}
}
void Player::moveRight()
{
	posPlayer.x += SPEEDX;
	if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
	{
		posPlayer.x -= SPEEDX;
		if (!downCol && Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
			posPlayer.y -= FALL_STEP / 2;
			//sprite->changeAnimation(DESLIZANDO2);
		}
		specialMove = 0;
	}
	else sprite->changeAnimation(JUMP_RIGHT);
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

	int py = int(startY - JUMP_HEIGHT * sin(3.14159 * jumpAngle / 180.f));

	aux.y += FALL_STEP;

	if (map->collisionMoveDown(aux, glm::ivec2(32, 32), &aux.y)) downCol = true;
	else downCol = false;

	if (map->collisionMoveUp(posPlayer, glm::ivec2(32, 32), &py)) upCol = true;
	else upCol = false;
}

void Player::rightJump() {

	movementEffectsR->play2D("sound/jump.wav", false);
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
	movementEffectsL->play2D("sound/jump.wav", false);
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
	if (sprite->animation() == DESLIZANDO && !leftCol) sprite->changeAnimation(JUMP_LEFT);
	else if (sprite->animation() == DESLIZANDO2 && !rightCol)	sprite->changeAnimation(JUMP_RIGHT);
	//IF JUMP ENDED REINITIALIZE VARIABLES (CREATE FUNCTION)
	if (jumpAngle >= 180)
	{
		bJumping = false;
		isMolla = false;
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
	if (Game::instance().getKey('c') && !cPressed && rCol && jumpAngle > 32) {
		polvillo = 1;
		cPressed = true;
		rightJump();
	}
	//ACTIVATE SPECIAL RIGHT JUMP	
	else if (Game::instance().getKey('c') && !cPressed && lCol && jumpAngle > 32) {
		polvillo = 1;
		cPressed = true;
		leftJump();
	}
	else polvillo = 0;
}

bool Player::getUnderground() {
	return underGround;
}

bool Player::getNextLvl() {
	return nextLvl;
}

void Player::respawn() {
	underGround = false;
	specialMove = 0;
	bJumping = 0;
	jumpAngle = 0;
	map->respawn();
}

void Player::stopDashMove() {
	ticks -= 1;
}
int Player::getTicks() {
	return ticks;
}

void Player::isInCloud(bool b)
{
	isCloud = b;
}

void Player::resetLvl() {
	nextLvl = false;
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
			posPlayer.y += 5 * DASH_SPEED;
		}
	}
	else if (dashY == 2) {
		posPlayer.y += DASH_SPEED;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y)) {
			polvillo = 0;
			specialMove = 0;
		}
	}
	else {

	}
	if (dashAngle >= 60) {
		specialMove = 0;
	}
}

void Player::Yanimations() {
	if (Game::instance().getSpecialKey(GLUT_KEY_UP) && downCol) {
		if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT) sprite->changeAnimation(STAND_UP);
		else if (sprite->animation() != STAND_UP)sprite->changeAnimation(STAND_UP2);
	}
	else {
		if (sprite->animation() == STAND_UP) sprite->changeAnimation(STAND_RIGHT);
		else if (sprite->animation() == STAND_UP2) sprite->changeAnimation(STAND_LEFT);
	}
	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && downCol) {
		if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT) sprite->changeAnimation(STAND_DOWN);
		else if (sprite->animation() != STAND_DOWN)sprite->changeAnimation(STAND_DOWN2);
	}
	else {
		if (sprite->animation() == STAND_DOWN) sprite->changeAnimation(STAND_RIGHT);
		else if (sprite->animation() == STAND_DOWN2) sprite->changeAnimation(STAND_LEFT);
	}
}


void Player::update(int deltaTime)
{

	sprite->update(deltaTime);
	
	//if (sprite->animation() == DESLIZANDO || sprite->animation() == DESLIZANDO2) posPlayer.y -= FALL_STEP / 2;
	Yanimations();
	if (Game::instance().getKey('g')) {
		if (god) god = false;
		else god = true;
	}
	if (posPlayer.y <= 1) {
		nextLvl = true;
		posPlayer.y = 700;
		bJumping = false;
		specialMove = 0;
		goalEffects->play2D("sound/nextlvl.wav", false);
	}
	else if (posPlayer.y >= 512 || posPlayer.x > (32 * 16 + 25)) {
		collisionEffects->play2D("sound/respawn.wav", false);
		strawberries[lvl] = false;
		underGround = true;
	}
	else if (map->getSpikes() && !god) {
		collisionEffects->play2D("sound/spikes.wav", false);
		strawberries[lvl] = false;
		underGround = true;
	}
	else {

		checkCollisions();
		//LEFT MOVEMENT
		if (Game::instance().getKey('x') && (!isDashing || infiniteDash))
		{
			ticks = 6;
			movementEffects->play2D("sound/dash.wav", false);
			if (Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				polvillo = 5;
				dashY = 1;
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
			{
				polvillo = 6;
				dashY = 2;
			}
			else dashY = 0;
			if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
			{
				polvillo = 4;
				dashX = 1;
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
			{
				polvillo = 3;
				dashX = 2;
			}
			else if (dashY == 0) {

				if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT || sprite->animation() == JUMP_LEFT) {
					polvillo = 4;
					dashX = 1;
				}
				else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT || sprite->animation() == JUMP_RIGHT) {
					polvillo = 3;
					dashX = 2;
				}
			}
			else {
				dashX = 0;
			}
			specialMove = 3;
			isDashing = true;
			bJumping = false;
			dashAngle = 0;
		}
		int py = int(startY - JUMP_HEIGHT * sin(3.14159 * jumpAngle / 180.f));
		if (specialMove != 0)
		{
			switch (specialMove) {
			case 1:
				isMolla = false;
				moveLeft();
				break;
			case 2:
				isMolla = false;
				moveRight();
				break;
			case 3:
				isMolla = false;
				dash();
				break;
			}
		}
		else
		{
			polvillo = 0;
			//LEFT MOVEMENT
			if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
			{
				if (sprite->animation() != MOVE_LEFT && !bJumping) sprite->changeAnimation(MOVE_LEFT);
				if (sprite->animation() == JUMP_RIGHT) sprite->changeAnimation(JUMP_LEFT);
				posPlayer.x -= SPEEDX;
				if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
				{
					posPlayer.x += SPEEDX;
					if (bJumping) {
						sprite->changeAnimation(DESLIZANDO);
						posPlayer.y -= FALL_STEP / 2;
					}
					else sprite->changeAnimation(STAND_LEFT);
				}
			}
			//RIGHT MOVEMENT
			else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
			{
				if (sprite->animation() != MOVE_RIGHT && !bJumping) sprite->changeAnimation(MOVE_RIGHT);
				posPlayer.x += SPEEDX;
				if (sprite->animation() == JUMP_LEFT) sprite->changeAnimation(JUMP_RIGHT);
				if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
				{
					posPlayer.x -= SPEEDX;
					if (bJumping) {
						posPlayer.y -= FALL_STEP / 2;
						sprite->changeAnimation(DESLIZANDO2);
					}
					else sprite->changeAnimation(STAND_RIGHT);
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
			isMolla = false;
			specialMove = 0;
		}
		else if (bJumping) {
			if (isMolla) py = int(startY - 128 * sin(3.14159 * jumpAngle / 180.f));
			posPlayer.y = py;
		}
		// CUANDO ESTAS CAYENDO		
		if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y)) {
			bJumping = false;
			isMolla = false;
			specialMove = 0;
		}
		if (bJumping) updateJump();
		//TRATAR POSIBLE ACTIVACION DE SALTO
		else if (specialMove != 3)
		{
			// CUANDO ESTAS CAYENDO
			posPlayer.y += FALL_STEP;
			if(sprite->animation() == DESLIZANDO2 || sprite->animation() == DESLIZANDO) posPlayer.y -= FALL_STEP/2;
			if (sprite->animation() == DESLIZANDO2 && !leftCol) sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == DESLIZANDO && !rightCol)	sprite->changeAnimation(STAND_RIGHT);
			if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && rightCol && !downCol) {
				polvillo = 2;
				posPlayer.y -= FALL_STEP / 2;
				sprite->changeAnimation(DESLIZANDO2);
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && leftCol && !downCol) {
				polvillo = 2;
				posPlayer.y -= FALL_STEP / 2;
				sprite->changeAnimation(DESLIZANDO);

			}

			
			
			if (!map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y)) {

				if (Game::instance().getKey('c') && !cPressed && rightCol && !upCol) {
					polvillo = 1;
					cPressed = true;
					rightJump();

				}
				else if (Game::instance().getKey('c') && !cPressed && leftCol && !upCol) {
					polvillo = 1;
					cPressed = true;
					leftJump();
				}
					
				
			}
			// CUANDO ESTAS EN EL SUELO
			else {
				
				if (sprite->animation() == DESLIZANDO2) sprite->changeAnimation(STAND_LEFT);
				else if (sprite->animation() == DESLIZANDO)	sprite->changeAnimation(STAND_RIGHT);				

				if (sprite->animation() == JUMP_LEFT) {
					sprite->changeAnimation(STAND_LEFT);
					polvillo = 1;
				}
				else if (sprite->animation() == JUMP_RIGHT) {
					sprite->changeAnimation(STAND_RIGHT);
					polvillo = 1;
				}
				else polvillo = 0;

				if (map->getMolla()) {
					polvillo = 1;
					collisionEffects->play2D("sound/molla.wav", false);
					isMolla = true;
					bJumping = true;
					jumpAngle = 0;
					startY = posPlayer.y;
					map->noMolla();
				}
				isDashing = false;
				posPlayer.x -= 1;
				if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
				{
					posPlayer.x += 1;
					sprite->changeAnimation(STAND_LEFT);
				}
				posPlayer.x += 1;
				if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
				{
					posPlayer.x -= 1;
					sprite->changeAnimation(STAND_RIGHT);
				}
				if (Game::instance().getKey('c') && !cPressed)
				{
					polvillo = 1;
					cPressed = true;
					movementEffects->play2D("sound/jump.wav", false);
					if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT)
						sprite->changeAnimation(JUMP_LEFT);
					else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT)
						sprite->changeAnimation(JUMP_RIGHT);
					bJumping = true;
					specialMove = 0;
					jumpAngle = 0;
					startY = posPlayer.y;
				}
				Yanimations();
			}
		}
	}
	if (posPlayer.x >= 480) {
		posPlayer.x = 480;
		specialMove = 0;
	}
	else if (posPlayer.x <= 0 && posPlayer.x > -1000) {
		posPlayer.x = 0;
		specialMove = 0;
	}
	if (!Game::instance().getKey('c')) {
		cPressed = false;
	}
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x + OFFSETX), float(tileMapDispl.y + posPlayer.y + OFFSETY)));

}

void Player::setDash(bool b) {
	isDashing = b;
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
glm::vec2 Player::getPosition()
{
	return posPlayer;
}

void Player::setInfDash(bool b)
{
	infiniteDash = b;
}

int Player::getResult() {
	int result = 0;
	for (int i = 0; i < 10; ++i) {
		if (strawberries[i]) result += 1;
	}
	return result;
}