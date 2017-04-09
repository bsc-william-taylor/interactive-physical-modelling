
/* -------------------------------------------------
  
 @Filename  : Projectiles.h
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: A list for each projectile fired

 ------------------------------------------------- */

#pragma once

#include "GL_Renderer.h"
#include "Projectile.h"
#include "Trajectory.h"

enum class Material
{
	IRON = 1,
	ALUMINIUM,
	COPPER,
	STONE
};

class Projectiles
{
private:

	vector<Projectile *> m_Projectiles;			// The projectiles	
	vector<GLuint> m_TextureIDs;
	Trajectory * m_pTrajectory;
	unsigned int m_Count;						// Current play in the vector 
	unsigned int m_Max;							// The amount of projectiles
	vec3 m_Scale;

public:

	// Constructor & Deconstructor
	Projectiles();
	~Projectiles();

	// Member Functions
	void Initialise(float angle, vec2, vec2);
	void FireProjectile(float angle);
	void SetMaterial(Material);
	void Update();

	// Get & Set Functions
	vector<Projectile *>& getTextures();
	Trajectory * getTrajectory();

	void setMaxProjectiles(unsigned int);
};