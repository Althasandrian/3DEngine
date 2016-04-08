#ifndef Texture_h
#define Texture_h
#include <glew.h>
#include "Core\ResourceManager.h"

namespace Components
{
	class Texture
	{
	public:
		Texture(){};
		void repeatTexture(std::vector<glm::fvec3, std::allocator<glm::fvec3>> vert);
		void nearTexture();
		void linearTexture();
		GLuint loadImage(const char* imagepath, int texNumber);
		void setTexture(const char* imagepath, int texNumber, std::string texFilter, std::vector<glm::fvec3, std::allocator<glm::fvec3>> vert);


	private:
		GLuint texture;
		GLuint shaderProgramId;
		std::vector<glm::fvec3, std::allocator<glm::fvec3>> vertices;
		std::string texFil;
		GLuint texNum = 0;
		GLuint** textures = new GLuint*[texNum];
	};
}
#endif