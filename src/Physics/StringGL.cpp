
#include "StringGL.h"

StringGL::StringGL(std::string fontname, std::string texture)
    : object(nullptr)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindVertexArray(0);

    setColour(0, 0, 0, 1);
    prepareFont(fontname, texture);
}

StringGL::~StringGL()
{
    if (vbo != 0 && vao != 0)
    {
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }
}

void StringGL::prepareFont(std::string fontname, std::string texture)
{
    if (!fontname.empty() && !texture.empty())
    {
        this->fontname = fontname;

        document = new tinyxml2::XMLDocument();
        document->LoadFile(fontname.c_str());       
        sprite = TextureManagerGL::get()->createTexture(texture, GL_CLAMP_TO_EDGE);
    }
}

GLvoid StringGL::setParameters(ObjectGL * object)
{
    this->object = object;
}

GLvoid StringGL::prepare()
{
    GLchar * vs = "data/shaders/text.vert";
    GLchar * fs = "data/shaders/text.frag";

    object->setShaders(vs, fs);
}

void StringGL::setString(std::string text, int spacing)
{
    if (!text.empty())
    {
        vec2 position = object->getPosition();

        std::vector<vec4> positions;
        positions.reserve(text.size() * 4);
        height = 0;
        width = 0;

        tinyxml2::XMLElement * start = document->FirstChildElement("fontMetrics")->FirstChildElement("character");

        for (auto i = 0u; i < text.size(); i++)
        {
            tinyxml2::XMLElement * element = start;

            for (auto b = 0; b < (int)text[i] - 32; b++)
            {
                element = element->NextSiblingElement();
            }

            GLfloat x = atof(element->FirstChildElement("x")->GetText());
            GLfloat w = atof(element->FirstChildElement("width")->GetText()) + spacing;
            GLfloat y = sprite->height - atof(element->FirstChildElement("y")->GetText());
            GLfloat h = atof(element->FirstChildElement("height")->GetText());
            GLfloat realX = (GLfloat)x / sprite->width;
            GLfloat realY = (GLfloat)y / sprite->height;
            GLfloat realW = (GLfloat)(x + w) / sprite->width;
            GLfloat realH = (GLfloat)(y - h) / sprite->height;

            positions.push_back(vec4(position, vec2(realX, realH)));
            positions.push_back(vec4(position + vec2(0, h), vec2(realX, realY)));
            positions.push_back(vec4(position + vec2(w, 0), vec2(realW, realH)));
            positions.push_back(vec4(position + vec2(w, h), vec2(realW, realY)));

            height += h;
            width += w;

            position += vec2(w, 0);
        }

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vec4) * positions.size(), &positions[0], GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glBindVertexArray(0);

        height /= text.size();
        this->text = text;
    }
}

GLvoid StringGL::setColour(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    colour[0] = r;
    colour[1] = g;
    colour[2] = b;
    colour[3] = a;
}

GLuint StringGL::getHeight()
{
    return(height);
}

GLuint StringGL::getWidth()
{
    return(width);
}

GLuint StringGL::getTextureID()
{
    return sprite->uniqueID;
}

GLuint StringGL::getStringLength()
{
    return(text.size() * 4);
}

GLuint StringGL::getVertexArray()
{
    return vao;
}

ObjectGL * StringGL::getObject()
{
    return object;
}

std::string StringGL::getString()
{
    return text;
}

GLfloat* StringGL::getColour()
{
    return colour;
}