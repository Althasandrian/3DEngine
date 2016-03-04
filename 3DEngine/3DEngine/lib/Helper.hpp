#ifndef Helper_h
#define Helper_h

#include <iostream>
#include <string>

#define GLAssert() Engine::AssertGLError(__FILE__, __LINE__);

namespace Engine {

	inline wchar_t* GetLCWSTR(const char* lpcstr) {
		unsigned size = strlen(lpcstr) + 1; // +1 to include NULL
		wchar_t* wc = new wchar_t[size];
		unsigned outSize;
		mbstowcs_s(&outSize, wc, size, lpcstr, size - 1);
		return wc;
	}

	inline void AssertGLError(const char* file, const unsigned int line) {
		const GLenum error = glGetError();

		if (error != GL_NO_ERROR) {
			std::cout << "OpenGL error at " << file << " line " << line << " error " << error << std::endl;
			std::abort();
		}
	}
};

#endif