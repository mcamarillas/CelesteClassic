#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "objectManager.h"
#include "backgroundManager.h"
using namespace irrklang;

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
	int getLvl();
	bool isdead();
	void respawn();
	bool nextLvl();
	void resetLvl();
	void changeInstrucctions();
	void changeCredits();
	void changeMainMenu();
	bool getInfDash();
	void setInfDash(bool b);
	bool getSM();
	void resetEnd();
	bool getEnd();
	bool getFlag();

private:
	void initShaders();

private:
	TileMap* map;
	Player* player;
	ShaderProgram texProgram, texProgram2;
	float currentTime;
	glm::mat4 projection;
	objectManager obj;
	int lvl;
	string s;
	bool end = false;
	bool infDash = false;
	bool stopMusic = false;
	bool flagCaught = false;
	backgroundManager background;
	ISoundEngine* sceneEffects = createIrrKlangDevice();
	ISoundEngine* sceneBG = createIrrKlangDevice();
};


#endif // _SCENE_INCLUDE