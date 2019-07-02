#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Shader.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Surface.h"
class SpriteRenderer
{
public:
	void InitRenderData();
	void DrawSprite(Texture2D texture,glm::vec2 position,glm::vec2 size=glm::vec2(10,10),glm::vec3 color = glm::vec3(1.0),Shader shader = ResourceManager::GetShader("spriteDefault"));
	void DrawSurface(Surface& surface, Shader shader = ResourceManager::GetShader("surfaceDefault"));


private:
	unsigned int spriteVAO, spriteVBO;
	unsigned int surfaceVAO,surfaceVBO;

};



#endif // !SPRITERENDERER_H
