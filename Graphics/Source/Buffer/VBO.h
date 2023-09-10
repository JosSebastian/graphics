#ifndef VBO_H
#define VBO_H

#include <GLAD/glad.h>

class VBO
{
public:

    // Properties
    GLuint ID;

    // Constructor
    VBO(GLfloat* Vertices, GLsizeiptr Size);

    // Destructor
    ~VBO();

    // Methods
    void Bind();
    void Unbind();

};

VBO::VBO(GLfloat* Vertices, GLsizeiptr Size)
{
    glGenBuffers(1, &this->ID);
    glBindBuffer(GL_ARRAY_BUFFER, this->ID);
    glBufferData(GL_ARRAY_BUFFER, Size, Vertices, GL_STATIC_DRAW);
}

VBO::~VBO()
{
    glDeleteBuffers(1, &this->ID);
}

void VBO::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->ID);
}

void VBO::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

#endif