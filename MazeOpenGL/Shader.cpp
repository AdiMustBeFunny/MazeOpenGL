#include "Shader.h"


using namespace std;



Shader::Shader()
{

}


void Shader::setInt(const char* variable, int value, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform1i(glGetUniformLocation(ID, variable), value);
}

void Shader::setVec3(const char* variable, float x, float y, float z, GLboolean useShader )
{
	if (useShader)
		this->Use();
	glUniform3f(glGetUniformLocation(ID, variable), x, y, z);
}

void Shader::setMat4fv(const char* variable,const glm::mat4& matrix, GLboolean useShader )
{
	if (useShader)
		this->Use();
	glUniformMatrix4fv(glGetUniformLocation(ID, variable), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setVec3(const char* variable,const glm::vec3& v, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform3fv(glGetUniformLocation(ID, variable), 1, &v[0]);
}

void Shader::setFloat(const char* variable, float value, GLboolean useShader )
{
	if (useShader)
		this->Use();
	glUniform1f(glGetUniformLocation(ID, variable), value);
}


void Shader::setVec2(const char* variable, const glm::vec2& v, GLboolean useShader )
{
	if (useShader)
		this->Use();
	glUniform2fv(glGetUniformLocation(ID, variable), 1, &v[0]);
	
}

void Shader::setVec4(const char* variable, const glm::vec4& v, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform4fv(glGetUniformLocation(ID, variable), 1, &v[0]);
}


Shader& Shader::Use()
{
	glUseProgram(ID);
	return *this;
}


void  Shader::Compile(const GLchar *vertexSource, const GLchar *fragmentSource ) {

	GLuint sVertex, sFragment;

	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, NULL);
	glCompileShader(sVertex);
	checkCompileErrors(sVertex, "VERTEX");


	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, NULL);
	glCompileShader(sFragment);
	checkCompileErrors(sFragment, "FRAGMENT");

	

	this->ID = glCreateProgram();
	glAttachShader(ID, sVertex);
	glAttachShader(ID, sFragment);

	glLinkProgram(ID);

	checkCompileErrors(ID, "PROGRAM");

	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	
}



void Shader::checkCompileErrors(GLuint object, std::string type)
{

	GLint success;
	GLchar infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(object, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER: Compile-time error: Type: " << type << '\n'
					<< infoLog <<"\n -------------------------------------------"<< std::endl;
			}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{

			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER: Link-time error: Type: " << type << '\n'
				<< infoLog << "\n -------------------------------------------" << std::endl;

		}

	}


}


