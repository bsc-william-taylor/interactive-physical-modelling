
#pragma once

#include "HeaderGL.h"

enum ShaderType
{
    VertexShader,
    FragShader,
    EnumLength
};

class ProgramGL
{
    std::string filenames[EnumLength];
    GLuint shaders[EnumLength];
    GLuint program;
public:
    ProgramGL();
    ~ProgramGL();

    GLuint getAttribute(const std::string&);
    GLuint getUniform(const std::string&);

    GLvoid setMatrix(const std::string&, glm::mat4);
    GLvoid setTexture(GLuint);
    GLvoid load(ShaderType, const std::string&);
    GLvoid outputLog(ShaderType);
    GLvoid release();
    GLvoid create();
    GLvoid link();
    GLvoid use();

    const std::string& getFS();
    const std::string& getVS();
private:
    std::string readTextFile(const std::string&);
};