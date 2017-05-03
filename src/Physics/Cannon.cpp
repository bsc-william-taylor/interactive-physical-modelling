
/* -------------------------------------------------
  
 @Filename  : Cannon.cpp
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: Class implementation

 ------------------------------------------------- */

#include "Win32Codes.h"
#include "Cannon.h"
#include "Main.h"

// Constructor & Deconstructor
Cannon::Cannon()
	: m_pProjectiles(new Projectiles()),
	  m_pStaticObject(new GL_Object()),
	  m_pRotateObject(new GL_Object()),
	  m_Angle(0)
{
	m_BallMaterial = Material::IRON;
	for(int i = 0; i < 3; i++)
		m_pSprites.push_back(new GL_Texture());
}

Cannon::~Cannon()
{
	SAFE_RELEASE(m_pProjectiles);

	for(int i = 0; i < 3; i++)
		 delete m_pSprites[i];
}

// Member Functions
void Cannon::Initialise()
{
	m_pRotateObject->setOrtho2D(vec4(0, 0, 1280, 720));
	m_pRotateObject->setPosition(vec2(0, 0));
	m_pRotateObject->setSize(vec2(235, 96));
	
	m_pStaticObject->setOrtho2D(vec4(0, 0, 1280, 720));
	m_pStaticObject->setPosition(vec2(0, 0));
	m_pStaticObject->setSize(vec2(235, 96));

	std::string filenames[3] = {
		"data/img/c3.png",
		"data/img/cannon96.png",
		"data/img/c1.png"
	};

	for(int i = 0; i < 3; i++)
	{
		m_pSprites[i]->setTexture(filenames[i], GL_CLAMP_TO_EDGE);
		
		if(i == 1)
			m_pSprites[i]->setParameters(m_pRotateObject);
		else
		m_pSprites[i]->setParameters(m_pStaticObject);

		m_pSprites[i]->Prepare();
	}

	m_pProjectiles->setMaxProjectiles(1);

	float cannonLengthX = 90.0*cosf(glm::radians(m_Angle));
	float cannonLengthY = 90.0*sinf(glm::radians(m_Angle));
	float xComponent(FULCRUM_X-10+ cannonLengthX);		// 10 is bomb radius seeing the fact the origin is not in the center
	float yComponent(FULCRUM_Y-10+ cannonLengthY);		// bomb radius again

	m_pProjectiles->Initialise(m_Angle, vec2(xComponent, yComponent), vec2(xComponent, yComponent));
}

Trajectory * Cannon::getTrajectory()
{
	return m_pProjectiles->getTrajectory();
}

void Cannon::Fire()
{
	m_pProjectiles->FireProjectile(m_Angle);
}

void Cannon::onKeyPress(int Key, int State)
{
	switch(Key)
	{
		case ARROW_DOWN: if(m_Angle > 0) m_Angle--; break;
		case ARROW_UP: if(m_Angle < 90) m_Angle++; break;
			
		case FOUR:m_pProjectiles->SetMaterial(Material::STONE); m_BallMaterial = Material::STONE; break;
		case THREE: m_pProjectiles->SetMaterial(Material::COPPER); m_BallMaterial = Material::COPPER; break;
		case TWO:m_pProjectiles->SetMaterial(Material::ALUMINIUM); m_BallMaterial = Material::ALUMINIUM; break;
		case ONE: m_pProjectiles->SetMaterial(Material::IRON); m_BallMaterial = Material::IRON; break;

		default: break;
	};	
}

Projectile* Cannon::getProjectile()
{
	return m_pProjectiles->getTextures().at(0);
}

void Cannon::onUpdate()
{
	m_pStaticObject->setIdentity();
	m_pRotateObject->setIdentity();

	m_pRotateObject->setTranslate(vec2(FULCRUM_X, FULCRUM_Y));
	m_pRotateObject->setRotation(glm::radians((float)m_Angle), vec3(0.0, 0.0, 1.0));
	m_pRotateObject->setTranslate(-vec2(FULCRUM_X, FULCRUM_Y));
	
	m_pProjectiles->onUpdate();
}

// Get & Set Functions
vector<Projectile *>& Cannon::getProjectiles()
{
	return m_pProjectiles->getTextures();
}

std::vector<GL_Texture *>& Cannon::getTextures()
{
	return m_pSprites;
}

Projectiles* Cannon::getProjects()
{
	return m_pProjectiles;
}
