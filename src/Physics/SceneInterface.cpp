
#include "SceneInterface.h"
#include "SceneManager.h"
#include "Win32Codes.h"
#include "Main.h"
#include "Scenes.h"

SceneInterface::SceneInterface()
	: m_pHeaderTexture(new GL_Texture()),
	  m_pHeaderObject(new GL_Object()),
	  m_pRenderer(new GL_Renderer()),
	  m_pBackObject(new GL_Object()),
	  m_pBackPlate(new GL_Texture()),
	  m_pQuitButton(new Button())
{
	float x[4] = { 1150, 1143, 1160, 1160 };
	float y = 467;
	for(int i = 0; i < 4; i++)
	{
		m_pObjects[i] = new GL_Object();
		m_pObjects[i]->setOrtho2D(vec4(0, 0, 1280, 720));
		m_pObjects[i]->setPosition(vec2(x[i], y));
		m_pObjects[i]->setSize(vec2(18, 18));

		m_pStrings[i] = new GL_String("data/version.xml", "data/version.png");
		m_pStrings[i]->setParameters(m_pObjects[i]);
		m_pStrings[i]->setColour(1, 1, 1, 1);
		m_pStrings[i]->setString("0");
		m_pStrings[i]->Prepare();
		
		y += 15;
	}

	float y2 = 380;

	for(int i = 0; i < 4; i++)
	{
		m_pStatusObjects[i] = new GL_Object();
		m_pStatusObjects[i]->setOrtho2D(vec4(0, 0, 1280, 720));
		m_pStatusObjects[i]->setPosition(vec2(1125, y2));
		m_pStatusObjects[i]->setSize(vec2(15, 15));

		m_pStatusStrings[i] = new GL_String("data/version.xml", "data/version.png");
		m_pStatusStrings[i]->setParameters(m_pStatusObjects[i]);
		m_pStatusStrings[i]->setString("0");
		m_pStatusStrings[i]->setColour(1, 1, 1, 1);
		m_pStatusStrings[i]->Prepare();

		y2 += 15;
	}

	m_pAirResistance = new Button();
	m_pAirResistance->SetTexture("data/img/enabled.png");
	m_pAirResistance->SetPosition("", vec2(1125, 428), vec2(78, 14));
	m_pAirResistance->OnPress(this);
}

SceneInterface::~SceneInterface()
{
	SAFE_RELEASE(m_pHeaderTexture);
	SAFE_RELEASE(m_pHeaderObject);
	SAFE_RELEASE(m_pQuitButton);
	SAFE_RELEASE(m_pBackObject);
	SAFE_RELEASE(m_pBackPlate);
	SAFE_RELEASE(m_pRenderer);

	for(int i = 0; i < 4; i++)
	{
		SAFE_RELEASE(m_pStrings[i]);
		SAFE_RELEASE(m_pObjects[i]);
	}
}

void SceneInterface::GiveObjects(SceneObjects * objects)
{
	this->m_pSceneObjects = objects;
}

void SceneInterface::VUpdate()
{
	Projectile* pBall = m_pSceneObjects->getCannon()->getProjectile();

	std::string weight = std::to_string(int(pBall->getMass() * 1000.0f)).append("g");
	std::string angle = std::to_string((int)m_pSceneObjects->getCannon()->getAngle());
	std::string num = std::to_string((int)m_pSceneObjects->getCannon()->getBallMaterial());

	m_pStrings[0]->setString(weight);
	m_pStrings[3]->setString(angle);
	m_pStrings[2]->setString(num);

	switch(m_pSceneObjects->getCannon()->getBallMaterial())
	{
		case 1: m_pStrings[1]->setString("   Iron  ");  m_pHeaderTexture->setID(m_IDs[0]); break;
		case 2: m_pStrings[1]->setString("Aluminium"); m_pHeaderTexture->setID(m_IDs[1]); break;
		case 3: m_pStrings[1]->setString("  Copper ");  m_pHeaderTexture->setID(m_IDs[2]); break;
		case 4: m_pStrings[1]->setString("   Zinc  "); m_pHeaderTexture->setID(m_IDs[3]); break;

		default: break;
	}

	float ballX = pBall->getPosition().x;
	float ballStartX = pBall->getStartPos().x;
	float targetX = m_pSceneObjects->getTarget()->getPosition().x;	
	float distTarget = ( (targetX - ballStartX) + TARGETWIDTH/2 - (ballX - ballStartX) ) / METRE;

	std::string distance = std::to_string( ( ballX - ballStartX ) / METRE ).append("m");
	std::string distTargetStr = std::to_string( abs(distTarget) ).append("m");
	
	m_pStatusStrings[1]->setString(distTargetStr);
	m_pStatusStrings[2]->setString(distance );

	if( distTarget > TARGETWIDTH/(2*METRE) || distTarget < -TARGETWIDTH/(2*METRE) )
	{
		m_pStatusStrings[0]->setString("Missed!");
	}
	else
	{
		if ( pBall->getPosition().y < TARGETHEIGHT/4 )
		{
			m_pStatusStrings[0]->setString("Hit!");
		}
	}
}

