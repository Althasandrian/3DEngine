#include "Texture.h"
#include <lib\Helper.hpp>

namespace Engine{

	void Texture::loadImage(const char* imagepath)
	{
		Resource* tex = ResourceManager::GetInstance()->LoadResource(imagepath);
		texWidth = tex->iWidth;
		texHeight = tex->iHeight;
		imgData = tex->getImageData();

	}

	void Texture::textureasd(GLint id, Texture* img)
	{
		GLuint boundTex = 0;
		glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint*)&boundTex);
		GLuint _tex = glGetUniformLocation(id, "tex");
		glBindTexture(GL_TEXTURE_2D, _tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->texWidth, img->texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, &img->imgData[0]);
		glActiveTexture(GL_TEXTURE0 + 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, _tex);

	}




}