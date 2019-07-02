#include"ResourceManager.h"


std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Texture2D> ResourceManager::Textures;
std::map<std::string, Surface> ResourceManager::Surfaces;

 Shader ResourceManager::LoadShader(const GLchar* vs, const GLchar* fs, std::string name)
{
	 Shaders[name] = loadShaderFromFile(vs, fs);
	 return Shaders[name];
}

 Shader ResourceManager::GetShader(std::string name)
 {
	 return Shaders[name];
 }

 Texture2D ResourceManager::LoadTexture(const GLchar* file, std::string name)
 {
	 Textures[name] = loadTextureFromFile(file);
	 return Textures[name];
 }

 Texture2D ResourceManager::GetTexture(std::string name)
 {
	 return Textures[name];
 }


 Surface ResourceManager::CreateSurface(int Width, int Height, std::string name)
 {
	 Surfaces[name] = Surface(Width, Height);
	 return Surfaces[name];
 }
 Surface ResourceManager::GetSurface(std::string name)
 {
	 return Surfaces[name];
 }



 void ResourceManager::Clear()
 {

	 for (auto iter : Shaders)
	 {
		 glDeleteProgram(iter.second.ID);
	 }

	 for (auto iter : Textures)
	 {
		 glDeleteTextures(1,&iter.second.Id);
	 }

	 for (auto iter : Surfaces)
	 {
		 iter.second.Clear();
	 }

 }


 Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile )
 {

	 std::string vertexCode;
	 std::string fragmentCode;
	

	 try
	 {
		 std::ifstream vertexShaderFile(vShaderFile);
		 std::ifstream fragmentShaderFile(fShaderFile);

		 std::stringstream vShaderStream, fShaderStream;

		 vShaderStream << vertexShaderFile.rdbuf();
		 fShaderStream << fragmentShaderFile.rdbuf();

		 vertexShaderFile.close();
		 fragmentShaderFile.close();

		 vertexCode = vShaderStream.str();
		 fragmentCode = fShaderStream.str();

		
	 }
	 catch (std::exception e)
	 {
		 std::cout <<"ERROR::SHADER::Failed to load shader file(s) :: "<< e.what() << std::endl;
	 }

	 const GLchar *vShaderCode = vertexCode.c_str();
	 const GLchar *fShaderCode = fragmentCode.c_str();
	 


	 Shader shader;
	 
	 shader.Compile(vShaderCode, fShaderCode);

	 return shader;
 }


 Texture2D ResourceManager::loadTextureFromFile(const GLchar *file)
 {
	 Texture2D texture;



	 int width, height,channels;

	 unsigned char* data = stbi_load(file, &width, &height, &channels, 0);
	// std::cout << channels << std::endl;

	 if(channels==4)
	 {
		 texture.Image_Format = GL_RGBA;
		 texture.Internal_Format = GL_RGBA;
	 }
	 else if (channels == 3)
	 {
		 texture.Image_Format = GL_RGB;
		 texture.Internal_Format = GL_RGB;
	 }

	
	 texture.Generate(width, height, data);



	 stbi_image_free(data);

	 return texture;
 }