
/* -------------------------------------------------
  
 @Filename  : GL_Texture_Manager.cpp
 @author	: William Taylor
 @date		: 14/02/2014

 @purpose	: Class implementation

 ------------------------------------------------- */

#include "GL_Texture_Manager.h"

TextureManagerGL * TextureManagerGL::manager = NULL;

// Constructor & Deconstructor
TextureManagerGL::TextureManagerGL()
{
	glEnable(GL_TEXTURE_2D);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

TextureManagerGL::~TextureManagerGL()
{
	FreeTextures();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

// Member Functions
GL_Sprite * TextureManagerGL::CreateTexture(const std::string& filename, GLenum e)
{
	for(unsigned int i = 0; i < m_Textures.size(); i++)
	{
		if(m_Textures[i]->m_TextureName == filename)
		{
			return m_Textures[i];
		}
	}

	GL_Sprite * Tex = LoadTexture(filename, e);
		
	if(Tex != NULL)
	{
		Tex->m_TextureName = filename;
		m_Textures.push_back(Tex);
	}

	return Tex;
}

GLuint TextureManagerGL::getTextureCount()
{
	return(m_Textures.size());
}


GL_Sprite * TextureManagerGL::CreateTexture(GLubyte * data, GLuint width, GLuint height, GLenum format)
{
	GL_Sprite * Sprite = new GL_Sprite();

	Sprite->Height = height;
	Sprite->Width = width;

	glGenTextures(1, &Sprite->m_ID);
	glBindTexture(GL_TEXTURE_2D, Sprite->m_ID);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, (GLvoid *)data);

	return Sprite;
}

GL_Sprite * TextureManagerGL::LoadTexture(const std::string& WindowLocation, GLenum e)
{
	GL_Sprite * Sprite = new GL_Sprite();

	FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(WindowLocation.c_str(), 0);
		
	FIBITMAP * Texture = FreeImage_Load(formato, WindowLocation.c_str());
	FIBITMAP * Temp    = FreeImage_ConvertTo32Bits(Texture);
		
	GLuint Height = FreeImage_GetHeight(Temp);
	GLuint Width = FreeImage_GetWidth(Temp);

	BYTE * NewBits	= new BYTE[Height * Width * 4];
	BYTE * Bits		= FreeImage_GetBits(Temp);

	Sprite->Height = Height;
	Sprite->Width = Width;

	for (GLuint i = 0; i < Width * Height; i++)
	{
        NewBits[i * 4 + 0] = Bits[i * 4 + 2];
        NewBits[i * 4 + 1] = Bits[i * 4 + 1];
        NewBits[i * 4 + 2] = Bits[i * 4 + 0];
        NewBits[i * 4 + 3] = Bits[i * 4 + 3];
    }		

	RGBQUAD Colour;

	FreeImage_GetPixelColor(Temp, 0, 0, &Colour);

	glGenTextures(1, &Sprite->m_ID);
	glBindTexture(GL_TEXTURE_2D, Sprite->m_ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, e);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, e);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *)NewBits);
	
	FreeImage_Unload(Texture);
	FreeImage_Unload(Temp);
	
	delete[] NewBits;
	return Sprite;
}

GLvoid TextureManagerGL::FreeTextures()
{
	for(GLuint i = 0; i < m_Textures.size(); i++)
	{
		glDeleteTextures(1, &m_Textures[i]->m_ID);
	}
}

// Get Functions
TextureManagerGL * TextureManagerGL::get()
{
	if(manager == NULL) 
	{
		manager = new TextureManagerGL();
	}

	return manager;
}