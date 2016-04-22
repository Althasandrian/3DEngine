#ifndef Texture_h
#define Texture_h
#include <glew.h>
#include "Core\ResourceManager.h"

namespace Engine
{
	class Texture
	{
	public:
		Texture(){};

		void textureasd();
		//void nearTexture();
		//void linearTexture();
		void loadImage(const char* imagepath /*int texNumber*/);
		//void setTexture(const char* imagepath);


	private:
		//GLuint tex;

		GLuint shaderProgramId;
		std::vector<glm::fvec3, std::allocator<glm::fvec3>> vertices;
		std::string texFil;
		GLuint texNum = 0;
		GLuint** textures = new GLuint*[texNum];
	};
}
#endif