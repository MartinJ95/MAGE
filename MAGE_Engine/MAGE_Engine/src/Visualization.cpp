#include "Visualization.h"

Visualization::Visualization(const int screenWidth, const int screenHeight, const std::string windowName)
	: m_screenWidth(screenWidth),
	m_screenHeight(screenHeight),
	m_windowName(windowName),
	m_window(nullptr),
	m_meshes(),
	m_shaderPrograms()
{
	
}

bool Visualization::initialise()
{
	/* Initialize the library GLFW */
	if (!glfwInit())
	{
		return false;
	}
	/* Create a windowed mode window and its OpenGL context */
	m_window = glfwCreateWindow(m_screenWidth, m_screenHeight, m_windowName.c_str(), NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		{
			return false;
		}
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(m_window);
	return true;
}

void Visualization::generateShader(std::string vertexShader, std::string fragmentShader, std::string shaderName)
{
	GLuint shaderProgramID;

	int success;
	char infoLog[512];

	GLuint vertex = compileShader("VERTEX", vertexShader);
	GLuint fragment = compileShader("FRAGMENT", fragmentShader);

	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertex);
	glAttachShader(shaderProgramID, fragment);
	glLinkProgram(shaderProgramID);
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING::FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	m_shaderPrograms.emplace(shaderName, shaderProgramID);
}

bool Visualization::isOpen() const
{
	if (!glfwWindowShouldClose(m_window))
	{
		return true;
	}
	return false;
}

void Visualization::clear()
{
	if (!glfwWindowShouldClose(m_window))
	{
		glClearColor(0.f, 0.25f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		return;
	}
	return;
}

void Visualization::display()
{
	if (!glfwWindowShouldClose(m_window))
	{
		glfwSwapBuffers(m_window);
		return;
	}
	return;
}

Visualization::~Visualization()
{
	for (auto x : m_shaderPrograms)
	{
		glDeleteProgram(x.second);
	}
	glfwTerminate();
}

GLuint Visualization::compileShader(const std::string &shaderType, const std::string &shaderFileName)
{

	std::string shaderCode;
	std::ifstream shaderFile;
	std::stringstream shaderStream;

	shaderFile.open(shaderFileName);
	shaderStream << shaderFile.rdbuf();
	shaderCode = shaderStream.str();

	const char* cShaderCode = shaderCode.c_str();

	unsigned int shader;
	int success;
	char infoLog[512];

	glCreateShader(shader);
	glShaderSource(shader, 1, &cShaderCode, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" + shaderType + "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return shader;
}
