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


GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
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

	// Initialize Shader
	Shader shader("Shaders/Vertex.glsl", "Shaders/Fragement.glsl");

	// Initialize VAO, VBO, EBO
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.Link(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.Link(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Link(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Inizialize Uniform
	GLuint ScaleUL = glGetUniformLocation(shader.ID, "Scale");
	int ModelUL = glGetUniformLocation(shader.ID, "Model");
	int ViewUL = glGetUniformLocation(shader.ID, "View");
	int ProjectionUL = glGetUniformLocation(shader.ID, "Projection");

	// Initialize Texture
	Texture texture1("Textures/tile.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	texture1.Unit(shader, "texture1", 0);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Activate();

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians((float)glfwGetTime() * 50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

		glUniform1f(ScaleUL, 0.5f);
		glUniformMatrix4fv(ModelUL, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(ViewUL, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(ProjectionUL, 1, GL_FALSE, glm::value_ptr(projection));

		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}