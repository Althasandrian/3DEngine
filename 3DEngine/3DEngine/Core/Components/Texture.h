#ifndef Texture_h
#define Texture_h
#include <glew.h>
#include "Core\ResourceManager.h"

namespace Engine
{
	class Texture
	{
	public:
		Texture() {};

		void textureasd(GLint id, Texture* img);
		//void nearTexture();
		//void linearTexture();
		void loadImage(const char* imagepath);
		//void setTexture(const char* imagepath);


	private:
		//GLuint tex;

		GLuint shaderProgramId;
		GLint difMapLoc;
		float texWidth;
		float texHeight;
		std::vector<unsigned char> imgData;
		//td::vector<glm::fvec3, std::allocator<glm::fvec3>> vertices;
		//std::string texFil;
		//GLuint texNum = 0;
		//GLuint** textures = new GLuint*[texNum];
	};
}
#endif