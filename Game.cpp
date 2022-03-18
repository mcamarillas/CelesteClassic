#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene.init();
}

bool Game::update(int deltaTime)
{
	scene.update(deltaTime);
	if (change) {
		scene.changeLevel(level);
		change = false;
	}
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
		change = true;
	}
	else if (key == '2') {
		level = 2;
		change = true;
	}
	else if (key == '3') {
		level = 3;
		change = true;
	}
	else if (key == '4') {
		level = 4;
		change = true;
	}
	else if (key == '5') {
		level = 5;
		change = true;
	}
	else if (key == '6') {
		level = 6;
		change = true;
	}
	else if (key == '8') {
		level = 8;
		change = true;
	}
	else if (key == '0') {
		level = 10;
		change = true;
	}
	keys[key] = true;
}


void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
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

int Game::getLevel() {
	return level;
}
int Game::hasChanged() {
	return change;
}





