#include "Visualization.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Camera.h"
#include "Entity.h"

Visualization::Visualization(const int screenWidth, const int screenHeight, const std::string &windowName) :
	m_screenWidth(screenWidth),
	m_screenHeight(screenHeight),
	m_window(nullptr),
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
	glfwSetFramebufferSizeCallback(m_window, frameBufferSizeCallback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "GLAD failed to initualize" << std::endl;
		return false;
	}
	glViewport(0, 0, m_screenWidth, m_screenHeight);
	glEnable(GL_DEPTH_TEST);
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

GLFWwindow * Visualization::getWindow() const
{
	if (m_window != nullptr)
	{
		return m_window;
	}
	return nullptr;
}

void Visualization::clear()
{
	if (!glfwWindowShouldClose(m_window))
	{
		glClearColor(0.f, 0.25f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		return;
	}
	return;
}

void Visualization::render2D(const std::string & meshName, const std::string & textureName, const std::string & shaderName, const glm::mat4 transformMatrix)
{
	useShader(shaderName);
	setShaderUniformMatrix4f(shaderName, "model_xform", transformMatrix);
	setShaderTexture("Texture", textureName, shaderName, 1);
	m_meshes.find(meshName)->second->render();
}

void Visualization::render3D(const std::string & meshName, const std::string & textureName, const std::string & shaderName, const glm::mat4 transformMatrix, Camera & camera, Vector3f &worldUp)
{
	useShader(shaderName);
	setShaderUniformMatrix4f(shaderName, "model_xform", transformMatrix);
	glm::mat4 projection = glm::perspective(glm::radians(camera.m_fieldOfView), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 100.0f);
	setShaderUniformMatrix4f(shaderName, "projection", projection);
	Vector3f cameraPosition(camera.m_entity.getComponent<Transform>()->worldPosition());
	Vector3f cameraDirection(camera.m_entity.getComponent<Transform>()->worldForward());
	glm::vec3 camPos(cameraPosition.x, cameraPosition.y, cameraPosition.z);
	glm::vec3 camDir(cameraDirection.x, cameraDirection.y, cameraDirection.z);
	glm::vec3 up(worldUp.x, worldUp.y, worldUp.z);
	glm::mat4 view = glm::lookAt(camPos, camPos + camDir, up);
	setShaderUniformMatrix4f(shaderName, "view", view);
	setShaderTexture("Texture", textureName, shaderName, 1);
	m_meshes.find(meshName)->second->render();
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
	stbi_set_flip_vertically_on_load(true);
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

void Visualization::generateFace(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, const Vector3f & minSize, const Vector3f & maxSize, const Vector2f & minTexcoord, const Vector2f & maxTexcoord, const Vector3f & normal, const int & offset)
{
	unsigned int newIndices[]{ 0, 1, 2, 2, 1, 3 };

	for (auto i : newIndices)
	{
		indices.emplace_back(i + offset);
	}

	for (int i = 0; i < 4; i++)
	{
		vertices.emplace_back(Vertex());
		if (minSize.x != maxSize.x)
		{
			vertices[i + offset].position = Vector3f(
				(i % 2 == 0) ? minSize.x : maxSize.x,
				(i < 2) ? minSize.y : maxSize.y,
				(i < 2) ? minSize.z : maxSize.z);
		}
		else
		{
			vertices[i + offset].position = Vector3f(
				minSize.x,
				(i < 2) ? minSize.y : maxSize.y,
				(i % 2 == 0) ? minSize.z : maxSize.z);
		}

		vertices[i + offset].normal = normal;
		vertices[i + offset].color = Vector3f(0, 0, 0);

		vertices[i + offset].texCoords = Vector2f(
			(i % 2 == 0) ? minTexcoord.x : maxTexcoord.x,
			(i < 2) ? minTexcoord.y : maxTexcoord.y);
	}
	/*for (int i = 0; i < 4; i++)
	{
		vertices.emplace_back(Vertex());
		vertices[i].position = Vector3f(0, 0, 0);
		vertices[i].position.x = (i % 2 == 0) ? minSize : maxSize;
		vertices[i].position.y = (i < 2) ? minSize : maxSize;

		vertices[i].color = Vector3f(0, 0, 0);

		vertices[i].normal = Vector3f(0, 0, 1);

		vertices[i].texCoords = Vector2f(0, 0);
		vertices[i].texCoords.x = (i % 2 == 0) ? minTexCoord : maxTexCoord;
		vertices[i].texCoords.y = (i < 2) ? minTexCoord : maxTexCoord;
	}*/
}

void Visualization::generateMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::string & meshName)
{
	MeshGL *newMesh = new MeshGL(vertices, indices);
	newMesh->initualize();
	//std::pair<std::string, MeshGL> meshPair;
	//meshPair.first = meshName;
	//meshPair.second = MeshGL(vertices, indices);
	m_meshes.emplace(meshName, newMesh);
}

void Visualization::generateSquareMesh(const int & minSize, const int & maxSize, const int & minTexCoord, const int & maxTexCoord, const std::string & meshName)
{

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	generateFace(vertices, indices, Vector3f(minSize, minSize, 0), Vector3f(maxSize, maxSize, 0), Vector2f(minTexCoord, minTexCoord), Vector2f(maxTexCoord, maxTexCoord), Vector3f(0, 0, 1), 0);

	generateMesh(vertices, indices, meshName);
}

void Visualization::generateBoxMesh(const int & minSize, const int & maxSize, const int & minTexCoord, const int & maxTexCoord, const std::string & meshName)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	//back
	generateFace(vertices, indices,
		Vector3f(minSize, minSize, minSize), Vector3f(maxSize, maxSize, minSize),
		Vector2f(minTexCoord, minTexCoord), Vector2f(maxTexCoord, maxTexCoord),
		Vector3f(0, 0, -1), 0);
	//front
	generateFace(vertices, indices,
		Vector3f(minSize, minSize, maxSize), Vector3f(maxSize, maxSize, maxSize),
		Vector2f(minTexCoord, minTexCoord), Vector2f(maxTexCoord, maxTexCoord),
		Vector3f(0, 0, 1), 4);
	//top
	generateFace(vertices, indices,
		Vector3f(minSize, maxSize, minSize), Vector3f(maxSize, maxSize, maxSize),
		Vector2f(minTexCoord, minTexCoord), Vector2f(maxTexCoord, maxTexCoord),
		Vector3f(0, 1, 0), 8);
	//bottom
	generateFace(vertices, indices,
		Vector3f(minSize, minSize, minSize), Vector3f(maxSize, minSize, maxSize),
		Vector2f(minTexCoord, minTexCoord), Vector2f(maxTexCoord, maxTexCoord),
		Vector3f(0, -1, 0), 12);
	//left
	generateFace(vertices, indices,
		Vector3f(minSize, minSize, minSize), Vector3f(minSize, maxSize, maxSize),
		Vector2f(minTexCoord, minTexCoord), Vector2f(maxTexCoord, maxTexCoord),
		Vector3f(-1, 0, 0), 16);
	//right
	generateFace(vertices, indices,
		Vector3f(maxSize, minSize, minSize), Vector3f(maxSize, maxSize, maxSize),
		Vector2f(minTexCoord, minTexCoord),	Vector2f(maxTexCoord, maxTexCoord),
		Vector3f(1, 0, 0), 20);

	generateMesh(vertices, indices, meshName);
}

