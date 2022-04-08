#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 0
#define INIT_PLAYER_Y_TILES 12


Scene::Scene()
{
	map = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}

bool Scene::isdead() {
	return player->getUnderground();
}

bool Scene::nextLvl() {
	return player->getNextLvl();
}

void Scene::respawn() {
	player->respawn();
}

void Scene::resetLvl() {
	player->resetLvl();
}

void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/startScreen.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(-100,-100));
	player->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}	

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	obj.paintObjects(deltaTime);
	player->update(deltaTime);
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	player->render();
	obj.renderObjects();
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

void Scene::changeLevel(int level) {
	Texture t;
	switch (level) {
	case 1:
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
		map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case 2:
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), (INIT_PLAYER_Y_TILES + 2)* map->getTileSize()));
		map = TileMap::createTileMap("levels/level02.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case 3:
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), (INIT_PLAYER_Y_TILES + 1) * map->getTileSize()));
		map = TileMap::createTileMap("levels/level03.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case 4:
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
		map = TileMap::createTileMap("levels/level04.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		obj.createObject(100, 100, "images/Madeline.png", texProgram);
		obj.createObject(200, 200, "images/Madeline.png", texProgram);
		break;	
	case 5:
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), (INIT_PLAYER_Y_TILES - 1) * map->getTileSize()));
		map = TileMap::createTileMap("levels/level05.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case 6:
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), (INIT_PLAYER_Y_TILES - 1) * map->getTileSize()));
		map = TileMap::createTileMap("levels/level06.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case 7:
		player->setPosition(glm::vec2((INIT_PLAYER_X_TILES + 1) * map->getTileSize(), (INIT_PLAYER_Y_TILES + 1) * map->getTileSize()));
		map = TileMap::createTileMap("levels/level07.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case 8:
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), (INIT_PLAYER_Y_TILES + 2) * map->getTileSize()));
		map = TileMap::createTileMap("levels/level08.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case 9:
		player->setPosition(glm::vec2((INIT_PLAYER_X_TILES + 2) * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
		map = TileMap::createTileMap("levels/level09.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	case 10:
		player->setPosition(glm::vec2((INIT_PLAYER_X_TILES + 1) * map->getTileSize(), (INIT_PLAYER_Y_TILES + 1) * map->getTileSize()));
		map = TileMap::createTileMap("levels/level10.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	}
	player->setTileMap(map);
}



