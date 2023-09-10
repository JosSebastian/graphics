#ifndef EBO_H
#define EBO_H

#include <GLAD/glad.h>

class EBO
{
public:

    // Properties
    GLuint ID;

    // Constructor
    EBO(GLuint* Indices, GLsizeiptr Size);

    // Destructor
    ~EBO();

    // Methods
    void Bind();
    void Unbind();
};

EBO::EBO(GLuint* Indices, GLsizeiptr Size)
{
    glGenBuffers(1, &this->ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Size, Indices, GL_STATIC_DRAW);
}

EBO::~EBO()
{
    glDeleteBuffers(1, &this->ID);
}

void EBO::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
}

void EBO::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

#endif