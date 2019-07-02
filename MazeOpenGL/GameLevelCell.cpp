#include "GameLevelCell.h"



GameLevelCell::GameLevelCell(glm::vec2 pos,
	glm::vec2 size,
	glm::vec3 color ,
	Texture2D tex,
	Shader shader)
	:GameObject(tex,pos,size,color,shader)
{
}


GameLevelCell::~GameLevelCell()
{
}

