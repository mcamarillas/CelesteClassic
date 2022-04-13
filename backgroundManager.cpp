#include "backgroundManager.h"

void backgroundManager::init(ShaderProgram& shaderProgram) {
	srand(time(NULL));
	
	shader = shaderProgram;

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
		int x = (rand() % 5) + 3;
		int speed = (rand() % 5) + 1;
		int A = (rand() % 25) + 10;
		float w = (rand() % 4 + 1)/ 100.f;
		b->init("images/White.png", glm::vec2(x1, y1), glm::vec2(x,x), speed, shaderProgram);
		b->setA(A);
		b->setW(w);
		snows[i] = b;
	}
}

void backgroundManager::setCloudColor(string s) {
	for (std::map<int, Background*>::iterator it = backgrounds.begin(); it != backgrounds.end(); ++it) {
		it->second->changeColor(s);
	}
}

void backgroundManager::createParticles(string s, glm::vec2 pos, ShaderProgram& shaderProgram)
{
	Background* b = new Background();
	b->createParticles(s, glm::vec2(pos.x, pos.y - 32), shaderProgram);
	b->setTicks(0);
	if (s == "images/points.png")  particles[99] = b;
	else if (s == "images/muerte2.png") particles[100] = b;
	else if (particles.find(0) == particles.end()) particles[0] = b;
	else if (particles.find(1) == particles.end()) particles[1] = b;
	else if (particles.find(2) == particles.end()) particles[2] = b;
	else particles[3] = b;

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
	for (std::map<int, Background*>::iterator it = particles.begin(); it != particles.end(); ++it) {
		if (it->second->addTicks() == 25) {
			delete it->second;
			particles.erase(it);
			break;
		}
		it->second->updateParticles(deltaTime);
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

void backgroundManager::renderParticles() {
	for (std::map<int, Background*>::iterator it = particles.begin(); it != particles.end(); ++it) {
		it->second->render();
	}
}

