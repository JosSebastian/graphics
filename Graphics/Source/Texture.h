#ifndef TEXTURE_H
#define TEXTURE_H

#include <GLAD/glad.h>
#include <STB/stbi.h>

#include <iostream>

#include "Source/Shader.h"

class Texture {
public:

    // Properties
    GLuint ID;
    GLenum Type;
    GLuint Slot;

    // Constructor
    Texture(const char* ImagePath, GLenum Type, GLuint Slot, GLenum Format, GLenum Pixel);

    // Destructor
    ~Texture();

    // Methods
    void Unit(Shader& Shader, const char* Uniform, GLuint Unit);
    void Bind();
    void Unbind();

};

Texture::Texture(const char* ImagePath, GLenum Type, GLuint Slot, GLenum Format, GLenum Pixel) {

    this->Type = Type;

    glGenTextures(1, &this->ID);
    glActiveTexture(GL_TEXTURE0 + Slot);
    this->Slot = Slot;
    glBindTexture(Type, this->ID);

    glTexParameteri(Type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(Type, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(Type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(Type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int Width, Height, Channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* Data = stbi_load(ImagePath, &Width, &Height, &Channels, 0);
    if (Data)
    {
        glTexImage2D(Type, 0, Format, Width, Height, 0, Format, Pixel, Data);
        glGenerateMipmap(Type);
    }
    else
    {
        std::cout << "ERROR::TEXTURE::FAILED_TO_LOAD_IMAGE" << std::endl;
    }
    stbi_image_free(Data);

}

Texture::~Texture() {

    glDeleteTextures(1, &this->ID);

}

void Texture::Unit(Shader& Shader, const char* Uniform, GLuint Unit) {

    GLuint TextureID = glGetUniformLocation(Shader.ID, Uniform);
    Shader.Activate();
    glUniform1i(TextureID, Unit);

}

void Texture::Bind() {

    glActiveTexture(GL_TEXTURE0 + Slot);
    glBindTexture(this->Type, this->ID);

}

void Texture::Unbind() {

    glBindTexture(this->Type, 0);

}

#endif