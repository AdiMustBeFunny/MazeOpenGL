#pragma once

#ifndef SURFACE_H
#define SURFACE_H

#include<glad\glad.h>
#include"Texture.h"
class Surface
{
public:
	Surface(int width, int height);
	Surface(){}
	~Surface();
	void Clear();


	void Bind();
	void UnBind();
	void BindTexture();
	int Width, Height;
private:
	unsigned int MSFBO, FBO, RBO;
	Texture2D Texture;
};

#endif