#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"


using namespace std;

vector<int> nonCollisionableBlock = { 0, 4, 5, 6, 7, 19, 20, 24, 25, 26, 27, 31, 32, 33, 34, 76, 88, 85, 86, 87};
vector<int> spikesX = { 85, 86 };
vector<int> spikesY = { 7, 87 };

TileMap *TileMap::createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	TileMap *map = new TileMap(levelFile, minCoords, program);
	
	return map;
}


TileMap::TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
	mPos = minCoords;
	texProgram = program;
}

TileMap::~TileMap()
{
	if(map != NULL)
		delete map;
}


void TileMap::render() const
{
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * mapSize.x * mapSize.y);
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool TileMap::loadLevel(const string &levelFile)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char tile;
	
	fin.open(levelFile.c_str());
	if(!fin.is_open())
		return false;
	getline(fin, line);
	if(line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);
	
	ticks = new int[mapSize.x * mapSize.y];
	map = new int[mapSize.x * mapSize.y];
	mapAux = new int[mapSize.x * mapSize.y];
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			char c;
			fin.get(tile);
			char aux = tile;
			fin.get(tile);
			if (tile == ' ') {
				map[j * mapSize.x + i] = 0;
				mapAux[j * mapSize.x + i] = 0;
			}
			else {
				int a = (aux - '0') * 10 + tile - '0';
				map[j * mapSize.x + i] = a;
				mapAux[j * mapSize.x + i] = a;
			}
		}
		fin.get(tile);
#ifndef _WIN32
		fin.get(tile);
#endif
	}
	fin.close();
	
	return true;
}

void TileMap::prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program)
{
	int tile, nTiles = 0;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;
	
	halfTexel = glm::vec2(0.0f / tilesheet.width(), 0.0f / tilesheet.height());
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];
			if(tile != 0)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				texCoordTile[0] = glm::vec2(float((tile-1)%tilesheetSize.x) / tilesheetSize.x, float((tile-1)/tilesheetSize.x) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				//texCoordTile[0] += halfTexel;
				texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4*sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));
}

// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool TileMap::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) 
{
	int x, y0, y1;
	
	x = pos.x / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for(int y=y0; y<=y1; y++)
	{
		destroyWall(x, y);
		if (count(spikesX.begin(), spikesX.end(), map[(y)*mapSize.x + x])) spikes = true;
		if(!count(nonCollisionableBlock.begin(), nonCollisionableBlock.end(), map[y*mapSize.x + x]))
			return true;

	}
	
	return false;
}

bool TileMap::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size)
{
	int x, y0, y1;	
	x = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for(int y=y0; y<=y1; y++)
	{
		destroyWall(x, y);
		if(!count(nonCollisionableBlock.begin(), nonCollisionableBlock.end(), map[y*mapSize.x + x]))
			return true;
		if (map[(y)*mapSize.x + x] == 68) {
			ticks[(y)*mapSize.x + x] = 0;
			map[(y)*mapSize.x + x] = 69;
			destroy = true;
		}
		if (count(spikesX.begin(), spikesX.end(), map[(y) * mapSize.x + x])) spikes = true;
	}
	
	return false;
}

bool TileMap::getSpikes() {
	return spikes;
}

bool TileMap::getMolla() {
	return molla;
}


void TileMap::respawn() {
	spikes = false;
}

void TileMap::noMolla() {
	molla = false;
}


bool TileMap::collisionMoveDown(glm::ivec2& pos, const glm::ivec2& size, int* posY) 
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	bool result = false;

	for (int x = x0; x <= x1; x++)
	{
		destroyWall(x, y);
		if (!count(nonCollisionableBlock.begin(), nonCollisionableBlock.end(), map[y * mapSize.x + x]) || map[y * mapSize.x + x] == 76)
		{
			if (*posY - tileSize * y + size.y < 32)
			{
				*posY = tileSize * y - size.y;
				result = true;
			}
					
		}

		if (count(spikesY.begin(), spikesY.end(), map[(y-1) * mapSize.x + x])) spikes = true;
		if (48 == map[(y)*mapSize.x + x]) {
			map[(y)*mapSize.x + x] = 49;
			countt = 0;
			prepareArrays(mPos, texProgram);
			molla = true;
			updateMap = true;
		}
		if (map[(y)*mapSize.x + x] == 68) {
			ticks[(y)*mapSize.x + x] = 0;
			map[(y)*mapSize.x + x] = 69;
			destroy = true;
		}
	}
	
	for (glm::vec3 i : cloudPos) {
		int rangX0 = i.x - 30;
		int rangX1 = i.x + 63;
		int rangY0 = i.y - 5;
		int rangY1 = i.y + 5;
		y = (i.y + size.y) / tileSize;
		int x = i.x / tileSize;
		map[(y)*mapSize.x + x - 1] = mapAux[(y)*mapSize.x + x - 1];
		map[(y)*mapSize.x + x + 2] = mapAux[(y)*mapSize.x + x + 2];
		map[(y)*mapSize.x + x + 3] = mapAux[(y)*mapSize.x + x + 3];
		if (pos.x > rangX0 && pos.x < rangX1 && *posY < rangY1 && *posY > rangY0) {
			map[(y)*mapSize.x + x] = 76;
			map[(y)*mapSize.x + x + 1] = 76;
			map[(y)*mapSize.x + x + 2] = 76;
			if (int(i.z) % 2 == 0) {
				pos.x += 1;
				if (collisionMoveRight(pos, glm::ivec2(32, 32))) pos.x -= 1;
			}
			else {
				pos.x -= 1;
				if (collisionMoveLeft(pos, glm::ivec2(32, 32))) pos.x += 1;
			}
		}
		else {
			if (i.x > 510) {
				map[(y)*mapSize.x + 0] = mapAux[(y)*mapSize.x + 0];
				map[(y)*mapSize.x + 1] = mapAux[(y)*mapSize.x + 1];
				map[(y)*mapSize.x + 2] = mapAux[(y)*mapSize.x + 2];
			}
			map[(y)*mapSize.x + x] = mapAux[(y)*mapSize.x + x];
			map[(y)*mapSize.x + x + 1] = mapAux[(y)*mapSize.x + x + 1];
		}
	}
	

	return result;
}