void SceneInterface::MousePress(int x, int y, int k, int s)
{
	for(int i = 0; i < 8; i++)
	{
		m_pButtons[i]->MouseState(x, y, k, s);
	}

	m_pAirResistance->MouseState(x, y, k, s);
	m_pReloadButton->MouseState(x, y, k, s);
	m_pQuitButton->MouseState(x, y, k, s);
}

void SceneInterface::VRender()
{
	m_pRenderer->RenderTexture(m_pHeaderTexture);
	m_pRenderer->RenderTexture(m_pQuitButton->getTexture());
	m_pRenderer->RenderString(m_pQuitButton->getString());
	m_pRenderer->RenderTexture(m_pSettingsTexture);
	m_pRenderer->RenderTexture(m_pAirResistance->getTexture());
	m_pRenderer->RenderTexture(m_pBackPlate);

	if(m_pSceneObjects->mustReload())
	{
		m_pRenderer->RenderTexture(m_pReloadButton->getTexture());
	}

	for(int i = 0; i < 3; i++) 
	{
		m_pRenderer->RenderString(m_pStatusStrings[i]);
	}

	for(int i = 0; i < 4; i++) 
	{
		m_pRenderer->RenderString(m_pStrings[i]);
	}

	for(int i = 0; i < 8; i++)
	{
		m_pRenderer->RenderTexture(m_pButtons[i] ->getTexture());
	}
}

