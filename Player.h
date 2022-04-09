#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include <irrKlang.h>
using namespace irrklang;


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
    void update(int deltaTime);
    void render();
    void setTileMap(TileMap* tileMap);
    void setPosition(const glm::vec2& pos);
    bool getUnderground();
    void respawn();
    void resetLvl();
    bool getNextLvl();
    glm::vec2 getPosition();

private:
    bool bJumping;
    bool isDashing;
    bool leftCol, rightCol, downCol, upCol;
    bool underGround = false;
    bool nextLvl = false;
    glm::ivec2 tileMapDispl, posPlayer;
    int jumpAngle, dashAngle, startY, specialMove, dashX, dashY;
    Texture spritesheet;
    Sprite* sprite;
    TileMap* map;
    ISoundEngine* collisionEffects = createIrrKlangDevice();
    ISoundEngine* movementEffects = createIrrKlangDevice();
    ISoundEngine* movementEffectsL = createIrrKlangDevice();
    ISoundEngine* movementEffectsR = createIrrKlangDevice();
    ISoundEngine* goalEffects = createIrrKlangDevice();
    void moveLeft();
    void moveRight();
    void updateJump();
    void dash(); 
    void checkCollisions();
	void rightJump();
	void leftJump();
    void mollaJump();
    bool isMolla;


};


#endif // _PLAYER_INCLUDE
