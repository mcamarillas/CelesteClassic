
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
	void setCloudColor(string s);
	void createParticles(string s,glm::vec2 pos, ShaderProgram& shaderProgram);
	void renderParticles();

private:
	ShaderProgram shader;
	map<int, Background*> backgrounds;
	map<int, Background*> snows;
	map<int, Background*> particles;
};


