#include "GameObject.h"



GameObject::GameObject(Texture2D texture, glm::vec2 position, glm::vec2 size, glm::vec3 color, Shader s)
	:Color(color),Size(size),Position(position),Sprite(texture),shader(s)
{

}


GameObject::~GameObject()
{
}


void GameObject::Draw(SpriteRenderer& Renderer)
{
	Renderer.DrawSprite(Sprite, Position, Size, Color, shader);
}

