
#pragma once

#include "TextureGL.h"
#include "Projectiles.h"
#include "Trajectory.h"

class Cannon
{
	Projectiles * m_pProjectiles;		

	vector<TextureGL *> m_pSprites;
	ObjectGL * m_pStaticObject;
	ObjectGL * m_pRotateObject;
	Material m_BallMaterial;
	
	float m_Angle;				

public:
	Cannon();
	~Cannon();

	void onKeyPress(int, int);
	void initialise();
	void onUpdate();
	void Fire();

	ObjectGL * getStaticObject() { return m_pStaticObject; }
	ObjectGL * getRotateObject() { return m_pRotateObject; }

	float getAngle() { return m_Angle; };
	vector<Projectile *>& getProjectiles();
	vector<TextureGL *>& getTextures();
	Trajectory * getTrajectory();
	Projectile* getProjectile();
	Projectiles* getProjects();

	Material getBallMaterial(){ return m_BallMaterial; }
};