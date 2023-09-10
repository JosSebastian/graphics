#ifndef SHADER_H
#define SHADER_H

#include <GLAD/glad.h>

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

class Shader
{

public:

    // Properties
    GLuint ID;

    // Constructor
    Shader(const GLchar* VertexShaderPath, const GLchar* FragmentShaderPath);

    // Destructor
    ~Shader();

    // Methods
    void Activate();

};

Shader::Shader(const GLchar* VertexShaderPath, const GLchar* FragmentShaderPath) {

    std::ifstream VertexShaderFile, FragmentShaderFile;
    VertexShaderFile.exceptions(std::ifstream::badbit);
    FragmentShaderFile.exceptions(std::ifstream::badbit);

    std::string VertexShaderCode, FragmentShaderCode;

    try
    {
        VertexShaderFile.open(VertexShaderPath);
        FragmentShaderFile.open(FragmentShaderPath);

        std::stringstream VertexShaderStream, FragmentShaderStream;
        VertexShaderStream << VertexShaderFile.rdbuf();
        FragmentShaderStream << FragmentShaderFile.rdbuf();

        VertexShaderFile.close();
        FragmentShaderFile.close();

        VertexShaderCode = VertexShaderStream.str();
        FragmentShaderCode = FragmentShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FAILED_TO_READ_SHADER_FILES" << std::endl;
        std::cout << e.what() << std::endl;
    }

    const GLchar* VertexShaderSource = VertexShaderCode.c_str();
    const GLchar* FragmentShaderSource = FragmentShaderCode.c_str();

    // Create Shaders
    GLuint VertexShader, FragmentShader;
    GLint Success;
    GLchar InfoLog[512];

    // Vertex Shader
    VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShader, 1, &VertexShaderSource, NULL);
    glCompileShader(VertexShader);
    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Success);
    if (!Success)
    {
        glGetShaderInfoLog(VertexShader, 512, NULL, InfoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << InfoLog << std::endl;
    };

    // Fragment Shader
    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &FragmentShaderSource, NULL);
    glCompileShader(FragmentShader);
    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &Success);
    if (!Success)
    {
        glGetShaderInfoLog(FragmentShader, 512, NULL, InfoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << InfoLog << std::endl;
    };

    // Shader Program
    this->ID = glCreateProgram();
    glAttachShader(this->ID, VertexShader);
    glAttachShader(this->ID, FragmentShader);

    glLinkProgram(this->ID);
    glGetProgramiv(this->ID, GL_LINK_STATUS, &Success);
    if (!Success)
    {
        glGetProgramInfoLog(this->ID, 512, NULL, InfoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << InfoLog << std::endl;
    };

    // Delete Shaders
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);

}

Shader::~Shader() {
    glDeleteProgram(this->ID);
}

void Shader::Activate() {
    glUseProgram(this->ID);
}


#endif