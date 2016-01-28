#ifndef Renderer_H
#define Renderer_H

#include <Windows.h>
#include <glew.h>
#include <glm\glm.hpp>
#include <gl\GL.h>

class Window;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void initScene(LPVOID lpParam);
	void renderScene();


private:
	UINT  uiVBO[2];	// vertex buffer object
	float tVer[9]; // triangle rendering data
	float qVer[12]; // quad Rendering data
};


#endif 