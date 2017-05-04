
#include "ShaderManagerGL.h"
#include "ObjectGL.h"

ObjectGL::ObjectGL() :
    shader(nullptr)
{
}

ObjectGL::~ObjectGL()
{
}

GLvoid ObjectGL::setShaders(const char* vs, const char* fs)
{
    shader = ShaderManagerGL::get()->getShader(vs, fs);
}

vec2 ObjectGL::getPosition()
{
    return vec2(position.x, position.y);
}

GLvoid ObjectGL::sendMatricesToShader()
{
    shader->setMatrix("Projection", matrix.getProjection());
    shader->setMatrix("Model", matrix.getModel());
    shader->setMatrix("View", matrix.getView());
}

GLvoid ObjectGL::setRotation(GLfloat angle, vec3 vec)
{
    rotation.w = angle;
    rotation.x = vec.x;
    rotation.y = vec.y;
    rotation.z = vec.z;

    matrix.rotate(angle, vec);
}

GLvoid ObjectGL::bindProgram()
{
    shader->use();
}

GLvoid ObjectGL::setTranslate(vec2 vec)
{
    translation = vec;
    matrix.translate(vec3(vec, 0.0));
}

GLvoid ObjectGL::endProgram()
{
    shader->release();
}

GLvoid ObjectGL::setPosition(vec2 vec)
{
    position.x = vec.x;
    position.y = vec.y;
}

GLvoid ObjectGL::setSize(vec2 vec)
{
    position.z = position.x + vec.x;
    position.w = position.y + vec.y;
}

GLvoid ObjectGL::setScale(vec3 vec)
{
    matrix.scale(vec);
}

GLvoid ObjectGL::setOrtho2D(vec4 v)
{
    matrix.ortho(vec2(v.x, v.z), vec2(v.y, v.w));
}

GLvoid ObjectGL::setIdentity()
{
    matrix.loadIdenditity();
}

vec4 ObjectGL::getDimensions()
{
    return(position);
}

vec2 ObjectGL::getTranslate()
{
    return(translation);
}

ProgramGL* ObjectGL::getShader()
{
    return shader;
}

MatrixGL* ObjectGL::getMatrix()
{
    return &matrix;
}