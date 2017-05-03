
#pragma once

#include "GL_Renderer.h"
#include "Button.h"
#include "SceneList.h"
#include "SceneObjects.h"

class SceneInterface : public ISceneList, public IEvent
{
private:

	SceneObjects * m_pSceneObjects;
	
	GL_String * m_pStatusStrings[4];
	GL_String * m_pStrings[4];
	GL_Object * m_pStatusObjects[3];
	GL_Object * m_pObjects[4];
	
	Button * m_pAirResistance;
	Button * m_pReloadButton;
	Button * m_pQuitButton;
	Button * m_pButtons[8];

	std::vector<GLuint> m_IDs;

public:

	SceneInterface();
	~SceneInterface();

	void MousePress(int, int, int, int);
	void GiveObjects(SceneObjects *);
	void VUpdate();
	void VRender();
	void VLoad();

	std::string getMessage();
	void onTriggered(void *);

private:

	GL_Renderer * m_pRenderer;
	
	GL_Texture * m_pSettingsTexture;
	GL_Texture * m_pHeaderTexture;
	GL_Texture * m_pBackPlate;
	
	GL_Object * m_pSettingsObject;
	GL_Object * m_pHeaderObject;
	GL_Object * m_pBackObject;
};