void Visualization::useShader(const std::string & shaderName)
{
	if (m_shaderPrograms.find(shaderName) != m_shaderPrograms.end())
	{
		glUseProgram(m_shaderPrograms.find(shaderName)->second);
	}
}

void Visualization::setShaderTexture(const std::string &textureUniform, const std::string & textureName, const std::string & shaderName, const int textureIndex)
{
	if (m_textures.find(textureName) != m_textures.end()
		&& m_shaderPrograms.find(shaderName) != m_shaderPrograms.end())
	{
		glActiveTexture(GL_TEXTURE0 + textureIndex);
		glBindTexture(GL_TEXTURE_2D, m_textures.find(textureName)->second);
		setShaderUniformInt(shaderName, textureUniform, 1);
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
		if (glGetUniformLocation(m_shaderPrograms.find(shaderName)->second, uniformName.c_str()) == -1)
		{
			std::cout << "error finding uniform location" << std::endl;
		}
		glUniformMatrix4fv(glGetUniformLocation(m_shaderPrograms.find(shaderName)->second, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}
}

Visualization::~Visualization()
{
	for (auto i : m_shaderPrograms)
	{
		glDeleteProgram(i.second);
	}
	for (auto i : m_meshes)
	{
		delete i.second;
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
	shaderFile.close();
	shaderCode = shaderStream.str();

	const char* cShaderCode = shaderCode.c_str();

	GLuint shader{ 0 };
	int success;
	char infoLog[512];
	if (shaderType == "VERTEX")
	{
		shader = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (shaderType == "FRAGMENT")
	{
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	}
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

void frameBufferSizeCallback(GLFWwindow * window, int screenWidth, int screenHeight)
{
	glViewport(0, 0, screenWidth, screenHeight);
}
