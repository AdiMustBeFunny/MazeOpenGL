#ifndef  SHADER_H
#define SHADER_H

#include<glad\glad.h>

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include<glm\gtc\type_ptr.hpp>
#include<glm\glm.hpp>

#define GET_VARIABLE_NAME(name) #name

class Shader
{
	
	
	

public:
	unsigned int ID;
	//Shader(const char* vertex_source, const char* fragment_source);
	Shader();
	void    Compile(const GLchar *vertexSource, const GLchar *fragmentSource);


	void setInt(const char* variable, int value,GLboolean useShader=false);
	void setFloat(const char* variable, float value, GLboolean useShader = false);
	void setVec3(const char* variable, float x, float y, float z, GLboolean useShader = false);
	void setVec3(const char* variable, const glm::vec3& v, GLboolean useShader = false);
	void setVec4(const char* variable, const glm::vec4& v, GLboolean useShader = false);
	void setVec2(const char* variable, const glm::vec2& v, GLboolean useShader = false);
	void setMat4fv(const char* variable, const glm::mat4& matrix, GLboolean useShader = false);
	Shader& Use();


private:
	void checkCompileErrors(GLuint object, std::string type);
};




#endif // ! SHADER_H

