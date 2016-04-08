#include "Texture.h"
#include <lib\Helper.hpp>
//0 ja 1 muuttuu tarvittaessa
#define posAttrib 0
#define colAttrib 1
namespace Components{

	void Texture::repeatTexture(std::vector<glm::fvec3, std::allocator<glm::fvec3>> vert)
	{
		//GLuint tex;
		//glGenTextures(1, &tex);
		//glBindTexture(GL_TEXTURE_2D, tex);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		////float color[] = {1.0f, 0.0f, 0.0f, 1.0f};
		////glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
		//
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//glGenerateMipmap(GL_TEXTURE_2D);

		//float pixels[] = {
		//	0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		//	1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
		//};
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);

		//vertices = vert;

		//glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);
		//glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));

		//GLuint texAttrib = glGetAttribLocation(shaderProgramId, "Texcoord");
		//glEnableVertexAttribArray(texAttrib);
		//glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));

	}

	GLuint Texture::loadImage(const char* imagepath, int texNumber)
	{
		textures[texNumber];
		glGenTextures(texNumber, textures[texNumber]);
		int width, height;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *textures[texNumber]);
		Resource* tex = ResourceManager::GetInstance()->LoadResource(imagepath);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->iWidth, tex->iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imagepath);
		glUniform1i(glGetUniformLocation(shaderProgramId, "Texcoord"), texNumber);
		GLAssert();
		return true;
	}

	void Texture::setTexture(const char* imagepath, int texNumber, std::string texFilter, std::vector<glm::fvec3, std::allocator<glm::fvec3>> vert)
	{
		//if (texFilter == "repeat")
		//{
		//	repeatTexture(vert);
		//}
		//loadImage(imagepath, texNumber);
	}



	/////////////////////////////////////////////

	//GLuint Texture::loadImage(const char* imagepath)
	//{
	//	Resource* tex = ResourceManager::GetInstance()->LoadResource(imagepath);
	//	//Resource* tex = RM->LoadResource(imagepath);
	//	//GLAssert();
	//	//width = tex->width;
	//	//height = tex->height;
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex);
	//	//GLAssert();

	//	return true;
	//}

	//void Texture::repeatTexture(const char* imagepath)
	//{
	//	glGenTextures(1, &texture);
	//	glBindTexture(GL_TEXTURE_2D, texture);

	//	loadImage(imagepath);

	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//	glGenerateMipmap(GL_TEXTURE_2D);

		//float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
		//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

		//float pixels[] = {
		//	0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		//	1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
		//};
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);

		//float vertices[] = {
		////  Position      Color             Texcoords
		//	-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
		//	0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
		//	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
		//	-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
		//};

		//glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);
		//glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));

		//GLint texAttrib = glGetAttribLocation(shaderProgramId, "in_TexCoord");
		//glEnableVertexAttribArray(texAttrib);
		//glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
	}

//	void Texture::nearTexture(std::string imagepath)
//	{
//		glGenTextures(1, &texture);
//		glBindTexture(GL_TEXTURE_2D, texture);
//
//		float pixels[] = {
//			0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//			1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
//		};
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		float vertices[] = {
//		//  Position      Color             Texcoords
//			-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
//			0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
//			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
//			-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
//		};
//
//		glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);
//		glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));
//
//		GLint texAttrib = glGetAttribLocation(shaderProgramId, "in_TexCoord");
//		glEnableVertexAttribArray(texAttrib);
//		glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
//	}
//
//	void Texture::linearTexture(std::string imagepath)
//	{
//
//		Resource* tex = ResourceManager::GetInstance()->LoadResource(imagepath);
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 500, 500, 0, GL_RGB, GL_UNSIGNED_BYTE, tex);
//
//		glGenTextures(1, &texture);
//		glBindTexture(GL_TEXTURE_2D, texture);
//		//Resource* texres = ResourceManager*->getInstance()->LoadResource(filepath);
//		//std::vector<unsigned char> pixeldata = tex->getImageData();
//		float pixels[] = {
//			0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//			1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
//		};
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2/*texres->iWidth*/, 2/*texres->iHeight*/, 0, GL_RGB, GL_FLOAT, pixels);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		float vertices[] = {
//		//  Position      Color             Texcoords
//			-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
//			0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
//			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
//			-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
//		};
//
//		glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);
//		glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));
//
//		GLint texAttrib = glGetAttribLocation(shaderProgramId, "in_TexCoord");
//		glEnableVertexAttribArray(texAttrib);
//		glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
//	}
//}