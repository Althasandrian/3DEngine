#ifndef Helper_h
#define Helper_h

#include <iostream>
#include <string>

namespace Engine {

	inline wchar_t* GetLCWSTR(const char* lpcstr) {
		unsigned size = strlen(lpcstr) + 1; // +1 to include NULL
		wchar_t* wc = new wchar_t[size];
		unsigned outSize;
		mbstowcs_s(&outSize, wc, size, lpcstr, size - 1);
		return wc;
	}

};

#endif