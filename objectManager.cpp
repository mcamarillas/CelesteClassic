#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "objectManager.h"

void objectManager::createObject(int id, glm::vec2 position, string s, glm::vec2 d, ShaderProgram& shaderProgram) {
	Object *o = new Object(id, position, s, d,  shaderProgram);
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

