
#include "EventManager.h"
#include "Win32Codes.h"
#include "MainScene.h"
#include "BackEvent.h"
#include "Cannon.h"
#include "Target.h"
#include "Trajectory.h"
#include "Projectiles.h"

MainScene::MainScene()
{
    float x[4] = { 1150, 1143, 1160, 1160 };
    float y = 467;
    for (int i = 0; i < 4; i++)
    {
        m_pObjects[i].setOrtho2D(vec4(0, 0, 1280, 720));
        m_pObjects[i].setPosition(vec2(x[i], y));
        m_pObjects[i].setSize(vec2(18, 18));

        m_pStrings[i] = new GL_String("data/version.xml", "data/version.png");
        m_pStrings[i]->setParameters(&m_pObjects[i]);
        m_pStrings[i]->setColour(1, 1, 1, 1);
        m_pStrings[i]->setString("0");
        m_pStrings[i]->Prepare();

        y += 15;
    }

    float y2 = 380;

    for (int i = 0; i < 4; i++)
    {
        m_pStatusObjects[i].setOrtho2D(vec4(0, 0, 1280, 720));
        m_pStatusObjects[i].setPosition(vec2(1125, y2));
        m_pStatusObjects[i].setSize(vec2(15, 15));

        m_pStatusStrings[i] = new GL_String("data/version.xml", "data/version.png");
        m_pStatusStrings[i]->setParameters(&m_pStatusObjects[i]);
        m_pStatusStrings[i]->setString("0");
        m_pStatusStrings[i]->setColour(1, 1, 1, 1);
        m_pStatusStrings[i]->Prepare();

        y2 += 15;
    }

    m_pAirResistance.SetTexture("data/img/enabled.png");
    m_pAirResistance.SetPosition("", vec2(1125, 428), vec2(78, 14));
    m_pAirResistance.OnPress(this);

    m_pReloadButton.OnPress(this);
    m_pReloadButton.SetTexture("data/img/reload.png");
    m_pReloadButton.SetPosition("", vec2(1126, 526), vec2(78, 14));

    m_pSettingsObject.setOrtho2D(vec4(0, 0, 1280, 720));
    m_pSettingsObject.setPosition(vec2(1000, 358));
    m_pSettingsObject.setSize(vec2(228, 96));

    m_pSettingsTexture.setTexture("data/img/status.png", GL_CLAMP_TO_EDGE);
    m_pSettingsTexture.setParameters(&m_pSettingsObject);
    m_pSettingsTexture.Prepare();

    float position[] = {
        467, 482, 497, 512,
        467, 482, 497, 512
    };

    for (int i = 0; i < 8; i++)
    {

        buttons[i].OnPress(this);

        if (i < 4)
        {
            buttons[i].SetTexture("data/img/plus.png");
            buttons[i].SetPosition("", vec2(1190, position[i]), vec2(14, 13));
        }
        else
        {
            buttons[i].SetTexture("data/img/minus.png");
            buttons[i].SetPosition("", vec2(1125, position[i]), vec2(14, 13));
        }
    }

    m_pHeaderObject.setOrtho2D(vec4(0, 0, 1280, 720));
    m_pHeaderObject.setPosition(vec2(1000, 550));
    m_pHeaderObject.setSize(vec2(228, 96));

    m_pHeaderTexture.setTexture("data/img/header1.png", GL_CLAMP_TO_EDGE);
    m_pHeaderTexture.setParameters(&m_pHeaderObject);
    m_pHeaderTexture.Prepare();

    m_pQuitButton.SetPosition("Back", vec2(25, 600), vec2(200, 50));
    m_pQuitButton.OnPress(this);

    m_pBackObject.setOrtho2D(vec4(0, 0, 1280, 720));
    m_pBackObject.setPosition(vec2(1000, 454));
    m_pBackObject.setSize(vec2(228, 96));

    m_pBackPlate.setTexture("data/img/console.png", GL_CLAMP_TO_EDGE);
    m_pBackPlate.setParameters(&m_pBackObject);
    m_pBackPlate.Prepare();

    m_IDs.push_back(m_pHeaderTexture.getTextureID());
    m_IDs.push_back(GL_TextureManager::get()->CreateTexture("data/img/header2.png", GL_CLAMP_TO_EDGE)->m_ID);
    m_IDs.push_back(GL_TextureManager::get()->CreateTexture("data/img/header3.png", GL_CLAMP_TO_EDGE)->m_ID);
    m_IDs.push_back(GL_TextureManager::get()->CreateTexture("data/img/header4.png", GL_CLAMP_TO_EDGE)->m_ID);
    m_IDs.push_back(GL_TextureManager::get()->CreateTexture("data/img/disabled.png", GL_CLAMP_TO_EDGE)->m_ID);
    m_IDs.push_back(GL_TextureManager::get()->CreateTexture("data/img/enabled.png", GL_CLAMP_TO_EDGE)->m_ID);


    m_pCannon.Initialise();
    m_pCannon.getProjects()->SetMaterial(Material::IRON);
    m_pTarget.Setup(vec2(1000, 200));
    m_Reload = false;
}

