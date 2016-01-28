#ifndef OPENGLCONTROL_H
#define OPENGLCONTROL_H
#define SIMPLE_OPENGL_CLASS_NAME "Simple_openGL_class"
#include <Windows.h>
#include <glew.h>
#include <glm\glm.hpp>
#include <gl\GL.h>

class OpenGLControl
{
public:
	bool InitOpenGL(HINSTANCE hInstance, HWND* a_hWnd, int iMajorVersion, int iMinorVersion, void(*a_InitScene)(LPVOID),
		void(*a_RenderScene)(LPVOID),void(*a_ReleaseScene)(LPVOID), LPVOID lpParam);

	void ResizeOpenGLViewportFull();
	void Render(LPVOID lpParam);
	void releaseOpenGLControl(LPVOID lpParam);

	static void RegisterSimpleOpenGLClass(HINSTANCE hInstance){}
	static void UnregisterSimpleOpenGLClass(HINSTANCE hInstance);

	void MakeCurrent();
	void SwapBuffersM();
	
private:
	
	bool InitGLEW(HINSTANCE hInstance);

	HDC hDC;
	HWND* hWnd;
	HGLRC hRC;
	static bool bClassregistered;
	bool bGlewInitialized = false;
	int iMajorVesion, iMinorVersion;

	void (*InitScene)(LPVOID lpParam), (*RenderScene)(LPVOID lpParam), (*ReleaseScene)(LPVOID lpParam);

};



#endif