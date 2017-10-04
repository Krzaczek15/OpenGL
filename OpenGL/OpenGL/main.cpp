#include "sb7.h"

class my_app :public sb7::application
{
public:
	GLuint compile_shaders(void)
	{
		GLuint vertexShader;
		GLuint fragmentShader;
		GLuint program;

		static const GLchar *vShaderSource[] =
		{
			"#version 330 core                          \n"
			"                                           \n"
			"void main(void)                            \n"
			"{                                          \n"
			"	gl_Position = vec4(0.0, 0.0, 0.0, 1.0); \n"
			"}                                          \n"
		};

		static const GLchar *fShaderSource[] =
		{
			"#version 330 core                          \n"
			"                                           \n"
			"out vec4 color;                            \n"
			"                                           \n"
			"void main(void)                            \n"
			"{                                          \n"
			"	color = vec4(0.0, 0.8, 1.0, 1.0);       \n"
			"}                                          \n"
		};

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, vShaderSource, NULL);
		glCompileShader(vertexShader);

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, fShaderSource, NULL);
		glCompileShader(fragmentShader);

		program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return program;
	}

	void startup()
	{
		renderingProgram = compile_shaders();
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
	}

	void render(double currentTime)
	{
		static const GLfloat red[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, red);

		glUseProgram(renderingProgram);

		glPointSize((float)(sin(currentTime)*50));

		glDrawArrays(GL_POINTS, 0, 1);
	}

	void shutdown()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteProgram(renderingProgram);
	}
private:
	GLuint renderingProgram;
	GLuint VAO;
};

DECLARE_MAIN(my_app);
 