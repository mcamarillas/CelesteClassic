
#include "Background.h"
#include <map>

#pragma once
class backgroundManager
{
public:
	void updateBackground(int deltaTime);
	void renderBackground();
	void renderSnow();
	void init(ShaderProgram& shaderProgram);

private:
	map<int, Background*> backgrounds;
	map<int, Background*> snows;
};

