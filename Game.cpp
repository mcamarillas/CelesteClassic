#include <GL/glew.h>
#include <GL/glut.h>
#include <Windows.h>
#include <cstdlib>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	soundTrack->play2D("sound/mm.wav", true);
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	scene.init();
	speed = 1;
}

float Game::getSpeed() {
	return speed;
}



bool Game::update(int deltaTime)
{

	if (scene.getFlag()) mode = Mode::MENU;
	if (scene.getSM()) {
		soundTrack->stopAllSounds();
		soundTrack->play2D("sound/endingBG.wav", true);
	}
	if (scene.nextLvl()) {
		scene.resetLvl();
		scene.changeLevel(level+1);
	}
	else if (change) {
		if (scene.getEnd()) {
			soundTrack->stopAllSounds();
			soundTrack->play2D("sound/st1.wav", true);
			scene.resetEnd();
		}
		scene.changeLevel(level);
		change = false;
		
	}
	else if (scene.isdead()) {
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
	else if (key == 'i' && mode == Mode::MENU) {
		scene.changeInstrucctions();
		mode = Mode::INSTRUCTIONS;
	}
	else if (key == 'c' && mode == Mode::MENU) {
		if (level == 11) {
			level = 0;
			soundTrack->stopAllSounds();
			soundTrack->play2D("sound/mm.wav", true);
		}
		scene.changeCredits();
		mode = Mode::CREDITS;
	}
	if (key == 'q') {
		if (level == 11) {
			level = 0;
			soundTrack->stopAllSounds();
			soundTrack->play2D("sound/mm.wav", true);
		}
		if (mode == Mode::GAME) {
			soundTrack->stopAllSounds();
			soundTrack->play2D("sound/mm.wav", true);
		}
		scene.changeMainMenu();		
		mode = Mode::MENU;
	}
	else if (key == 'p' && mode == Mode::MENU) {
		level = prevLvl;
		change = true;
		mode = Mode::GAME;
		soundTrack->stopAllSounds();
		soundTrack->play2D("sound/st1.wav", true);
	}
	else if (key == 's') {
		if (speed == 1) speed = 0.5;
		else speed = 1;
	}
	else if (key == 'd') {
		bool b = scene.getInfDash();
		scene.setInfDash(!b);
	}
	else if (mode != Mode::CREDITS && mode != Mode::INSTRUCTIONS){
		if (mode == Mode::MENU) {
			mode = Mode::GAME;
			soundTrack->stopAllSounds();
			soundTrack->play2D("sound/st1.wav", true);
		}
		if (key == '1') {
		level = 1;
		prevLvl = 1;
		change = true;
		mode = Mode::GAME;
		}
		else if (key == '2') {
		level = 2;
		prevLvl = 2;
		change = true;
		mode = Mode::GAME;
		}
		else if (key == '3') {
		level = 3;
		prevLvl = 3;
		change = true;
		mode = Mode::GAME;
		}
		else if (key == '4') {
		level = 4;
		prevLvl = 4;
		change = true;
		mode = Mode::GAME;
		}
		else if (key == '5') {
		level = 5;
		prevLvl = 5;
		change = true;
		mode = Mode::GAME;
		}
		else if (key == '6') {
		level = 6;
		prevLvl = 6;
		change = true;
		mode = Mode::GAME;
		}
		else if (key == '7') {
		level = 7;
		prevLvl = 7;
		change = true;
		mode = Mode::GAME;
		}
		else if (key == '8') {
		level = 8;
		prevLvl = 8;
		change = true;
		mode = Mode::GAME;
		}
		else if (key == '9') {
		level = 9;
		prevLvl = 9;
		change = true;
		mode = Mode::GAME;
		}
		else if (key == '0') {
		level = 10;
		prevLvl = 10;
		change = true;
		mode = Mode::GAME;
		}
		else if (key == 'f') {
		level = 11;
		prevLvl = 11;
		change = true;
		mode = Mode::GAME;
		}
	}
	
	
	keys[key] = true;
}


void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	if (mode == Mode::GAME) {
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