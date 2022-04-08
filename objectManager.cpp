#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "objectManager.h"

void objectManager::createObject(int x, int y, string s, ShaderProgram& shaderProgram) {
	Object *o = new Object(x, y, s, shaderProgram);
	objects.push_back(o);
}

void objectManager::deleteObjects() {
	objects.clear();
}
void objectManager::paintObjects(int deltaTime) {
	for (Object *o : objects) {
		o->update(deltaTime);
	}
}

void objectManager::renderObjects() {
	for (Object *o : objects) {
		o->render();
	}
}