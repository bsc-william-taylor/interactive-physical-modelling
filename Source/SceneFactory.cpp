
/* -------------------------------------------------
  
 @Filename  : SceneFactory.cpp
 @author	: William Taylor
 @date		: 12/02/2014

 @purpose	: Class implementation

 ------------------------------------------------- */

#include "SceneFactory.h"

// Constructor & Deconstructor
SceneFactory::SceneFactory()
{
	m_Assets.reserve(20);
}

SceneFactory::~SceneFactory()
{
}

// Member Functions
void SceneFactory::PushAsset(std::string ID, void * data)
{
	Asset * asset = new Asset();
	asset->data = data;
	asset->ID = ID;

	m_Assets.push_back(asset);
}