bool TileMap::collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, int* posY) 
{
	int x0, x1, y,r;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	r = *posY / tileSize - 1;
	for (int x = x0; x <= x1; x++)
	{
		destroyWall(x, y - 1);
		if (!count(nonCollisionableBlock.begin(), nonCollisionableBlock.end(), map[(y - 1)*mapSize.x + x]))
		{			
			int a = *posY;
			int b = tileSize * (y-1) + size.y;
			if (a < b)
			{
				*posY = tileSize * y - size.y;
				return true;
			}
			
		}
	}

	return false;
}

glm::vec2 TileMap::openCofre() {
	for (int j = 0; j < mapSize.y; j++) {
		for (int i = 0; i < mapSize.x; i++) {
			if (map[j * mapSize.x + i] == 74) {
				map[j * mapSize.x + i] = 0;
				prepareArrays(mPos, texProgram);
				return glm::vec2(i, j - 2);
			}
		}
	}
}

void TileMap::destroyFloor() {
	for (int j = 0; j < mapSize.y; j++) {
		for (int i = 0; i < mapSize.x; i++) {
			if (map[j * mapSize.x + i] == 69) {
				if (ticks[j * mapSize.x + i] == 16) map[j * mapSize.x + i] = 70;
			}
			else if (map[j * mapSize.x + i] == 70) {
				if (ticks[j * mapSize.x + i] == 32) map[j * mapSize.x + i] = 88;
			}
			else if (map[j * mapSize.x + i] == 88) {
				if (ticks[j * mapSize.x + i] == 64) map[j * mapSize.x + i] = 68;
			}
			ticks[j * mapSize.x + i]++;
		}
	}
	prepareArrays(mPos, texProgram);
}

void TileMap::changeCoords(glm::vec2 pos)
{
	mPos = pos;
	prepareArrays(mPos, texProgram);
}

void TileMap::setCloudsCol(vector<glm::vec3>& pos)
{
	cloudPos = pos;
}

void TileMap::update() {
	if (updateMap == true) countt++;
	if (updateMap == true && countt == 10) {
		countt = 0;
		updateMap = false;
		for (int j = 0; j < mapSize.y; j++) {
			for (int i = 0; i < mapSize.x; i++) {
				if (map[j * mapSize.x + i] == 49) {
					map[j * mapSize.x + i] = 48;
					prepareArrays(mPos, texProgram);
				}
			}
		}
	}
	if(destroy) destroyFloor();
}

void TileMap::destroyWall(int x, int y) {
	if (map[y * mapSize.x + x] == 30) {
		map[y * mapSize.x + x] = 0;
		map[y * mapSize.x + x - 1] = 0;
		map[(y-1) * mapSize.x + x] = 33;
		map[(y-1) * mapSize.x + x - 1] = 26;
		creaFresa = true;
		prepareArrays(mPos, texProgram);
		posFresa = glm::vec2(x - 0.5, y - 2);
	}
	else if (map[y * mapSize.x + x] == 29) {
		map[y * mapSize.x + x] = 0;
		map[y * mapSize.x + x + 1] = 0;
		map[(y - 1) * mapSize.x + x] = 26;
		map[(y - 1) * mapSize.x + x + 1] = 33;
		creaFresa = true;
		prepareArrays(mPos, texProgram);
		posFresa = glm::vec2(x + 0.5, y - 2);
	}
	else if (map[y * mapSize.x + x] == 23) {
		map[y * mapSize.x + x] = 33;
		map[y * mapSize.x + x - 1] = 26;
		map[(y + 1) * mapSize.x + x] = 0;
		map[(y + 1) * mapSize.x + x - 1] = 0;
		creaFresa = true;
		prepareArrays(mPos, texProgram);
		posFresa = glm::vec2(x - 0.5, y - 1);
	}
	else if (map[y * mapSize.x + x] == 22) {
		map[y * mapSize.x + x] = 26;
		map[y * mapSize.x + x + 1] = 33;
		map[(y + 1) * mapSize.x + x] = 0;
		map[(y + 1) * mapSize.x + x + 1] = 0;
		creaFresa = true;
		prepareArrays(mPos, texProgram);
		posFresa = glm::vec2(x - 0.5, y - 1);
	}
	
}

bool TileMap::getCreaFresa(glm::vec2 &pos)
{
	pos = posFresa;
	return creaFresa;
}

void TileMap::setCreaFresa(bool b)
{
	creaFresa = b;
}





























