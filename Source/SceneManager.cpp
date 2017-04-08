
/* -------------------------------------------------
  
 @Filename  : SceneManager.cpp
 @author	: William Taylor
 @date		: 12/02/2014
 @purpose	: class implementation

 ------------------------------------------------- */

#include "SceneManager.h"

// Initialise static variable
SceneManager * SceneManager::m_pManager = NULL;

// Constructor & Deconstructor
SceneManager::SceneManager() 
	: m_pFactory(new SceneFactory()),
	  m_CurrentPlace(NULL)
{
}

SceneManager::~SceneManager()
{
	m_vScenes.erase(m_vScenes.cbegin(), m_vScenes.cend());
	m_pManager = NULL;
}

// Member Functions
void SceneManager::StartFrom(unsigned int startingPoint)
{
	m_CurrentPlace = startingPoint;
}

void SceneManager::EnableFactory()
{
	for(unsigned int i = 0; i < m_vScenes.size(); i++)
	{
		m_vScenes[i]->VOnCommit(m_pFactory);	
	}

	for(unsigned int i = 0; i < m_vScenes.size(); i++)
	{
		m_vScenes[i]->VOnRequest(m_pFactory);	
	}
}

void SceneManager::PreviousScene()
{
	m_CurrentPlace--;
}

void SceneManager::NextScene()
{
	m_CurrentPlace++;
}

void SceneManager::PushState(Scene * state)
{
	if(state != NULL)
	{
		m_vScenes.push_back(state);
	}
}

void SceneManager::UpdateManager()
{
	m_vScenes[m_CurrentPlace]->Update();
	m_vScenes[m_CurrentPlace]->Render();
}

void SceneManager::SwitchTo(unsigned int newPlace)
{
	m_vScenes[m_CurrentPlace]->Enter();
	m_CurrentPlace = newPlace;
	m_vScenes[m_CurrentPlace]->Exit();
}


// Get & Set Functions
Scene * SceneManager::getCurrent()
{
	if(m_vScenes.empty())
	{
		return NULL;
	}

	return m_vScenes[m_CurrentPlace];
}

SceneManager * SceneManager::get()
{
	if(m_pManager == 0)
	{
		m_pManager = new SceneManager();
	} 

	return m_pManager;
}