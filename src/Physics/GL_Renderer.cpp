
/* -------------------------------------------------
  
 @Filename  : GL_Renderer.h
 @author	: William Taylor
 @date		: 14/02/2014

 @purpose	: Class Implementation

 ------------------------------------------------- */

#include "GL_Renderer.h"

// Constructor & Deconstructor
GL_Renderer::GL_Renderer()
{
	m_Textures.reserve(20);
}

GL_Renderer::~GL_Renderer()
{
	for(unsigned int i = 0; i < m_Textures.size(); i++)
	{
		delete m_Textures[i];
		m_Textures[i] = NULL;
	}
}

// Member Functions
GLvoid GL_Renderer::RenderTexture(GL_Texture * texture)
{
	GL_Object* glObject = texture->getObject();
    GLuint Tex = texture->getTextureID();
    GLuint VAO = texture->getVAO();

    glObject->BindProgram();
    glBindVertexArray(VAO);
    glObject->sendMatricesToShader();

    glBindTexture(GL_TEXTURE_2D, Tex);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glObject->EndProgram();
}

GLvoid GL_Renderer::RenderString(GL_String * game_str)
{
	auto object = game_str->getObject();
    object->BindProgram();
    object->sendMatricesToShader();

    GL_Program * program = object->getShader();
    GLuint colourID = program->getUniform("text_colour");

    glBindVertexArray(game_str->getVertexArray());
    glUniform4fv(colourID, 1, game_str->getColour());
    glBindTexture(GL_TEXTURE_2D, game_str->getTextureID());
    glDrawArrays(GL_TRIANGLE_STRIP, 0, game_str->getStringLength());
    glBindVertexArray(0);

    object->EndProgram();
}


GLvoid GL_Renderer::PushTexture(GL_Texture * object)
{
	if(object != NULL) 
	{
		m_Textures.push_back(object);
	} 
}


GLvoid GL_Renderer::Prepare()
{
	for(unsigned int i = 0; i < m_Textures.size(); i++)
	{
		m_Textures[i]->Prepare();
	}
}

GLvoid GL_Renderer::onRender()
{
	for(unsigned int i = 0; i < m_Textures.size(); i++)
	{
		RenderTexture(m_Textures[i]);
	}

	for(unsigned int i = 0; i < m_Labels.size(); i++)
	{
		RenderString(m_Labels[i]);
	}
}

GLvoid GL_Renderer::PushText(GL_String * textItem)
{
	if(textItem != NULL)
	{
		m_Labels.push_back(textItem);
	}
}