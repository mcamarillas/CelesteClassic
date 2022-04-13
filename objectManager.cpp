#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "objectManager.h"

void objectManager::createObject(int id, int type, glm::vec2 position, string s, glm::vec2 d, ShaderProgram& shaderProgram) {
	Object *o = new Object(id,type, position, s, d,  shaderProgram);
	objects[id] = o;
}

bool objectManager::getStrawberry() {
	bool b = SWcaught;
	SWcaught = false;
	return b;
}

void objectManager::deleteObjects() {
	for (std::map<int, Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		delete it->second;
	}
	objects.clear();
}
void objectManager::paintObjects(int deltaTime) {
	clouds.clear();
	for (std::map<int, Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		if (it->second->getType() == 4) clouds.push_back(glm::vec3(it->second->getPosition(), it->second->getID()));
		it->second->update(deltaTime);
	}
}

void objectManager::renderObjects() {
	for (std::map<int, Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		it->second->render();
	}
}

void objectManager::deleteObject(int id) {
	objects.erase(id);
}

bool objectManager::endgamed() {
	return endgame;
}

glm::vec2 objectManager::getPos() {
	return pos;
}

void objectManager::checkCollisions(glm::vec2 posPlayer) {
	for (std::map<int, Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		if (it->second->hasCollisioned(posPlayer)) {
			if (it->second->getType() == 0) {
				SWcaught = true;
				pos = it->second->getPosition();
			}
			if (it->second->getType() == 1) open = true;
			if (it->second->getType() == 2) globo = true;
			if (it->second->getType() == 3) endgame = true;
			delete it->second;
			objects.erase(it);
			break;
		}
	}
}

void objectManager::endendgame() {
	endgame = false;
}


bool objectManager::isOpen()
{
	return open;
}


bool objectManager::isGlobo()
{
	return globo;
}

void objectManager::setOpen(bool o) {
	open = o;
}

void objectManager::setGlobo(bool g)
{
	globo = g;
}

void objectManager::getClouds(vector<glm::vec3>& pos) {
	pos = clouds;
}

bool objectManager::cloudCol(glm::ivec2 pos) {
	for (std::map<int, Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		glm::vec2 i = it->second->getPosition();
		int rangX0 = i.x - 30;
		int rangX1 = i.x + 63;
		int rangY0 = i.y - 32;
		int rangY1 = i.y - 24;
		if (pos.x > rangX0 && pos.x < rangX1 && pos.y > rangY0 && pos.y < rangY1) {
			return true;
		}
	}
	return false;
}

