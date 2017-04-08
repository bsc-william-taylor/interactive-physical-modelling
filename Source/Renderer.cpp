
/* -------------------------------------------------
  
 @Filename  : Renderer.cpp
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: Class implementation

 ------------------------------------------------- */

#include "Renderer.h"

// Constructor & Deconstructor
Renderer::Renderer()
	: m_pRenderer(new GL_Renderer())
{
}

Renderer::~Renderer()
{
	SAFE_RELEASE(m_pRenderer);
}

// Member Functions
void Renderer::RenderBackground(GL_Texture * background)
{
	// Background is just a texture so we just render it haha :P
	m_pRenderer->RenderTexture(background);
}

void Renderer::RenderCannon(Cannon * cannon)
{
	// Get all projectiles in the scene
	vector<Projectile *>& vec = cannon->getProjectiles();
	for(auto iterator = vec.begin(); iterator != vec.end(); ++iterator)
	{
		// If its been fired draw the projectile.
		if((*iterator)->hasFired()) 
		{
			auto position = (*iterator)->getPosition() + (*iterator)->getVelocity();
			
			cannon->getTrajectory()->PlotPoint(position.x, position.y, 5.0f);
			cannon->getTrajectory()->Render();
			
			m_pRenderer->RenderTexture((*iterator)->getSprite());
		}
	}

	// Render the cannon itself
	std::vector<GL_Texture *>& textures =  cannon->getTextures();
	for(auto i = textures.begin(); i != textures.end(); ++i)
	{
		m_pRenderer->RenderTexture((*i));
	}
}

void Renderer::RenderTarget(Target * pTarget)
{
	m_pRenderer->RenderTexture( pTarget->getSprite() );
}