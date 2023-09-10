#ifndef VAO_H
#define VAO_H

#include <GLAD/glad.h>

#include "VBO.h"

class VAO
{
public:

    // Properties
    GLuint ID;

    // Constructor
    VAO();

    // Destructor
    ~VAO();

    // Methods
    void Link(VBO& VBO, GLuint Layout, GLuint Components, GLenum Type, GLsizeiptr Stride, void* Offset);
    void Bind();
    void Unbind();

};

VAO::VAO()
{
    glGenVertexArrays(1, &this->ID);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &this->ID);
}

void VAO::Link(VBO& VBO, GLuint Layout, GLuint Components, GLenum Type, GLsizeiptr Stride, void* Offset)
{
    VBO.Bind();
    glVertexAttribPointer(Layout, Components, Type, GL_FALSE, Stride, Offset);
    glEnableVertexAttribArray(Layout);
    VBO.Unbind();
}

void VAO::Bind()
{
    glBindVertexArray(this->ID);
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}

#endif