MainScene::~MainScene()
{
    for (int i = 0; i < 4; i++)
    {
        SAFE_RELEASE(m_pStrings[i]);
    }
}

void MainScene::onRequest(SceneFactory * factory)
{
    backgroundTexture = factory->GrabAsset<GL_Texture>("MenuBackground");
}

void MainScene::onKeyPress(int Key, int State)
{
    auto events = EventManager::get();

    if (KEY_DOWN(ESCAPE, Key, State))
    {
        events->TriggerEvent(new BackEvent(), true, this);
    }
    else
    {
        m_pCannon.onKeyPress(Key, State);

        if (Key == SPACE && State == PRESSED && !m_Reload)
        {
            m_pCannon.Fire();
            m_Reload = true;
        }

        if (Key == R_KEY && State == PRESSED)
        {
            m_Reload = false;

            m_Camera.x = 0;
        }

        if (Key == W_KEY && State == PRESSED)
        {
            float mass = m_pCannon.getProjectile()->getMass() + 0.1f;
            m_pCannon.getProjectile()->setMass(mass);
        }

        if (Key == S_KEY && State == PRESSED)
        {
            float mass = m_pCannon.getProjectile()->getMass() - 0.1f;
            m_pCannon.getProjectile()->setMass(mass);

        }

        if (Key == ARROW_LEFT)
        {
            m_Camera.x -= CAMERASPEED;

            if (m_Camera.x < 0)
            {
                m_Camera.x = 0.0f;
            }
        }
        else if (Key == ARROW_RIGHT)
        {
            m_Camera.x += CAMERASPEED;

            if (m_Camera.x > 1720)
            {
                m_Camera.x = 1720;
            }
        }
    }
}

void MainScene::onMousePress(int key, int state, int x, int y)
{
    for (int i = 0; i < 8; i++)
    {
        buttons[i].MouseState(key, state, x, y);
    }

    m_pAirResistance.MouseState(key, state, x, y);
    m_pReloadButton.MouseState(key, state, x, y);
    m_pQuitButton.MouseState(key, state, x, y);
    m_pTarget.onMousePress(key, state, x + m_Camera.x, y + m_Camera.y);
}

void MainScene::onUpdate()
{
    backgroundTexture->getObject()->getMatrix()->Ortho(vec2(0, 1280), vec2(0, 720));
    backgroundTexture->getObject()->getMatrix()->LookAt(m_Camera);
    m_pCannon.getStaticObject()->getMatrix()->LookAt(m_Camera);
    m_pCannon.getRotateObject()->getMatrix()->LookAt(m_Camera);
    m_pTarget.getObject()->getMatrix()->LookAt(m_Camera);
    m_pCannon.getTrajectory()->getMatrix()->LookAt(m_Camera);

    auto& vec = m_pCannon.getProjectiles();

    for (auto iterator = vec.begin(); iterator != vec.end(); ++iterator)
    {
        (*iterator)->getObject()->getMatrix()->LookAt(m_Camera);
    }

    m_pCannon.getTrajectory()->getMatrix()->LookAt(m_Camera);
    m_pCannon.onUpdate();
    m_pTarget.onUpdate();

    Projectile* pBall = getCannon()->getProjectile();

    std::string weight = std::to_string(int(pBall->getMass() * 1000.0f)).append("g");
    std::string angle = std::to_string((int)getCannon()->getAngle());
    std::string num = std::to_string((int)getCannon()->getBallMaterial());

    m_pStrings[0]->setString(weight);
    m_pStrings[3]->setString(angle);
    m_pStrings[2]->setString(num);

    switch (getCannon()->getBallMaterial())
    {
    case Material::IRON: m_pStrings[1]->setString("   Iron  ");  m_pHeaderTexture.setID(m_IDs[0]); break;
    case Material::ALUMINIUM: m_pStrings[1]->setString("Aluminium"); m_pHeaderTexture.setID(m_IDs[1]); break;
    case Material::COPPER: m_pStrings[1]->setString("  Copper ");  m_pHeaderTexture.setID(m_IDs[2]); break;
    case Material::STONE: m_pStrings[1]->setString("   Zinc  "); m_pHeaderTexture.setID(m_IDs[3]); break;

    default:
        break;
    }

    float ballX = pBall->getPosition().x;
    float ballStartX = pBall->getStartPos().x;
    float targetX = getTarget()->getPosition().x;
    float distTarget = ((targetX - ballStartX) + TARGETWIDTH / 2 - (ballX - ballStartX)) / METRE;

    std::string distance = std::to_string((ballX - ballStartX) / METRE).append("m");
    std::string distTargetStr = std::to_string(abs(distTarget)).append("m");

    m_pStatusStrings[1]->setString(distTargetStr);
    m_pStatusStrings[2]->setString(distance);

    if (distTarget > TARGETWIDTH / (2 * METRE) || distTarget < -TARGETWIDTH / (2 * METRE))
    {
        m_pStatusStrings[0]->setString("Missed!");
    }
    else
    {
        if (pBall->getPosition().y < TARGETHEIGHT / 4)
        {
            m_pStatusStrings[0]->setString("Hit!");
        }
    }
}

