#include "backgroundManager.h"

void backgroundManager::init(ShaderProgram& shaderProgram) {
	srand(time(NULL));
	

	for (int i = 0; i < 15; ++i) {
		int x1 = (rand() % 30) -30;
		int x = (rand() % 512) / 512. * 200 + 100;
		int y = rand() % 512 / 512.f * 20 + 20;
		int speed = (rand() % 4) + 1;
		Background* b = new Background();
		b->init("images/Blue.png", glm::vec2(x1,i), glm::vec2(x,y),speed, shaderProgram);
		backgrounds[i] = b;
	}

	for (int i = 0; i < 40; ++i) {
		Background* b = new Background();
		int x1 = (rand() % 100) - 100;
		int y1 = (rand() % 16);
		int x = (rand() % 7) + 1;
		int speed = (rand() % 4) + 1;
		b->init("images/White.png", glm::vec2(x1, y1), glm::vec2(x,x), speed, shaderProgram);
		snows[i] = b;
	}
}

void backgroundManager::updateBackground(int deltaTime) {
	for (std::map<int, Background*>::iterator it = backgrounds.begin(); it != backgrounds.end(); ++it) {
		it->second->updateX();
		it->second->update(deltaTime);
	}
	for (std::map<int, Background*>::iterator it = snows.begin(); it != snows.end(); ++it) {
		it->second->updateX();
		it->second->updateYSnow();
		it->second->update(deltaTime);
	}
}

void backgroundManager::renderBackground() {
	for (std::map<int, Background*>::iterator it = backgrounds.begin(); it != backgrounds.end(); ++it) {
		it->second->render();
	}
	
}

void backgroundManager::renderSnow() {
	for (std::map<int, Background*>::iterator it = snows.begin(); it != snows.end(); ++it) {
		it->second->render();
	}
}