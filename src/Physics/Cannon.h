
/* -------------------------------------------------
  
 @Filename  : Cannon.h
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: A cannon object that will fire 
			  projectiles.

 ------------------------------------------------- */

#pragma once

#include "GL_Texture.h"
#include "Projectiles.h"
#include "Trajectory.h"

class Cannon
{
private:

	Projectiles * m_pProjectiles;		// A list of projectiles

	vector<GL_Texture *> m_pSprites;
	GL_Object * m_pStaticObject;
	GL_Object * m_pRotateObject;
	Material m_BallMaterial;
	
	float m_Angle;					// rotation of the object.

public:

	// Constructor & Deconstructor
	Cannon();
	~Cannon();

	// Member Functions
	void onKeyPress(int, int);
	void Initialise();
	void onUpdate();
	void Fire();

	GL_Object * getStaticObject() { return m_pStaticObject; }
	GL_Object * getRotateObject() { return m_pRotateObject; }
	// Set & get Functions
	float getAngle() { return m_Angle; };
	vector<Projectile *>& getProjectiles();
	vector<GL_Texture *>& getTextures();
	Trajectory * getTrajectory();
	Projectile* getProjectile();
	Projectiles* getProjects();

	Material getBallMaterial(){ return m_BallMaterial; }
};