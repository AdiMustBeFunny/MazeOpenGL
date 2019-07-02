#include "Surface.h"
#include <iostream>


Surface::Surface(int width,int height):Width(width),Height(height)
{

	glGenFramebuffers(1, &MSFBO);
	glGenFramebuffers(1, &FBO);
	glGenRenderbuffers(1, &RBO);

	glBindFramebuffer(GL_FRAMEBUFFER, MSFBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);

	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 8, GL_RGB, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, RBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::Failed to create MSFBO" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	Texture.Generate(width, height, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Texture.Id, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::Failed to create FBO" << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Surface::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, MSFBO);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}
void Surface::UnBind()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, MSFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
	glBlitFramebuffer(0, 0, Width, Height, 0, 0, Width, Height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Surface::BindTexture()
{
	Texture.Bind();
}

Surface::~Surface()
{
}

void Surface::Clear()
{

	glDeleteRenderbuffers(1, &RBO);
	glDeleteFramebuffers(1, &FBO);
	glDeleteFramebuffers(1, &MSFBO);
}