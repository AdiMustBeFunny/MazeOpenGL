#include"SpriteRenderer.h"

void SpriteRenderer::InitRenderData()
{
#pragma region 
	GLfloat spriteVertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &spriteVAO);
	glGenBuffers(1, &spriteVBO);

	glBindVertexArray(spriteVAO);
	glBindBuffer(GL_ARRAY_BUFFER, spriteVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(spriteVertices), spriteVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

#pragma endregion Init sprite render data

#pragma region 
	GLfloat surfaceVertices[] = {
		// Pos        // Tex
		-1.0f, -1.0f, 0.0f, 0.0f,
		1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f,

		-1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 0.0f,
		1.0f,  1.0f, 1.0f, 1.0f
	};

	glGenVertexArrays(1, &surfaceVAO);
	glGenBuffers(1, &surfaceVBO);

	glBindVertexArray(surfaceVAO);
	glBindBuffer(GL_ARRAY_BUFFER, surfaceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(surfaceVertices), surfaceVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
#pragma endregion Init surface render data
}

void SpriteRenderer::DrawSprite(Texture2D texture, glm::vec2 position, glm::vec2 size, glm::vec3 color, Shader shader)
{

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(position.x, position.y, 0));
	model = glm::scale(model, glm::vec3(size.x, size.y, 0.0));

	shader.Use();
	shader.setMat4fv("model", model);
	shader.setVec3("color", color);

	glBindVertexArray(spriteVAO);
	texture.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
}

void SpriteRenderer::DrawSurface(Surface& surface, Shader shader)
{
	shader.Use();
	glBindVertexArray(surfaceVAO);
	surface.BindTexture();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
