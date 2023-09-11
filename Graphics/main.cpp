#include <iostream>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <STB/stbi.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Source/Shader.h"
#include "Source/Buffer/VAO.h"
#include "Source/Buffer/VBO.h"
#include "Source/Buffer/EBO.h"
#include "Source/Texture.h"
#include "Source/Camera.h"


// Vertices for Object
GLfloat ObjectVertices[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f,

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f,

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f,

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f,

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f,
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f
};

// Indices for Object
GLuint ObjectIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	4, 6, 5,
	7, 9, 8,
	10, 12, 11,
	13, 15, 14
};

// Vertices for Light
GLfloat LightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

// Indices for Light
GLuint LightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

// Dimensions
int WIDTH = 720;
int HEIGHT = 720;

int main(int argc, char const* argv[])
{

	// Initialize GLFW
	if (!glfwInit())
	{
		std::cout << "ERROR::FAILED_TO_INITIALIZE_GLFW" << std::endl;
		return -1;
	}

	// GLFW Properties 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create GLFW Window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Graphics", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "ERROR::FAILED_TO_CREATE_GLFW_WINDOW" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR::FAILED_TO_INITIALIZE_GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, WIDTH, HEIGHT);

	// Initialize Object Shader
	Shader object("Shaders/ObjectVertex.glsl", "Shaders/ObjectFragement.glsl");

	// Initialize Object VAO, VBO, EBO
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(ObjectVertices, sizeof(ObjectVertices));
	EBO EBO1(ObjectIndices, sizeof(ObjectIndices));

	VAO1.Link(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.Link(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Link(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Link(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Initialize Light Shader
	Shader light("Shaders/LightVertex.glsl", "Shaders/LightFragment.glsl");

	// Initialize Light VAO, VBO, EBO
	VAO VAO2;
	VAO2.Bind();

	VBO VBO2(LightVertices, sizeof(LightVertices));
	EBO EBO2(LightIndices, sizeof(LightIndices));

	VAO2.Link(VBO2, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	// Object and Light
	glm::vec4 lightColor(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPosition(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel(1.0f);
	lightModel = glm::translate(lightModel, lightPosition);

	glm::vec3 objectPosition(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel(1.0f);
	objectModel = glm::translate(objectModel, objectPosition);

	light.Activate();
	glUniformMatrix4fv(glGetUniformLocation(light.ID, "Model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(light.ID, "LightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	object.Activate();
	glUniformMatrix4fv(glGetUniformLocation(object.ID, "Model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(object.ID, "LightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(object.ID, "LightPosition"), lightPosition.x, lightPosition.y, lightPosition.z);


	// Initialize Texture
	Texture texture1("Textures/tile.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	texture1.Unit(object, "texture1", 0);

	glEnable(GL_DEPTH_TEST);

	Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		object.Activate();

		camera.Input(window);
		camera.Update(45.0f, 0.1f, 100.0f);
		camera.Matrix(object, "Camera");

		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(ObjectIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		light.Activate();
		camera.Matrix(light, "Camera");
		VAO2.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(LightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}