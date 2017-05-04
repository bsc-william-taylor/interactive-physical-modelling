
#pragma once

#include "ProgramGL.h"
#include "MatrixGL.h"

class ObjectGL
{
    ProgramGL* shader;
    MatrixGL matrix;

    vec4 position;
    vec2 translation;
    vec4 rotation;
public:
    ObjectGL();
    ~ObjectGL();

    ProgramGL* getShader();
    MatrixGL* getMatrix();

    GLvoid setShaders(const char*, const char*);
    GLvoid setRotation(GLfloat, vec3);
    GLvoid sendMatricesToShader();
    GLvoid setIdentity();
    GLvoid setTranslate(vec2);
    GLvoid setPosition(vec2);
    GLvoid setOrtho2D(vec4);
    GLvoid setScale(vec3);
    GLvoid setSize(vec2);
    GLvoid bindProgram();
    GLvoid endProgram();

    vec4 getDimensions();
    vec2 getTranslate();
    vec2 getPosition();
};