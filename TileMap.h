#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include <vector>
#include "Texture.h"
#include "ShaderProgram.h"


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class TileMap
{

private:
	TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap *createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

	~TileMap();

	void render() const;
	void update();
	void free();
	int getTileSize() const { return tileSize; }
	bool getSpikes();
	bool getMolla();
	void noMolla();
	void respawn();
	bool collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size);
	bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size);
	bool collisionMoveDown(glm::ivec2& pos, const glm::ivec2& size, int* posY);
	bool collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, int* posY);
	glm::vec2 openCofre();
	void destroyFloor();
	void changeCoords(glm::vec2 pos);
	void setCloudsCol(vector<glm::vec3>& pos);
	void destroyWall(int x, int y);
	bool getCreaFresa(glm::vec2 &pos);
	void setCreaFresa(bool b);
private:
	bool loadLevel(const string &levelFile);
	void prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program);

	

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	glm::vec2 posFresa;
	int *map, *mapAux, *ticks;
	bool spikes = false;
	bool molla = false;
	bool updateMap = false;
	bool destroy = false;
	bool creaFresa = false;
	glm::vec2 mPos;
	ShaderProgram texProgram;
	int countt = 0;
	vector<glm::vec3> cloudPos;
	

};


#endif // _TILE_MAP_INCLUDE


