
#include "TextureGL.h"
#include "TextureManagerGL.h"

TextureGL::TextureGL() :
    object(nullptr)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindVertexArray(0);
}

TextureGL::~TextureGL()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void TextureGL::prepare()
{
    auto position = object->getDimensions();
    auto vertexSahder = std::string("data/shaders/texture.vert");
    auto fragShader = std::string("data/shaders/texture.frag");
    auto vertices = std::array<float, 16> {
        position.x, position.y, 0, 0,
        position.x, position.w, 0, 1,
        position.z, position.y, 1, 0,
        position.z, position.w, 1, 1
    };

    texture = TextureManagerGL::get()->createTexture(path, setting);
    object->setShaders(vertexSahder.c_str(), fragShader.c_str());

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec4) * 16, &vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

GLvoid TextureGL::setID(GLuint ID)
{
    texture->uniqueID = ID;
}

GLvoid TextureGL::setParameters(ObjectGL * object)
{
    this->object = object;
}

void TextureGL::setTexture(std::string filename, GLenum e)
{
    path = filename;
    setting = e;
}

ObjectGL * TextureGL::getObject()
{
    return object;
}

GLuint TextureGL::getTextureID()
{
    return texture->uniqueID;
}

const std::string& TextureGL::getPath()
{
    return path;
}

GLuint TextureGL::getVAO()
{
    return vao;
}