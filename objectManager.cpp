#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "objectManager.h"

void objectManager::createObject(int id, int type, glm::vec2 position, string s, glm::vec2 d, ShaderProgram& shaderProgram) {
	Object *o = new Object(id,type, position, s, d,  shaderProgram);
	objects[id] = o;
}

void objectManager::deleteObjects() {
	objects.clear();
}
void objectManager::paintObjects(int deltaTime) {
	for (std::map<int, Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
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

void objectManager::checkCollisions(glm::vec2 posPlayer) {
	for (std::map<int, Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		if (it->second->hasCollisioned(posPlayer)) {
			if (it->second->getType() == 1) open = true;
			if (it->second->getType() == 2) globo = true;
			objects.erase(it);
			break;
		}
	}
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