void MainScene::onRender()
{
    RenderBackground(backgroundTexture);
    RenderCannon(&m_pCannon);
    RenderTarget(&m_pTarget);

    renderer.RenderTexture(&m_pHeaderTexture);
    renderer.RenderTexture(m_pQuitButton.getTexture());
    renderer.RenderString(m_pQuitButton.getString());
    renderer.RenderTexture(&m_pSettingsTexture);
    renderer.RenderTexture(m_pAirResistance.getTexture());
    renderer.RenderTexture(&m_pBackPlate);

    if (mustReload())
    {
        renderer.RenderTexture(m_pReloadButton.getTexture());
    }

    for (int i = 0; i < 3; i++)
    {
        renderer.RenderString(m_pStatusStrings[i]);
    }

    for (int i = 0; i < 4; i++)
    {
        renderer.RenderString(m_pStrings[i]);
    }

    for (int i = 0; i < 8; i++)
    {
        renderer.RenderTexture(buttons[i].getTexture());
    }
}

bool MainScene::mustReload()
{
    return m_Reload;
}

Cannon* MainScene::getCannon()
{
    return &m_pCannon;
}

Target* MainScene::getTarget()
{
    return &m_pTarget;
}

// Member Functions
void MainScene::RenderBackground(GL_Texture * background)
{
    // Background is just a texture so we just render it haha :P
    renderer.RenderTexture(background);
}

void MainScene::RenderCannon(Cannon * cannon)
{
    // Get all projectiles in the scene
    vector<Projectile *>& vec = cannon->getProjectiles();
    for (auto iterator = vec.begin(); iterator != vec.end(); ++iterator)
    {
        // If its been fired draw the projectile.
        if ((*iterator)->hasFired())
        {
            auto position = (*iterator)->getPosition() + (*iterator)->getVelocity();

            cannon->getTrajectory()->PlotPoint(position.x, position.y, 5.0f);
            cannon->getTrajectory()->onRender();

            renderer.RenderTexture((*iterator)->getSprite());
        }
    }

    // Render the cannon itself
    std::vector<GL_Texture *>& textures = cannon->getTextures();
    for (auto i = textures.begin(); i != textures.end(); ++i)
    {
        renderer.RenderTexture((*i));
    }
}

void MainScene::RenderTarget(Target * pTarget)
{
    renderer.RenderTexture(pTarget->getSprite());
}

std::string MainScene::getMessage()
{
    return("Back button pressed");
}

void MainScene::onTriggered(void * data)
{
    if (data == &m_pQuitButton)
    {
        SceneManager::get()->SwitchTo((int)SceneStates::MainMenu);
    }
    else
    {
        auto scene = SceneManager::get()->getCurrent();

        Projectile* pBall = getCannon()->getProjectile();

        if (data == &buttons[3])
        {
            scene->onKeyPress(ARROW_UP, PRESSED);
        }
        else if (data == &buttons[7])
        {
            scene->onKeyPress(ARROW_DOWN, PRESSED);
        }
        else if (data == &buttons[6] || data == &buttons[5])
        {
            switch (getCannon()->getBallMaterial())
            {
            case Material::IRON: scene->onKeyPress(FOUR, PRESSED);  break;
            case Material::ALUMINIUM: scene->onKeyPress(ONE, PRESSED); break;
            case Material::COPPER: scene->onKeyPress(TWO, PRESSED); break;
            case Material::STONE: scene->onKeyPress(THREE, PRESSED); break;

            default:
                break;
            };
        }
        else if (data == &buttons[2] || data == &buttons[1])
        {
            switch (getCannon()->getBallMaterial())
            {
            case Material::IRON: scene->onKeyPress(TWO, PRESSED);  break;
            case Material::ALUMINIUM: scene->onKeyPress(THREE, PRESSED); break;
            case Material::COPPER: scene->onKeyPress(FOUR, PRESSED); break;
            case Material::STONE: scene->onKeyPress(ONE, PRESSED); break;

            default:
                break;
            };
        }
        else if (data == &buttons[0])
        {
            scene->onKeyPress(W_KEY, PRESSED);
        }
        else if (data == &buttons[4])
        {
            scene->onKeyPress(S_KEY, PRESSED);
        }
        else if (data == &m_pReloadButton)
        {
            scene->onKeyPress(R_KEY, PRESSED);
        }
        else if (data == &m_pAirResistance)
        {
            if (m_pAirResistance.getTexture()->getTextureID() != m_IDs[4])
            {
                m_pAirResistance.getTexture()->setID(m_IDs[4]);
            }
            else
            {
                m_pAirResistance.getTexture()->setID(m_IDs[5]);
            }

            getCannon()->getProjectile()->toggleDragForce();
        }
    }
}