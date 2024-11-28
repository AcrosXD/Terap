#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>

#include "shader.h"
#include "texture.h"

Texture createTexture(const char* image, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType) {
    char totalFilePath[1024] = "C:\\Users\\rayan\\Terap\\src\\textures\\";
    char filePath[1024];
    strncpy(filePath, totalFilePath, sizeof(filePath) - 1);
    filePath[sizeof(filePath) - 1] = '\0';
    strncat(filePath, image, sizeof(filePath) - strlen(filePath) - 1);

    Texture texture;
    texture.textureType = textureType;
    texture.image = image;
    texture.slot = slot;
    texture.format = format;
    texture.pixelType = pixelType;

    int imageWidth, imageHeight, colorChannelNumber;

    stbi_set_flip_vertically_on_load(1);
    unsigned char* bytes = stbi_load(filePath, &imageWidth, &imageHeight, &colorChannelNumber, 0);

    if (!bytes) {
        printf("Failed to load texture: %s\n", filePath);
    } else {
        printf("Loaded texture: %s\n", filePath);
    }

    glGenTextures(1, &texture.ID);

    glActiveTexture(slot);
    glBindTexture(textureType, texture.ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(textureType, 0, GL_RGBA, imageWidth, imageHeight, 0, format, pixelType, bytes);
    glGenerateMipmap(textureType);

    stbi_image_free(bytes);

    bindTexture(texture);

    printf("Texture created with ID: %d\n", texture.ID);

    return texture;
}

void textureUnit(Shader shader, const char* uniformn, GLuint unit){
    useShader(shader);
    GLuint textureUnit = glGetUniformLocation(shader.ID, uniformn);
    glUniform1i(textureUnit, unit);
}

void bindTexture(Texture texture){
    glActiveTexture(texture.ID);
    glBindTexture(texture.textureType, texture.ID);
}

void unBindTexture(Texture texture){
    glBindTexture(texture.textureType, 0);
}

void deleteTexture(Texture texture){
    glDeleteTextures(1, &texture.ID);
}