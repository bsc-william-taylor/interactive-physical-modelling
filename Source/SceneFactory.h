
/* -------------------------------------------------
  
 @Filename  : SceneFactory.h
 @author	: William Taylor
 @date		: 12/02/2014

 @purpose	:  A Factory that stores objects
			   that need to be shared between
			   states

 ------------------------------------------------- */

#pragma once

#include "Win32Header.h"

// Should be expanded !!!
class SceneFactory
{
private:

	// Data type for storing each object
	struct Asset
	{
		std::string ID;
		void * data;
	};

private:

	std::vector<Asset *> m_Assets;		// Vector of objects

public:

	// Constructor & Deconstructor
	SceneFactory();
	~SceneFactory();

	// Member Functions
	void PushAsset(std::string, void *);
		
	// Template Functions
	template<class T>
	T * GrabAsset(const std::string& ID)
	{
		try 
		{
			for(unsigned int i = 0; i < m_Assets.size(); i++)
			{
				if(m_Assets[i]->ID == ID)
				{
					auto value = static_cast<T *>(m_Assets[i]->data);
					return value;
				}
			} 
		} 
		catch(...)
		{
			std::string msg = "Could Not Find Asset : ";
			msg.append(ID);
			MessageBox(0, msg.c_str(), "Error", MB_OK);
			PostQuitMessage(0);
		} 
		
		return NULL;
	}
};