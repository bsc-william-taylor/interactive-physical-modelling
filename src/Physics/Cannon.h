
#pragma once

#include "GL_Texture.h"
#include "Projectiles.h"
#include "Trajectory.h"

class Cannon
{
	Projectiles * m_pProjectiles;		

	vector<GL_Texture *> m_pSprites;
	GL_Object * m_pStaticObject;
	GL_Object * m_pRotateObject;
	Material m_BallMaterial;
	
	float m_Angle;				

public:
	Cannon();
	~Cannon();

	void onKeyPress(int, int);
	void initialise();
	void onUpdate();
	void Fire();

	GL_Object * getStaticObject() { return m_pStaticObject; }
	GL_Object * getRotateObject() { return m_pRotateObject; }

	float getAngle() { return m_Angle; };
	vector<Projectile *>& getProjectiles();
	vector<GL_Texture *>& getTextures();
	Trajectory * getTrajectory();
	Projectile* getProjectile();
	Projectiles* getProjects();

	Material getBallMaterial(){ return m_BallMaterial; }
};