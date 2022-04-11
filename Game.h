#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"
#include <irrKlang.h>
using namespace irrklang;


#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 512


// Game is a singleton (a class with a single instance) that represents our whole application


enum Mode { MENU, INSTRUCTIONS, GAME, CREDITS };

class Game
{

private:
	Game() {}
	
public:
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	int hasChanged();
	float getSpeed();
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

private:
	int level = 0;
	int prevLvl = 1;
	bool change = false;
	bool bPlay;                       // Continue to play game?
	Scene scene;                      // Scene to render
	bool keys[256], specialKeys[256], push[256]; // Store key states so that 
	enum {IDLE, PRESS, REPEAT, RELEASE};
	ISoundEngine* soundTrack = createIrrKlangDevice();
	Mode mode = MENU;
	int teclat[256];
	float speed;
};


#endif // _GAME_INCLUDE


