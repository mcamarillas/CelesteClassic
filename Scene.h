#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "objectManager.h"
#include "Background.h"

// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	void changeLevel(int level);
	bool isdead();
	void respawn();
	bool nextLvl();
	void resetLvl();
	void changeInstrucctions();
	void changeCredits();
	void changeMainMenu();


private:
	void initShaders();

private:
	TileMap* map;
	Player* player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	objectManager obj;
	Background *background = new Background();
};


#endif // _SCENE_INCLUDE