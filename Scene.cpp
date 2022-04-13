#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 0
#define SCREEN_Y -32

#define INIT_PLAYER_X_TILES 0
#define INIT_PLAYER_Y_TILES 12

Scene::Scene()
{
	map = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
}

bool Scene::isdead() {
	return player->getUnderground();
}

bool Scene::nextLvl() {
	return player->getNextLvl();
}

void Scene::respawn() {
	switch (lvl) {
	case 1:
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
		break;
	case 2:
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), (INIT_PLAYER_Y_TILES + 2) * map->getTileSize()));
		break;
	case 3:
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), (INIT_PLAYER_Y_TILES + 1) * map->getTileSize()));
		break;
	case 4:
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
		break;
	case 5:
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), (INIT_PLAYER_Y_TILES - 1) * map->getTileSize()));
		break;
	case 6:
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), (INIT_PLAYER_Y_TILES - 1) * map->getTileSize()));
		obj.createObject(1, 2, glm::vec2(9, 8), "images/globo.png", glm::vec2(1. / 3, 1), texProgram);
		break;
	case 7:
		player->setPosition(glm::vec2((INIT_PLAYER_X_TILES + 1) * map->getTileSize(), (INIT_PLAYER_Y_TILES + 1) * map->getTileSize()));
		break;
	case 8:
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), (INIT_PLAYER_Y_TILES + 2) * map->getTileSize()));
		obj.createObject(1, 2, glm::vec2(7, 4), "images/globo.png", glm::vec2(1. / 3, 1), texProgram);
		break;
	case 9:
		player->setPosition(glm::vec2((INIT_PLAYER_X_TILES + 2) * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
		obj.createObject(1, 2, glm::vec2(8, 4), "images/globo.png", glm::vec2(1. / 3, 1), texProgram);
		obj.createObject(2, 2, glm::vec2(4.5, 4), "images/globo.png", glm::vec2(1. / 3, 1), texProgram);
		break;
	case 10:
		player->setPosition(glm::vec2((INIT_PLAYER_X_TILES + 1) * map->getTileSize(), (INIT_PLAYER_Y_TILES + 1) * map->getTileSize()));
		break;
	case 11:
		stopMusic = true;
		glClearColor(0.5254f, 0.1882f, 0.3294f, 1.0f);
		background.setCloudColor("images/rosita.png");
		player->setPosition(glm::vec2((INIT_PLAYER_X_TILES + 1) * map->getTileSize(), (INIT_PLAYER_Y_TILES + 1) * map->getTileSize()));
		map = TileMap::createTileMap("levels/final.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

		break;
	}
	player->respawn();
}


void Scene::resetLvl() {
	player->resetLvl();
}

void Scene::init()
{
	initShaders();
	lvl = 0;
	map = TileMap::createTileMap("levels/startScreen.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	s = "levels/startScreen.txt";
	player = new Player();
	player->initStrawberries();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(-1001, 100));
	player->setTileMap(map);
	background.init(texProgram);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

bool Scene::getSM() {
	bool b = stopMusic;
	stopMusic = false;
	return b;
}

void Scene::update(int deltaTime)
{
	
	currentTime += deltaTime;
		obj.paintObjects(deltaTime);
		vector<glm::vec3> pos;
		obj.getClouds(pos);
		map->setCloudsCol(pos);
		player->update(deltaTime);
		if (player->getUnderground()) {
			glm::vec2 aux = player->getPosition();
			aux.x -= 64;
			aux.y -= 64;
			background.createParticles("images/muerte2.png", aux, texProgram);
		}
		if (obj.getStrawberry()) {
			background.createParticles("images/points.png", obj.getPos(), texProgram);
			player->updateSB();
		}
		obj.checkCollisions(player->getPosition());
		if (obj.isOpen()) {
			glm::vec2 newPos = map->openCofre();
			obj.createObject(12, 0, newPos, "images/fresita.png", glm::vec2(1, 1), texProgram);
			obj.setOpen(false);
		}
		if (obj.isGlobo()) {
			player->setDash(false);
			obj.setGlobo(false);
		}
		glm::vec2 p;
		if (map->getCreaFresa(p)) {
			obj.createObject(1, 0, p, "images/fresita.png", glm::vec2(1, 1), texProgram);
			map->setCreaFresa(false);
		}
			if (player->getPolvillo() == 1) background.createParticles("images/polvo.png", player->getPosition(), texProgram);
			else if (player->getPolvillo() == 3) {
				glm::vec2 aux = player->getPosition();
				aux.x -= 32;
				background.createParticles("images/polvo2.png", aux, texProgram);
			}
			else if (player->getPolvillo() == 4) {
				glm::vec2 aux = player->getPosition();
				aux.x += 32;
				background.createParticles("images/polvo2.png", aux, texProgram);
			}
			else if (player->getPolvillo() == 5) {
				glm::vec2 aux = player->getPosition();
				aux.y += 32;
				background.createParticles("images/polvo2.png", aux, texProgram);
			}
			else if (player->getPolvillo() == 6) {
				glm::vec2 aux = player->getPosition();
				aux.y -= 32;
				background.createParticles("images/polvo2.png", aux, texProgram);
			}
		if (obj.endgamed()) {
			obj.endendgame();
			int x = player->getResult();
			lvl = 11;
			//sto1pMusic = true;
			if(x == 0) obj.createObject(5, 5, glm::vec2(4.5, 1), "images/fondo0.png", glm::vec2(1, 1), texProgram);
			else if (x == 1) obj.createObject(5, 5, glm::vec2(4.5, 1), "images/fondo1.png", glm::vec2(1, 1), texProgram);
			else if (x == 2) obj.createObject(5, 5, glm::vec2(4.5, 1), "images/fondo2.png", glm::vec2(1, 1), texProgram);
			else if (x == 3) obj.createObject(5, 5, glm::vec2(4.5, 1), "images/fondo3.png", glm::vec2(1, 1), texProgram);
			else if (x == 4) obj.createObject(5, 5, glm::vec2(4.5, 1), "images/fondo4.png", glm::vec2(1, 1), texProgram);
			else if (x == 5) obj.createObject(5, 5, glm::vec2(4.5, 1), "images/fondo5.png", glm::vec2(1, 1), texProgram);
			else if (x == 6) obj.createObject(5, 5, glm::vec2(4.5, 1), "images/fondo6.png", glm::vec2(1, 1), texProgram);
			sceneEffects->play2D("sound/ending.wav", false);
			flagCaught = true;
		}
	background.updateBackground(deltaTime);
	map->update();
	player->setInfDash(infDash);
	
}

bool Scene::getFlag() {
	bool b = flagCaught;
	flagCaught = false;
	return b;
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	if (player->getTicks() > 0) {
		player->stopDashMove();
		int t = player->getTicks();
		if (t % 2 == 0) t = -t;
		map->changeCoords(glm::vec2(SCREEN_X+t, SCREEN_Y+t));
	}
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	background.renderBackground();

	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);

	map->render();
	obj.renderObjects();
	player->render();
	background.renderParticles();
	background.renderSnow();
}

int Scene::getLvl() {
	return lvl;
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();

	texProgram2.init();
	texProgram2.addShader(vShader);
	texProgram2.addShader(fShader);
	texProgram2.link();
	if (!texProgram2.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram2.log() << endl << endl;
	}
	texProgram2.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

bool Scene::getEnd() {
	return end;
}

void Scene::resetEnd() {
	end = false;
}


void Scene::changeLevel(int level) {
	obj.deleteObjects();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	background.setCloudColor("images/Blue.png");
	player->setLvl(level);
	switch (level) {
	case 1:
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
		map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		lvl = level;
		s = "levels/level01.txt";
		break;
	case 2:
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), (INIT_PLAYER_Y_TILES + 2) * map->getTileSize()));
		map = TileMap::createTileMap("levels/level02.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		lvl = level;
		s = "levels/level02.txt";
		break;
	case 3:
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), (INIT_PLAYER_Y_TILES + 1) * map->getTileSize()));
		map = TileMap::createTileMap("levels/level03.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		lvl = level;
		s = "levels/level03.txt";
		obj.createObject(12, 0, glm::vec2(1, 5), "images/fresita.png", glm::vec2(1, 1), texProgram);
		break;
	case 4:
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
		map = TileMap::createTileMap("levels/level04.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		obj.createObject(12,0, glm::vec2(2, 5), "images/fresita.png", glm::vec2(1, 1), texProgram);
		lvl = level;
		s = "levels/level04.txt";
		break;
	case 5:
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), (INIT_PLAYER_Y_TILES - 1) * map->getTileSize()));
		map = TileMap::createTileMap("levels/level05.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		lvl = level;
		s = "levels/level05.txt";
		obj.createObject(1, 1, glm::vec2(7, 14), "images/llave.png", glm::vec2(1./3, 1), texProgram);
		break;
	case 6:
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), (INIT_PLAYER_Y_TILES - 1) * map->getTileSize()));
		map = TileMap::createTileMap("levels/level06.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		obj.createObject(1, 2, glm::vec2(9, 8), "images/globo.png", glm::vec2(1./3, 1), texProgram);
		lvl = level;
		s = "levels/level06.txt";
		break;
	case 7:
		player->setPosition(glm::vec2((INIT_PLAYER_X_TILES + 1) * map->getTileSize(), (INIT_PLAYER_Y_TILES + 1) * map->getTileSize()));
		map = TileMap::createTileMap("levels/level07.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		lvl = level;
		obj.createObject(0, 4, glm::vec2(3, 5), "images/nube.png", glm::vec2(1, 1), texProgram);
		obj.createObject(2, 4, glm::vec2(11, 5), "images/nube.png", glm::vec2(1, 1), texProgram);
		obj.createObject(1, 4, glm::vec2(1, 8), "images/nube.png", glm::vec2(1, 1), texProgram);
		obj.createObject(3, 4, glm::vec2(9, 8), "images/nube.png", glm::vec2(1, 1), texProgram);
		obj.createObject(4, 4, glm::vec2(3, 11), "images/nube.png", glm::vec2(1, 1), texProgram);
		obj.createObject(6, 4, glm::vec2(8.6, 11), "images/nube.png", glm::vec2(1, 1), texProgram);
		obj.createObject(8, 4, glm::vec2(14.2,11), "images/nube.png", glm::vec2(1, 1), texProgram);
		obj.createObject(5, 4, glm::vec2(3, 13), "images/nube.png", glm::vec2(1, 1), texProgram);
		obj.createObject(7, 4, glm::vec2(8.6, 13), "images/nube.png", glm::vec2(1, 1), texProgram);
		obj.createObject(9, 4, glm::vec2(14.2,13), "images/nube.png", glm::vec2(1, 1), texProgram);
		obj.createObject(12, 0, glm::vec2(10, 3), "images/fresita.png", glm::vec2(1, 1), texProgram);
		s = "levels/level07.txt";
		break;
	case 8:
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), (INIT_PLAYER_Y_TILES + 2) * map->getTileSize()));
		map = TileMap::createTileMap("levels/level08.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		obj.createObject(1, 2, glm::vec2(7, 4), "images/globo.png", glm::vec2(1. / 3, 1), texProgram);
		lvl = level;
		s = "levels/level08.txt";
		break;
	case 9:
		player->setPosition(glm::vec2((INIT_PLAYER_X_TILES + 2) * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
		map = TileMap::createTileMap("levels/level09.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		obj.createObject(1, 2, glm::vec2(8, 4), "images/globo.png", glm::vec2(1. / 3, 1), texProgram);
		obj.createObject(2, 2, glm::vec2(4.5, 4), "images/globo.png", glm::vec2(1. / 3, 1), texProgram);
		lvl = level;
		s = "levels/level09.txt";
		break;
	case 10:
		player->setPosition(glm::vec2((INIT_PLAYER_X_TILES + 1) * map->getTileSize(), (INIT_PLAYER_Y_TILES + 1) * map->getTileSize()));
		map = TileMap::createTileMap("levels/level10.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		lvl = level;
		s = "levels/level10.txt";
		break;
	case 11:
		stopMusic = true;
		end = true;
		glClearColor(0.5254f, 0.1882f, 0.3294f, 1.0f);
		background.setCloudColor("images/rosita.png");
		player->setPosition(glm::vec2((INIT_PLAYER_X_TILES + 1) * map->getTileSize(), (INIT_PLAYER_Y_TILES + 1) * map->getTileSize()));
		map = TileMap::createTileMap("levels/final.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		obj.createObject(1, 3, glm::vec2(7, 7), "images/banderaEspaña.png", glm::vec2(1. / 3, 1), texProgram);
		lvl = level;
		break;
	}
	player->setTileMap(map);
}


void Scene::changeInstrucctions() {
	lvl = 0;
	player->setPosition(glm::vec2(-1001, 100));
	obj.deleteObjects();
		map = TileMap::createTileMap("levels/pauseScreen.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
}

void Scene::changeCredits() {
	lvl = 0;
	player->setPosition(glm::vec2(-1001, 100));
	obj.deleteObjects();
	map = TileMap::createTileMap("levels/creditsScreen.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
}

void Scene::changeMainMenu() {
	lvl = 0;
	player->setPosition(glm::vec2(-1001, 100));
	obj.deleteObjects();
	map = TileMap::createTileMap("levels/startScreen.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
}

bool Scene::getInfDash()
{
	return infDash;
}

void Scene::setInfDash(bool b)
{
	infDash = b;
}

