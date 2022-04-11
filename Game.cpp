#include <GL/glew.h>
#include <GL/glut.h>
#include <Windows.h>
#include <cstdlib>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	soundTrack->play2D("sound/st1.wav", false);
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	scene.init();
	speed = 1;
}

float Game::getSpeed() {
	return speed;
}



bool Game::update(int deltaTime)
{

		
	
	if (scene.nextLvl()) {
		scene.resetLvl();
		scene.changeLevel(level+1);
	}
	else if (change || scene.isdead()) {
		scene.changeLevel(level);
		change = false;
		scene.respawn();
	}
	scene.update(deltaTime);
	level = scene.getLvl();
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.render();
}

void Game::keyPressed(int key)
{
	if (key == 27) // Escape code
		bPlay = false;
	else if (key == '1') {
		level = 1;
		prevLvl = 1;
		change = true;
		mode = GAME;
	}
	else if (key == '2') {
		level = 2;
		prevLvl = 2;
		change = true;
		mode = GAME;
	}
	else if (key == '3') {
		level = 3;
		prevLvl = 3;
		change = true;
		mode = GAME;
	}
	else if (key == '4') {
		level = 4;
		prevLvl = 4;
		change = true;
		mode = GAME;
	}
	else if (key == '5') {
		level = 5;
		prevLvl = 5;
		change = true;
		mode = GAME;
	}
	else if (key == '6') {
		level = 6;
		prevLvl = 6;
		change = true;
		mode = GAME;
	}
	else if (key == '7') {
		level = 7;
		prevLvl = 7;
		change = true;
		mode = GAME;
	}
	else if (key == '8') {
		level = 8;
		prevLvl = 8;
		change = true;
		mode = GAME;
	}
	else if (key == '9') {
		level = 9;
		prevLvl = 9;
		change = true;
		mode = GAME;
	}
	else if (key == '0') {
		level = 10;
		prevLvl = 10;
		change = true;
		mode = GAME;
	}
	else if (key == 'f') {
		level = 11;
		prevLvl = 11;
		change = true;
		mode = GAME;
	}
	else if (key == 'i' && mode == MENU) {
		scene.changeInstrucctions();
		mode = INSTRUCTIONS;
	}
	else if (key == 'c' && mode == MENU) {
		scene.changeCredits();
		mode = CREDITS;
	}
	else if (key == 'q') {
		scene.changeMainMenu();
			mode = MENU;
	}
	else if (key == 'p' && mode == MENU) {
		level = prevLvl;
		change = true;
		mode = GAME;
	}
	else if (key == 's') {
		if (speed == 1) speed = 0.5;
		else speed = 1;
	}
	else if (key == 'd') {
		bool b = scene.getInfDash();
		scene.setInfDash(!b);
	}
	keys[key] = true;
}


void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	if (mode == GAME) {
		specialKeys[key] = true;
	}
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}


int Game::hasChanged() {
	return change;
}