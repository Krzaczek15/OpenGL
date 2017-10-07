#include "sb7.h"

class my_app :public sb7::application
{
public:
	GLuint compile_shaders(void)
	{
		GLuint vertexShader;
		GLuint fragmentShader;
		GLuint tcsShader;
		GLuint tesShader;
		GLuint program;

		static const GLchar *vShaderSource[] =
		{
			"#version 410 core                                                 \n"
			"                                                                  \n"
			"void main(void)                                                   \n"
			"{                                                                 \n"
			"    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),  \n"
			"                                   vec4(-0.25, -0.25, 0.5, 1.0),  \n"
			"                                   vec4( 0.25,  0.25, 0.5, 1.0)); \n"
			"                                                                  \n"
			"    gl_Position = vertices[gl_VertexID];                  \n"
			"}																   \n"
		};

		static const GLchar *fShaderSource[] =
		{
			"#version 410 core                          \n"
			"                                           \n"
			"out vec4 color;                            \n"
			"                                           \n"
			"void main(void)                            \n"
			"{                                          \n"
			"	color = vec4(0.0, 0.8, 1.0, 1.0);                    \n"
			"}                                          \n"
		};
		static const GLchar *tcsShaderSource[] =
		{
			"#version 410 core                                                                 \n"
			"                                                                                  \n"
			"layout (vertices = 3) out;                                                        \n"
			"                                                                                  \n"
			"void main(void)                                                                   \n"
			"{                                                                                 \n"
			"    if (gl_InvocationID == 0)                                                     \n"
			"    {                                                                             \n"
			"        gl_TessLevelInner[0] = 5.0;                                               \n"
			"        gl_TessLevelOuter[0] = 5.0;                                               \n"
			"        gl_TessLevelOuter[1] = 5.0;                                               \n"
			"        gl_TessLevelOuter[2] = 5.0;                                               \n"
			"    }                                                                             \n"
			"    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;     \n"
			"}														\n"
		};

		static const GLchar *tesShaderSource[] = {
			"#version 410 core                                                                 \n"
			"                                                                                  \n"
			"layout (triangles, equal_spacing, cw) in;                                         \n"
			"                                                                                  \n"
			"void main(void)                                                                   \n"
			"{                                                                                 \n"
			"    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +                       \n"
			"                  (gl_TessCoord.y * gl_in[1].gl_Position) +                       \n"
			"                  (gl_TessCoord.z * gl_in[2].gl_Position);                        \n"
			"}                                                          \n"
		};

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, vShaderSource, NULL);
		glCompileShader(vertexShader);

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, fShaderSource, NULL);
		glCompileShader(fragmentShader);
		
		tcsShader = glCreateShader(GL_TESS_CONTROL_SHADER);
		glShaderSource(tcsShader, 1, tcsShaderSource, NULL);
		glCompileShader(tcsShader);

		tesShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
		glShaderSource(tesShader, 1, tesShaderSource, NULL);
		glCompileShader(tesShader);

		program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, tcsShader);
		glAttachShader(program, tesShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return program;
	}

	void startup()
	{
		renderingProgram = compile_shaders();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
	}

	void render(double currentTime)
	{
		static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, green);

		glUseProgram(renderingProgram);

		glDrawArrays(GL_PATCHES, 0, 3);
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
 