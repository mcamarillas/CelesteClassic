#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"


#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 512


// Game is a singleton (a class with a single instance) that represents our whole application


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
	int getLevel();
	int hasChanged();
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

private:
	int level = 1;
	bool change = false;
	bool bPlay;                       // Continue to play game?
	Scene scene;                      // Scene to render
	bool keys[256], specialKeys[256], push[256]; // Store key states so that 
	                                  // we can have access at any time
	enum {IDLE, PRESS, REPEAT, RELEASE};
	int teclat[256];

};


#endif // _GAME_INCLUDE


