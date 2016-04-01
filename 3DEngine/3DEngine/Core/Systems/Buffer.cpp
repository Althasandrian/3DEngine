#include <Core\Systems\Buffer.hpp>
#include <glm\glm.hpp>

namespace Engine {
	void Buffer::CreateBuffer(GLenum bufferType) {
		_bufferType = bufferType;

		switch (_bufferType)
		{
		case GL_ARRAY_BUFFER: {
			glGenBuffers(1, &_bufferID);
			glBindBuffer(_bufferType, _bufferID);
			glBufferData(_bufferType, _bufferSize, NULL, GL_STATIC_DRAW);
			break;
		}
		case GL_ELEMENT_ARRAY_BUFFER: {
			glGenBuffers(1, &_bufferID);
			glBindBuffer(_bufferType, _bufferID);
			glBufferData(_bufferType, _bufferSize, NULL, GL_STATIC_DRAW);
			break;
		}
		default: {
			std::cout << "Unrecognized buffer type!" << std::endl;
			break;
		}
		}
		glGenBuffers(1, &_bufferID);
		glBindBuffer(_bufferType, _bufferID);
	}




	void Buffer::BindBufferData(GLuint size, void* data) {

		switch (_bufferType)
		{
			case GL_ARRAY_BUFFER: {
				glBufferData(_bufferType, sizeof(glm::fvec3) * size, data, GL_STATIC_DRAW);
				break;
			}
			case GL_ELEMENT_ARRAY_BUFFER: {
				glBufferData(_bufferType, sizeof(glm::uvec3) * size, data, GL_STATIC_DRAW);
				break;
			}
			default: {
				printf_s("Unrecognized buffer type!\n");
				break;
			}
		}
	}

	//void Buffer::Resize(GLuint size) {

	//	switch (_bufferType)
	//	{
	//		case GL_ARRAY_BUFFER: {
	//			while (_bufferSize * 6 < size) { _bufferSize *= 2; }
	//			while ((_bufferSize * 6) / 2 > size) { _bufferSize /= 2; }
	//			break;
	//		}
	//		case GL_ELEMENT_ARRAY_BUFFER: {
	//			while (_bufferSize * 6 < size) { _bufferSize *= 2; }
	//			while ((_bufferSize * 3) / 2 > size) { _bufferSize /= 2; }
	//			break;
	//		}
	//		default: {
	//			printf_s("Undefined buffer type!\n");
	//			break;
	//		}
	//	}
	//}
}