
#include "RendererGL.h"

RendererGL::RendererGL()
{
    textures.reserve(20);
}

RendererGL::~RendererGL()
{
    for (auto& texture : textures)
    {
        delete texture;
    }
}

GLvoid RendererGL::renderTexture(TextureGL * texture)
{
    auto object = texture->getObject();
    auto textureID = texture->getTextureID();
    auto arrayID = texture->getVAO();

    object->bindProgram();
    object->sendMatricesToShader();

    glBindVertexArray(arrayID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);

    object->endProgram();
}

GLvoid RendererGL::renderString(StringGL * string)
{
    auto object = string->getObject();
    auto program = object->getShader();
    auto location = program->getUniform("text_colour");

    object->bindProgram();
    object->sendMatricesToShader();

    glBindVertexArray(string->getVertexArray());
    glUniform4fv(location, 1, string->getColour());
    glBindTexture(GL_TEXTURE_2D, string->getTextureID());
    glDrawArrays(GL_TRIANGLE_STRIP, 0, string->getStringLength());
    glBindVertexArray(0);

    object->endProgram();
}


GLvoid RendererGL::pushTexture(TextureGL * object)
{
    if (object != nullptr)
    {
        textures.push_back(object);
    }
}

GLvoid RendererGL::prepare()
{
    for (auto i = 0; i < textures.size(); i++)
    {
        textures[i]->prepare();
    }
}

GLvoid RendererGL::onRender()
{
    for (auto i = 0; i < textures.size(); i++)
    {
        renderTexture(textures[i]);
    }

    for (auto i = 0; i < labels.size(); i++)
    {
        renderString(labels[i]);
    }
}

GLvoid RendererGL::pushText(StringGL * textItem)
{
    if (textItem != nullptr)
    {
        labels.push_back(textItem);
    }
}