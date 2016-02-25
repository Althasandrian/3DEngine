#ifndef Renderer_h
#define Renderer_h

#include "..\Window.h"
#include "..\Component.hpp"
#include "ShaderProgram.h"

#include <vector>

namespace Engine
{
	typedef void(*DrawCallback)(void);

	class Renderer
	{
	public:
		static Renderer* GetInstance() {
			static Renderer instance;
			return &instance;
		};

		void RegisterDraw(DrawCallback draw) { _draw = draw; };
		void Renderende(Window* window);
		void Draw(std::vector<Engine::Renderable*> renderables);
	private:
		Renderer(){};
		~Renderer() {};

		Renderer(Renderer const&);
		void operator=(Renderer const&);

		DrawCallback _draw;

		Window* _window;

		GLSLProgram _GLSLP;
		GLuint _shaderProgram;
		GLuint _vertexShader;
		GLuint _fragmentShader;
	};
}

#endif