#pragma once

namespace Engine {

	// Base Component
	class Component {
	public:
		Component() = default;
		virtual ~Component() = default;
		//virtual std::ofstream& Serialize(std::ofstream& os) = 0; //Onkohan t‰‰ virtual vai ei?
	};

	class Renderable : public Component {
	public:
		Renderable() = default;
		virtual ~Renderable() = default;

		void Init() {
			_shaderAttribID = 0;

			float VertexPositions[] = {
				0.0f, 1.0f, 0.0f,
				-1.0f, -1.0f, 0.0f,
				1.0f, -1.0f, 0.0f };

			glGenBuffers(1, &_vbo);

			glBindBuffer(GL_ARRAY_BUFFER, _vbo);

			glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositions), VertexPositions, GL_STATIC_DRAW);

			glVertexAttribPointer(_shaderAttribID, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glEnableVertexAttribArray(_shaderAttribID);
		}

		void Draw() {
			glEnableVertexAttribArray(_shaderAttribID);

			glBindBuffer(GL_ARRAY_BUFFER, _vbo);

			glDrawArrays(GL_TRIANGLES, 0, (sizeof(VertexPositions) / 3) / sizeof(GLfloat));
		}

	private:
		float VertexPositions[9];
		char* _vertexData;
		GLuint _shaderAttribID;
		GLuint _vbo;
		//std::ofstream& Serialize(std::ofstream& os) {}
	};

	class Transformable : public Component {
	public:
		Transformable() = default;
		virtual ~Transformable() = default;
		//std::ofstream& Serialize(std::ofstream& os) {}
	};
}