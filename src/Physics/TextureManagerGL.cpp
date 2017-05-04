
#include "TextureManagerGL.h"

TextureManagerGL * TextureManagerGL::manager = nullptr;

TextureManagerGL::TextureManagerGL()
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

TextureManagerGL::~TextureManagerGL()
{
    freeTextures();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

SpriteGL* TextureManagerGL::createTexture(const std::string& filename, GLenum param)
{
    if (textures.count(filename) != 0)
    {
        return textures[filename];
    }

    auto texture = loadTexture(filename, param);

    if (texture != nullptr)
    {
        textures[filename] = texture;
    }

    return texture;
}

GLuint TextureManagerGL::getTextureCount()
{
    return(textures.size());
}

SpriteGL* TextureManagerGL::createTexture(GLubyte * data, GLuint width, GLuint height, GLenum format)
{
    auto sprite = new SpriteGL();
    sprite->height = height;
    sprite->width = width;

    glGenTextures(1, &sprite->uniqueID);
    glBindTexture(GL_TEXTURE_2D, sprite->uniqueID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, (GLvoid *)data);
    return sprite;
}

SpriteGL* TextureManagerGL::loadTexture(const std::string& WindowLocation, GLenum e)
{
    auto format = FreeImage_GetFileType(WindowLocation.c_str(), 0);
    auto texture = FreeImage_Load(format, WindowLocation.c_str());
    auto buffer = FreeImage_ConvertTo32Bits(texture);
    auto height = FreeImage_GetHeight(buffer);
    auto width = FreeImage_GetWidth(buffer);
    auto rgba = new BYTE[height * width * 4];
    auto bgra = FreeImage_GetBits(buffer);

    for (auto i = 0; i < width * height; i++)
    {
        rgba[i * 4 + 0] = bgra[i * 4 + 2];
        rgba[i * 4 + 1] = bgra[i * 4 + 1];
        rgba[i * 4 + 2] = bgra[i * 4 + 0];
        rgba[i * 4 + 3] = bgra[i * 4 + 3];
    }

    auto sprite = new SpriteGL();
    sprite->height = height;
    sprite->width = width;

    glGenTextures(1, &sprite->uniqueID);
    glBindTexture(GL_TEXTURE_2D, sprite->uniqueID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, e);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, e);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)rgba);

    delete[] rgba;

    FreeImage_Unload(texture);
    FreeImage_Unload(buffer);
    return sprite;
}

GLvoid TextureManagerGL::freeTextures()
{
    for (auto& texture : textures)
    {
        glDeleteTextures(1, &texture.second->uniqueID);
        SAFE_RELEASE(texture.second);
    }

    textures.clear();
}

TextureManagerGL * TextureManagerGL::get()
{
    if (manager == nullptr)
    {
        manager = new TextureManagerGL();
    }

    return manager;
}