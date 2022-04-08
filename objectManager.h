#ifndef _OBJECTMANAGER_INCLUDE
#define _OBJECTMANAGER_INCLUDE

#include "Object.h"
#include <vector>

#pragma
class objectManager
{
	
public:
	void paintObjects(int deltaTime);
	void createObject(int x, int y, string s, ShaderProgram& shaderProgram);
	void deleteObjects();
	void renderObjects();
private:
	vector<Object*> objects;

};

#endif