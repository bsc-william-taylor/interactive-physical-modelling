
/* -------------------------------------------------
  
 @Filename  : SceneList.h
 @author	: William Taylor
 @date		: 12/02/2014

 @purpose	: A interface that sets out the layout 
			  for how a collection of scene objects 
			  should be implemented.

 ------------------------------------------------- */

#pragma once

#include "SceneFactory.h"

class ISceneList
{
public:

	virtual void VOnRequest(SceneFactory *){}
	virtual void VOnCommit(SceneFactory *){}
	virtual void VUpdate() = 0;
	virtual void VRender() = 0;
	virtual void VLoad() = 0;
	virtual ~ISceneList(){};
};

// DONE