#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<glm\glm.hpp>
#include"Texture.h"
#include"Shader.h"
#include"ResourceManager.h"
#include"SpriteRenderer.h"
class GameObject
{
public:
	GameObject(Texture2D sprite,glm::vec2 pos, glm::vec2 size, glm::vec3 color= glm::vec3(1.0), Shader = ResourceManager::GetShader("spriteDefault"));
	~GameObject();

	virtual void Draw(SpriteRenderer&);

	float Velocity = 0.0f;
	glm::vec2 Position;
	glm::vec2 Size;
	glm::vec3 Color;
	Texture2D Sprite;
	Shader shader;
};

#endif // !GAMEOBJECT_H