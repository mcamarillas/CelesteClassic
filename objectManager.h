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
	void createObject(int id, glm::vec2 position, string s,glm::vec2 d, ShaderProgram& shaderProgram);
	void deleteObjects();
	void renderObjects();
	void deleteObject(int id);
private:
	map<int,Object*> objects;

};

#endif