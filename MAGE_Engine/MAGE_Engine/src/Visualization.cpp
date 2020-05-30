#include "Visualization.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Visualization::Visualization(const int screenWidth, const int screenHeight, const std::string &windowName) :
	m_window(nullptr),
	m_screenWidth(screenWidth),
	m_screenHeight(screenHeight),
	m_windowName(windowName),
	m_meshes(),
	m_textures(),
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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	/* Create a windowed mode window and its OpenGL context */
	m_window = glfwCreateWindow(m_screenWidth, m_screenHeight, m_windowName.c_str(), NULL, NULL);
	if (m_window == NULL)
	{
		glfwTerminate();
		{
			return false;
		}
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(m_window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "GLAD failed to initualize" << std::endl;
		return false;
	}
	//glViewport(0, 0, m_screenWidth, m_screenHeight);
	return true;
}

void Visualization::generateShader(const std::string &vertexShader, const std::string &fragmentShader, const std::string &shaderName)
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

void Visualization::generateTexture(const std::string & textureFilePath, const std::string & textureName)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load(textureFilePath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	m_textures.emplace(textureName, texture);
}

void Visualization::useShader(const std::string & shaderName)
{
	if (m_shaderPrograms.find(shaderName) != m_shaderPrograms.end())
	{
		glUseProgram(m_shaderPrograms.find(shaderName)->second);
	}
}

void Visualization::setShaderUniformFloat(const std::string & shaderName, const std::string & uniformName, const float value)
{
	if (m_shaderPrograms.find(shaderName) != m_shaderPrograms.end())
	{
		glUniform1f(glGetUniformLocation(m_shaderPrograms.find(shaderName)->second, uniformName.c_str()), value);
	}
}

void Visualization::setShaderUniformInt(const std::string & shaderName, const std::string & uniformName, const int value)
{
	if (m_shaderPrograms.find(shaderName) != m_shaderPrograms.end())
	{
		glUniform1i(glGetUniformLocation(m_shaderPrograms.find(shaderName)->second, uniformName.c_str()), value);
	}
}

void Visualization::setShaderUniformBool(const std::string & shaderName, const std::string & uniformName, const bool value)
{
	if (m_shaderPrograms.find(shaderName) != m_shaderPrograms.end())
	{
		glUniform1i(glGetUniformLocation(m_shaderPrograms.find(shaderName)->second, uniformName.c_str()), (int)value);
	}
}

void Visualization::setShaderUniformMatrix4f(const std::string & shaderName, const std::string & uniformName, const glm::mat4 &matrix)
{
	if (m_shaderPrograms.find(shaderName) != m_shaderPrograms.end())
	{
		glUniform4fv(glGetUniformLocation(m_shaderPrograms.find(shaderName)->second, uniformName.c_str()), 1, glm::value_ptr(matrix));
	}
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

	GLuint shader{ 0 };
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
