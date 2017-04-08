
/* -------------------------------------------------
  
 @Filename  : SceneObjects.h
 @author	: William Taylor
 @date		: 12/02/2014

 @purpose	: All the objects in the scene.

 ------------------------------------------------- */

#include "SceneObjects.h"
#include "Win32Codes.h"

// Constructor & Deconstructor
SceneObjects::SceneObjects()
	: m_pRenderer(new Renderer()),
	  m_pCannon(new Cannon()),
	  m_pTarget(new Target())
{
	m_pBackground = NULL;
	m_Reload = false;
}

SceneObjects::~SceneObjects()
{
	SAFE_RELEASE(m_pRenderer);
	SAFE_RELEASE(m_pCannon);
}

// Member Functions
void SceneObjects::VRender()
{
	m_pRenderer->RenderBackground(m_pBackground);
	m_pRenderer->RenderCannon(m_pCannon);
	m_pRenderer->RenderTarget(m_pTarget);
}

Cannon* SceneObjects::getCannon()
{
	return m_pCannon;
}

Target* SceneObjects::getTarget()
{
	return m_pTarget;
}

bool SceneObjects::mustReload()
{
	return m_Reload;
}

void SceneObjects::KeyPress(int Key, int State)
{
	m_pCannon->KeyPress(Key, State);

	if(Key == SPACE && State == PRESSED && !m_Reload)
	{
		m_pCannon->Fire();
		m_Reload = true;
	}

	if(Key == R_KEY && State == PRESSED)
	{
		m_Reload = false;

		m_Camera.x = 0;
	}

	if(Key == W_KEY && State == PRESSED)
	{
		float mass = m_pCannon->getProjectile()->getMass() + 0.1f;
		m_pCannon->getProjectile()->setMass( mass );
	}

	if(Key == S_KEY && State == PRESSED)
	{
		float mass = m_pCannon->getProjectile()->getMass() - 0.1f;
		m_pCannon->getProjectile()->setMass( mass );

	}

#define CAMERASPEED 10.0f

	if(Key == ARROW_LEFT)
	{
		m_Camera.x -= CAMERASPEED;

		if(m_Camera.x < 0)
		{
			m_Camera.x = 0.0f;
		}
	}
	else if(Key == ARROW_RIGHT)
	{
		m_Camera.x += CAMERASPEED;

		if(m_Camera.x > 2570)
		{
			m_Camera.x = 2570.0f;
		}
	}
}

void SceneObjects::MousePress(int button, int state, int x, int y)
{
	m_pTarget->MousePress(button, state, x + m_Camera.x, y + m_Camera.y );
}

void SceneObjects::VOnRequest(SceneFactory * Factory)
{
	m_pBackground = Factory->GrabAsset<GL_Texture>("MenuBackground");
}

void SceneObjects::VLoad()
{
	m_pCannon->Initialise();
	m_pCannon->getProjects()->SetMaterial( Material::IRON );
	m_pTarget->Setup( vec2( 1000, 200 ) );
}

void SceneObjects::VUpdate()
{
	m_pBackground->getObject()->getMatrix()->Ortho( vec2(0, 1280), vec2(0, 720) );
	m_pBackground->getObject()->getMatrix()->LookAt( m_Camera );
	m_pCannon->getStaticObject()->getMatrix()->LookAt( m_Camera );
	m_pCannon->getRotateObject()->getMatrix()->LookAt( m_Camera );
	m_pTarget->getObject()->getMatrix()->LookAt( m_Camera );
	m_pCannon->getTrajectory()->getMatrix()->LookAt( m_Camera );
	
	vector<Projectile *>& vec = m_pCannon->getProjectiles();

	for(auto iterator = vec.begin(); iterator != vec.end(); ++iterator)
	{
		(*iterator)->getObject()->getMatrix()->LookAt( m_Camera );
	}

	m_pCannon->getTrajectory()->getMatrix()->LookAt( m_Camera );

	m_pCannon->Update();
	m_pTarget->Update();
}
