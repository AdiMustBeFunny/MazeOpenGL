#pragma once
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include<map>
#include<string>

#include<glad\glad.h>

#include"Texture.h"
#include"Shader.h"
#include"Surface.h"

#include "stb_image.h"


class ResourceManager {
public:

	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture2D> Textures;
	static std::map<std::string, Surface> Surfaces;
	
	static Shader LoadShader(const GLchar* vs,const GLchar* fs, std::string name);
	static Shader GetShader(std::string name);

	static Texture2D LoadTexture(const GLchar* file,std::string name);
	static Texture2D GetTexture(std::string name);

	static Surface CreateSurface(int Width, int Height, std::string name);
	static Surface GetSurface(std::string name);

	static void Clear();
private:
	ResourceManager();

	static Shader loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile);
	static Texture2D loadTextureFromFile(const GLchar *file);
};



#endif // !RESOURCEMANAGER_H


