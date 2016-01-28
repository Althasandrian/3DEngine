#include "Renderer.h"

Renderer::Renderer(){}
Renderer::~Renderer(){}

void Renderer::initScene(LPVOID lpParam)
{
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);

	//vertices
	tVer[0] = -0.4f; tVer[1] = 0.1f; tVer[2] = 0.0f;
	tVer[3] = 0.4f; tVer[4] = 0.1f; tVer[5] = 0.0f;
	tVer[6] = 0.0f; tVer[7] = 0.7f; tVer[8] = 0.0f;

	qVer[0] = -0.2f; qVer[1] = -0.1f; qVer[2] = 0.0f;
	qVer[3] = -0.2f; qVer[4] = -0.6f; qVer[5] = 0.0f;
	qVer[6] = 0.2f; qVer[7] = -0.1f; qVer[8] = 0.0f;
	qVer[9] = 0.2f; qVer[10] = -0.6f; qVer[11] = 0.0f;

	glGenBuffers(2, uiVBO);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), tVer, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), qVer, GL_STATIC_DRAW);

}

void renderScene(LPVOID lpParam)
{
	//// Typecast lpParam to COpenGLControl pointer
	//OpenGLControl* oglControl = (OpenGLControl*)lpParam;

	//// We just clear color
	//glClear(GL_COLOR_BUFFER_BIT);

	//glEnableVertexAttribArray(0);
	//// Triangle render
	//glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	//// Quad render using triangle strip
	//glBindBuffer(GL_ARRAY_BUFFER, uiVBO[1]);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//oglControl->swapBuffers();
}