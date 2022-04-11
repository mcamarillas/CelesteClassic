#ifndef _OBJECTMANAGER_INCLUDE
#define _OBJECTMANAGER_INCLUDE

#include "Object.h"
#include <vector>
#include <map>

#pragma
class objectManager
{
	
public:
	void paintObjects(int deltaTime);
	void createObject(int id, int type,glm::vec2 position, string s,glm::vec2 d, ShaderProgram& shaderProgram);
	void deleteObjects();
	void renderObjects();
	void deleteObject(int id);
	void checkCollisions(glm::vec2 posPlayer);
	bool isOpen();
	bool isGlobo();
	void setOpen(bool o);
	void setGlobo(bool g);
	void getClouds(vector<glm::vec2> &pos);
	bool cloudCol(glm::ivec2 pos);

private:
	map<int,Object*> objects;
	vector<glm::vec2> clouds;
	bool open = false;
	bool globo = false;

};

#endif