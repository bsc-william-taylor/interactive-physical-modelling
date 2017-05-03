
/* -------------------------------------------------
  
 @Filename  : Projectiles.h
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: A list for each projectile fired

 ------------------------------------------------- */

#include <cmath>

#include "GL_Texture_Manager.h"
#include "Projectiles.h"
#include "Main.h"

double acos(int angle) { return cos(3.14156892/180*angle); };			//returns cosine from degrees
double asin(int angle) { return sin(3.14156892/180*angle); };			//returns sine from degrees

// Constructor & Deconstructor
Projectiles::Projectiles()
	: m_Count(0),
	  m_Max(10)
{
	TextureManagerGL * mgr = TextureManagerGL::get();
	m_pTrajectory = new Trajectory();
	
	m_TextureIDs.push_back(mgr->CreateTexture("data/img/iron.png", GL_CLAMP_TO_EDGE)->m_ID);
	m_TextureIDs.push_back(mgr->CreateTexture("data/img/aluminium.png", GL_CLAMP_TO_EDGE)->m_ID);
	m_TextureIDs.push_back(mgr->CreateTexture("data/img/copper.png", GL_CLAMP_TO_EDGE)->m_ID);
	m_TextureIDs.push_back(mgr->CreateTexture("data/img/steel.png", GL_CLAMP_TO_EDGE)->m_ID);
}

Projectiles::~Projectiles()
{
	for(auto i = m_Projectiles.cbegin(); i != m_Projectiles.cend(); ++i)
		delete(*i);
}

// Member Functions
void Projectiles::Initialise(float angle, vec2 vec, vec2 startPosition)
{
	// Initialise all projectiles
	float xVariation = cosf(glm::radians(angle));
	float yVariation = sinf(glm::radians(angle));

	m_pTrajectory->StartFrom(vec.x, vec.y, 5.0f);

	for(unsigned int i = 0; i < m_Max; i++)
	{
		Projectile * p = new Projectile();
		
		p->setOffset(vec2(xVariation, yVariation));
		p->setMass(10.0);
		p->Setup(startPosition);

		m_Projectiles.push_back(p);
	}
}

Trajectory * Projectiles::getTrajectory()
{	
	return m_pTrajectory;
}

void Projectiles::FireProjectile(float angle)
{
	// Reset the projectiles and fire it
	if(m_Count < m_Max)
	{
		m_Projectiles[m_Count]->Reset(angle);
		m_Projectiles[m_Count]->Fire(); 
	} 
	else
	{
		m_Projectiles[0]->Reset(angle);
		m_Count = 0;
	}

	auto p = m_Projectiles[m_Count]->getPosition() + m_Projectiles[m_Count]->getVelocity();

	m_pTrajectory->Clear();
	m_pTrajectory->ResetStart(p.x, p.y);

	++m_Count;
}

void Projectiles::SetMaterial(Material material)
{
	m_Projectiles.at(0)->getSprite()->setID(m_TextureIDs[(int)material - 1]);

	float radius = 5.0f * CM;
	float diametre = 2.0f * radius;
	m_Projectiles.at(0)->setSize(vec2(diametre, diametre));

	float volume = (4.0f / 3.0f) * pi<float>() * radius * radius * radius;
	float density = DENSITY[ (int)material - 1 ];
	float mass = density * volume;

	m_Projectiles.at(0)->setMass( mass );
}

void Projectiles::onUpdate()
{
	auto iterator = m_Projectiles.begin();
	
	// Iterate the vector and update each object
	while(iterator != m_Projectiles.end())
	{
		(*iterator)->onUpdate();
		++iterator;
	}
}

// Get & Set Functions
vector<Projectile *>& Projectiles::getTextures()
{
	return m_Projectiles;
}

void Projectiles::setMaxProjectiles(unsigned int newMax)
{
	m_Max = newMax;
}