void SceneInterface::VLoad()
{
	m_pReloadButton = new Button();
	m_pReloadButton->OnPress(this);
	m_pReloadButton->SetTexture("data/img/reload.png");
	m_pReloadButton->SetPosition("", vec2(1126, 526), vec2(78, 14));

	m_pSettingsObject = new GL_Object();
	m_pSettingsObject->setOrtho2D(vec4(0, 0, 1280, 720));
	m_pSettingsObject->setPosition(vec2(1000, 358));
	m_pSettingsObject->setSize(vec2(228, 96));

	m_pSettingsTexture = new GL_Texture();
	m_pSettingsTexture->setTexture("data/img/status.png", GL_CLAMP_TO_EDGE);
	m_pSettingsTexture->setParameters(m_pSettingsObject);
	m_pSettingsTexture->Prepare();

	float position[] = {
		467, 482, 497, 512,
		467, 482, 497, 512
	};

	for(int i = 0; i < 8; i++)
	{
		m_pButtons[i] = new Button();
		m_pButtons[i]->OnPress(this);

		if(i < 4) 
		{
			m_pButtons[i]->SetTexture("data/img/plus.png"); 
			m_pButtons[i]->SetPosition("", vec2(1190, position[i]), vec2(14, 13));
		} 
		else 
		{
			m_pButtons[i]->SetTexture("data/img/minus.png");
			m_pButtons[i]->SetPosition("", vec2(1125, position[i]), vec2(14, 13));
		}
	}

	m_pHeaderObject->setOrtho2D(vec4(0, 0, 1280, 720));
	m_pHeaderObject->setPosition(vec2(1000, 550));
	m_pHeaderObject->setSize(vec2(228, 96));

	m_pHeaderTexture->setTexture("data/img/header1.png", GL_CLAMP_TO_EDGE);
	m_pHeaderTexture->setParameters(m_pHeaderObject);
	m_pHeaderTexture->Prepare();

	m_pQuitButton->SetPosition("Back", vec2(25, 600), vec2(200, 50));
	m_pQuitButton->OnPress(this);

	m_pBackObject->setOrtho2D(vec4(0, 0, 1280, 720));
	m_pBackObject->setPosition(vec2(1000, 454));
	m_pBackObject->setSize(vec2(228, 96));
	
	m_pBackPlate->setTexture("data/img/console.png", GL_CLAMP_TO_EDGE);
	m_pBackPlate->setParameters(m_pBackObject);
	m_pBackPlate->Prepare();

	m_IDs.push_back(m_pHeaderTexture->getTextureID());
	m_IDs.push_back(GL_TextureManager::get()->CreateTexture("data/img/header2.png", GL_CLAMP_TO_EDGE)->m_ID);
	m_IDs.push_back(GL_TextureManager::get()->CreateTexture("data/img/header3.png", GL_CLAMP_TO_EDGE)->m_ID);
	m_IDs.push_back(GL_TextureManager::get()->CreateTexture("data/img/header4.png", GL_CLAMP_TO_EDGE)->m_ID);
	m_IDs.push_back(GL_TextureManager::get()->CreateTexture("data/img/disabled.png", GL_CLAMP_TO_EDGE)->m_ID);
	m_IDs.push_back(GL_TextureManager::get()->CreateTexture("data/img/enabled.png", GL_CLAMP_TO_EDGE)->m_ID);
}

std::string SceneInterface::getMessage() 
{
	return("Back button pressed");
}

void SceneInterface::onTriggered(void * data) 
{
	if(data == m_pQuitButton)
	{
		SceneManager::get()->SwitchTo((int)SceneStates::MainMenu);
	} 
	else
	{
		auto scene = SceneManager::get()->getCurrent();

		Projectile* pBall = m_pSceneObjects->getCannon()->getProjectile();

		if(data == m_pButtons[3]) 
		{
			scene->KeyPress(ARROW_UP, PRESSED);
		} 
		else if(data == m_pButtons[7]) 
		{
			scene->KeyPress(ARROW_DOWN, PRESSED);
		} 
		else if(data == m_pButtons[6] || data == m_pButtons[5]) 
		{
			switch(m_pSceneObjects->getCannon()->getBallMaterial())
			{
				case 1: scene->KeyPress(FOUR, PRESSED);  break;
				case 2: scene->KeyPress(ONE, PRESSED); break;
				case 3: scene->KeyPress(TWO, PRESSED); break;
				case 4: scene->KeyPress(THREE, PRESSED); break;

				default: break;
			};
		} 
		else if(data == m_pButtons[2] || data == m_pButtons[1]) 
		{
			switch(m_pSceneObjects->getCannon()->getBallMaterial())
			{
				case 1: scene->KeyPress(TWO, PRESSED);  break;
				case 2: scene->KeyPress(THREE, PRESSED); break;
				case 3: scene->KeyPress(FOUR, PRESSED); break;
				case 4: scene->KeyPress(ONE, PRESSED); break;

				default: break;
			};
		} 
		else if(data == m_pButtons[0]) 
		{
			scene->KeyPress(W_KEY, PRESSED);
		} 
		else if(data == m_pButtons[4]) 
		{
			scene->KeyPress(S_KEY, PRESSED);
		} 
		else if(data == m_pReloadButton) 
		{
			scene->KeyPress(R_KEY, PRESSED);
		} 
		else if(data == m_pAirResistance)
		{
			if(m_pAirResistance->getTexture()->getTextureID() != m_IDs[4])
			{
				m_pAirResistance->getTexture()->setID(m_IDs[4]);
			}
			else
			{
				m_pAirResistance->getTexture()->setID(m_IDs[5]);
			}

			m_pSceneObjects->getCannon()->getProjectile()->toggleDragForce();
		}
	}
}