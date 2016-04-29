#include "Texture.h"
#include <lib\Helper.hpp>

namespace Engine{

	Texture::Texture(const char* source)
	{
		tex = ResourceManager::GetInstance()->LoadResource(source);

		GLAssert();
	}

	void Texture::Init()
	{

	}

	void Texture::Cleanup()
	{

	}

	void Texture::Update(DeltaTime deltaTime)
	{

	}

	void Texture::BindTexture(GLint id)
	{
		//Kokeilen tätä hetken päästä
		//glGenTextures(1, &m_textureObj);
		//glBindTexture(m_textureTarget, m_textureObj);
		//glTexImage2D(m_textureTarget, 0, GL_RGBA, m_pImage->columns(), m_pImage->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());

		//glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//glActiveTexture(TextureUnit);
		//glBindTexture(m_textureTarget, m_textureObj);

		GLAssert();

		GLuint _tex = glGetUniformLocation(id, "tex");

		GLAssert();

		glBindTexture(GL_TEXTURE_2D, _tex);

		GLAssert();

		glActiveTexture(GL_TEXTURE0 + 0);

		GLAssert();

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->iWidth, tex->iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(tex->getImageData()[0]));

		GLAssert();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		GLAssert();

		glBindTexture(GL_TEXTURE_2D, _tex);

		GLAssert();
	}




}