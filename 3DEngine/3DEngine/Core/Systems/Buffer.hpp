#ifndef Engine_Buffer_hpp
#define Engine_Buffer_hpp

#include <iostream>
#include <glew.h>

namespace Engine
{
	class Buffer
	{
	public:
		Buffer() : _bufferID(0), _bufferSize(10), _bufferType(GL_NONE) {};
		~Buffer() {};

		void CreateBuffer(GLenum bufferType);
		void BindBufferData(GLuint size, void* data);


	private:
		void Resize(GLuint size);

		GLuint _bufferID;
		GLuint _bufferSize;
		GLenum _bufferType;
	};

	inline void Buffer::CreateBuffer(GLenum bufferType) {
		_bufferType = bufferType;
		
		glGenBuffers(1, &_bufferID);
		glBindBuffer(_bufferType, _bufferID);
		switch (_bufferType)
		{
		case GL_ARRAY_BUFFER: {
			glBufferData(_bufferType, _bufferSize * 6 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
			break;
		}
		case GL_ELEMENT_ARRAY_BUFFER: {
			glBufferData(_bufferType, _bufferSize * 3 * sizeof(GLuint), NULL, GL_STATIC_DRAW);
			break;
		}
		default: {
			std::cout << "Unknown buffer type, shame on you!" << std::endl;
			break;
		}
		}
	}

	inline void Buffer::BindBufferData(GLuint size, void* data) {
		Resize(size);

		glBufferData(_bufferType, _bufferSize, data, GL_STATIC_DRAW);
	}

	inline void Buffer::Resize(GLuint size) {
	
		switch (_bufferType)
		{
		case GL_ARRAY_BUFFER: {
			while (_bufferSize * 6 < size) { _bufferSize *= 2; }
			while ((_bufferSize * 6) / 2 > size) { _bufferSize /= 2; }
			break;
		}
		case GL_ELEMENT_ARRAY_BUFFER: {
			while (_bufferSize * 6 < size) { _bufferSize *= 2; }
			while ((_bufferSize * 3) / 2 > size) { _bufferSize /= 2; }
			break;
		}
		default: {
			std::cout << "Undefined buffer type!\n";
			break;
		}
		}
	}

}

#endif