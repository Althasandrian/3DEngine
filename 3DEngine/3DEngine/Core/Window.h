#ifndef Window_h
#define Window_h

#include <Windows.h>
#include <glew.h>
#include <glm\glm.hpp>
#include <gl\GL.h>

/*!< Window style flags*/
#define ENGINE_WINDOWED		0x00000001
#define ENGINE_BORDERLESS	0x00000010
#define ENGINE_FULLSCREEN	0x00000100

class Window
{
public:
	Window();
	~Window();

	int createWindow(LPCWSTR windowName, glm::vec2 size, glm::vec2 position, LPCWSTR icon, LPCWSTR cursor, int style, WNDPROC messageCallback);
	//! A basic function to create a window.
	/*!
	\param[in] windowName A constant character pointer
	\param[in] size A glm::vec2
	\param[in] position A glm::vec2
	\param[in] icon A constant character pointer
	\param[in] cursor A constant character pointer
	\param[in] style An integer
	\param[in] messageCallback A WNDPROC
	\return Returns 1 if it succeeds or -1 if it fails.
	*/

	int InitOpenGL();
	//! A function to create the OpenGL rendering context for the window.
	/*!
	\return Returns 1 if it succeeds or -1 if it fails.
	*/

	int Uninit();
	//! A function to free the OpenGL rendering context and window.

	int getMessage();


	bool IsOpen() { return IsWindow(_windowHandle); }
	//! Checks if the window is still open.
	/*!
	\return Return true if still open, false if closed.
	*/
	
	void SetSize(glm::vec2 newSize);
	//! Change the size of the window.
	/*!
	\param[in] newSize glm::vec2
	*/

	void SetPosition(glm::vec2 newPosition);
	//! Change the position of the window.
	/*!
	\param[in] newPosition glm::vec2
	*/

	//GETTERS
	glm::vec2 GetSize();
	//! Get window size.
	/*!
	\return Returns glm::vec2 with screen size.
	*/

	glm::vec2 GetPosition();
	//! Get window position.
	/*!
	\return Returns glm::vec2 with screens top left corner position.
	*/

	void Resize();

	//Toivottavasti turhia täällä.
	HDC hdc() { return _deviceContextHandle; }
	void confineMouse();
	void releaseMouse();

private:
	HINSTANCE	_instanceHandle;			/*!< A handle to the current instance of the application.*/
	HINSTANCE	_previousInstanceHandle;	/*!< A handle to the previous instance of the application.*/
	LPWSTR		_cmdLine;					/*!< The command line for the application, exluding the program name.*/
	int			_cmdShow;					/*!< Controls how the window is to be shown.*/

	HDC			_deviceContextHandle;		/*!< A handle to device context.*/
	HGLRC		_glRenderingContextHandle;	/*!< A handle to an OpenGL rendering context.*/
	HWND		_windowHandle;				/*!< A handle to window.*/

	MSG			_message;					/*!< Contains message information from a thread's message queue.*/
	WNDCLASSEX	_windowInfo;				/*!< Contains window class information. It is used with the RegisterClassEx and GetClassInfoEx functions.*/

	GLuint		_pixelFormat;				/*!< Contains the pixel format after searching for a match.*/
};
#endif /*End Window_h*/