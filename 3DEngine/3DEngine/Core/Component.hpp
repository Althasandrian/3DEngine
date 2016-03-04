#pragma once
#include "..\lib\Helper.hpp"
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <fstream>

namespace Engine {

	// Base Component
	class Component {
	public:
		Component() = default;
		virtual ~Component() = default;
		//virtual std::ofstream& Serialize(std::ofstream& os) = 0; //Onkohan t‰‰ virtual vai ei?
	};

	class Transformable : public Component {
	public:
		Transformable() = default;
		virtual ~Transformable() = default;
		//std::ofstream& Serialize(std::ofstream& os) {}
	};

	class Renderable : public Component {
	public:
		Renderable() = default;
		virtual ~Renderable() = default;

		void Init() {
			_shaderAttribID = 0;

			GLuint VertexArrayID;
			glGenVertexArrays(1, &VertexArrayID);
			glBindVertexArray(VertexArrayID);

			static const GLfloat VertexPositions[] = {
				0.0f, 0.5f, 0.0f,
				-0.5f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				0.0f, 0.0f, 0.5f
			};

			static const GLuint VertexIndex[] = {
				1, 2, 3,
				1, 2, 4,
				2, 3, 4,
				3, 1, 4
			};

			static const GLfloat VertexColor[] = {
				0.0f, 0.5f, 0.0f,
				0.5f, 0.5f, 0.0f,
				0.5f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.5f
			};

			
			glGenBuffers(1, &vertexbuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositions), VertexPositions, GL_STATIC_DRAW);

			glGenBuffers(1, &vertexIndex);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexIndex);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(VertexIndex), VertexIndex, GL_STATIC_DRAW);

			glGenBuffers(1, &colorbuffer);
			glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(VertexColor), VertexColor, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexIndex);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			//glGenBuffers(1, &_vertexBufferObject);

			//glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);

			//glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositions), VertexPositions, GL_STATIC_DRAW);

			//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//glEnableVertexAttribArray(0);

			//glGenBuffers(1, &_colorBuffer);

			//glBindBuffer(GL_ARRAY_BUFFER, _colorBuffer);

			//glBufferData(GL_ARRAY_BUFFER, sizeof(VertexColor), VertexColor, GL_STATIC_DRAW);

			//glBindBuffer(GL_ARRAY_BUFFER, _colorBuffer);

			//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//glEnableVertexAttribArray(1);

			//glGenBuffers(1, &_vertexBufferIndex);

			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vertexBufferIndex);

			//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(VertexIndex) * sizeof(unsigned int), &VertexIndex[0], GL_STATIC_DRAW);

			//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//glEnableVertexAttribArray(2);

			//GLAssert();



			///* Allocate and assign a Vertex Array Object to our handle */
			//glGenVertexArrays(1, &vao);

			///* Bind our Vertex Array Object as the current used object */
			//glBindVertexArray(vao);

			///* Allocate and assign two Vertex Buffer Objects to our handle */
			//glGenBuffers(2, vbo);

			///* Bind our first VBO as being the active buffer and storing vertex attributes (coordinates) */
			//glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

			///* Copy the vertex data from diamond to our buffer */
			///* 8 * sizeof(GLfloat) is the size of the diamond array, since it contains 8 GLfloat values */
			//glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), VertexIndex, GL_STATIC_DRAW);

			///* Specify that our coordinate data is going into attribute index 0, and contains two floats per vertex */
			//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

			///* Enable attribute index 0 as being used */
			//glEnableVertexAttribArray(0);

			///* Bind our second VBO as being the active buffer and storing vertex attributes (colors) */
			//glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

			///* Copy the color data from colors to our buffer */
			///* 12 * sizeof(GLfloat) is the size of the colors array, since it contains 12 GLfloat values */
			//glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), VertexColor, GL_STATIC_DRAW);

			///* Specify that our color data is going into attribute index 1, and contains three floats per vertex */
			//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			///* Enable attribute index 1 as being used */
			//glEnableVertexAttribArray(1);

			//GLAssert();
		}

		void Draw() {
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			//glDrawArrays(GL_TRIANGLES, 0, 3);

			glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)0);

			//glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
		}

	private:
		GLuint vao, vbo[2];
		float VertexPositions[12];
		unsigned int VertexIndex[12];
		char* _vertexData;
		GLuint _shaderAttribID;
		GLuint _vertexBufferObject;
		GLuint _vertexBufferIndex;
		GLuint _colorBuffer;

		GLuint vertexbuffer;
		GLuint colorbuffer;
		GLuint vertexIndex;
		//std::ofstream& Serialize(std::ofstream& os) {}
	};

	class Texture : public Component {
	public:
		Texture() = default;
		virtual ~Texture() = default;
		//std::ofstream& Serialize(std::ofstream& os) {}
	};

	class Colour : public Component {
	public:
		Colour() = default;
		virtual ~Colour() = default;
		//std::ofstream& Serialize(std::ofstream& os) {}
	};

	class Audio : public Component {
	public:
		Audio() = default;
		virtual ~Audio() = default;
		//std::ofstream& Serialize(std::ofstream& os) {}
	};
}