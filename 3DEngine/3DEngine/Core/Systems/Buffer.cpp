#include <Core\Systems\Buffer.hpp>

namespace Engine {
	void Buffer::CreateBuffer(GLenum bufferType) {
		_bufferType = bufferType;

		glGenBuffers(1, &_bufferID);
		glBindBuffer(_bufferType, _bufferID);

		switch (_bufferType)
		{
		case GL_ARRAY_BUFFER: {
			glBufferData(_bufferType, _bufferSize * 6, NULL, GL_STATIC_DRAW);
			break;
		}
		case GL_ELEMENT_ARRAY_BUFFER: {
			glBufferData(_bufferType, _bufferSize * 3, NULL, GL_STATIC_DRAW);
			break;
		}
		default: {
			printf_s("Undefined buffer type!\n");
			break;
		}
		}
	}

	void Buffer::BindBufferData(GLuint size, void* data) {
		Resize(size);

		switch (_bufferType)
		{
			case GL_ARRAY_BUFFER: {
				glBufferData(_bufferType, _bufferSize * 6, data, GL_STATIC_DRAW);
				break;
			}
			case GL_ELEMENT_ARRAY_BUFFER: {
				glBufferData(_bufferType, _bufferSize * 3, data, GL_STATIC_DRAW);
				break;
			}
			default: {
				printf_s("Undefined buffer type!\n");
				break;
			}
		}
	}

	void Buffer::Resize(GLuint size) {

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
				printf_s("Undefined buffer type!\n");
				break;
			}
		}
	}
}