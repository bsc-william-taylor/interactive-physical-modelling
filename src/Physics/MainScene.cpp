
#include "EventManager.h"
#include "Projectiles.h"
#include "Trajectory.h"
#include "Win32Codes.h"
#include "MainScene.h"
#include "BackEvent.h"
#include "Cannon.h"
#include "Target.h"

template<typename T>
GL_Matrix* fetchMatrix(T* object)
{
    return object->getObject()->getMatrix();
}

MainScene::MainScene() : 
    reloadCannon(false)
{
    setupUI();
    setupCannon();
}

MainScene::~MainScene()
{
}

void MainScene::onRequest(SceneFactory * factory)
{
    backgroundTexture = factory->GrabAsset<GL_Texture>("MenuBackground");
}

void MainScene::onKeyPress(int Key, int State)
{    
    auto eventManger = EventManager::get();
    auto ball = cannon.getProjectile();
    auto mass = ball->getMass();

    cannon.onKeyPress(Key, State);

    if (KEY_DOWN(ESCAPE, Key, State))
    {
        eventManger->TriggerEvent(new BackEvent(), true, this);
    }

    if (KEY_DOWN(SPACE, Key, State) && !reloadCannon)
    {
        cannon.Fire();
        reloadCannon = true;
    }

    if (KEY_DOWN(R_KEY, Key, State))
    {
        reloadCannon = false;
        cameraPosition.x = 0;
    }

    if (KEY_DOWN(W_KEY, Key, State))
    {
        ball->setMass(mass + 0.1f);
    }

    if (KEY_DOWN(S_KEY, Key, State))
    {
        ball->setMass(mass - 0.1f);
    }

    if (KEY_HOLDING(ARROW_LEFT, Key, State))
    {
        cameraPosition.x -= CAMERASPEED;
        cameraPosition.x = std::max(cameraPosition.x, 0.0f);
    }

    if (KEY_HOLDING(ARROW_RIGHT, Key, State))
    {
        cameraPosition.x += CAMERASPEED;
        cameraPosition.x = std::min(cameraPosition.x, 1720.0f);
    }
}

void MainScene::onMousePress(int key, int state, int x, int y)
{
    auto viewX = x + cameraPosition.x;
    auto viewY = y + cameraPosition.y;

    for (auto& button : uiButtons)
    {
        button.MouseState(key, state, x, y);
    }

    airResistanceButton.MouseState(key, state, x, y);
    reloadButton.MouseState(key, state, x, y);
    quitButton.MouseState(key, state, x, y);
    target.onMousePress(key, state, viewX, viewY);
}

std::string MainScene::getMateralName(Material material)
{
    switch (material)
    {
    case Material::Iron:
        return "   Iron  ";
    case Material::Aluminium:
        return "Aluminium";
    case Material::Copper:
        return "  Copper ";
    case Material::Stone:
        return "   Zinc  ";
    default:
        return " Unknown ";
    }
}

void MainScene::onUpdate()
{
    fetchMatrix(backgroundTexture)->Ortho(vec2(0, 1280), vec2(0, 720));
    fetchMatrix(backgroundTexture)->LookAt(cameraPosition);

    cannon.getStaticObject()->getMatrix()->LookAt(cameraPosition);
    cannon.getRotateObject()->getMatrix()->LookAt(cameraPosition);
    cannon.getTrajectory()->getMatrix()->LookAt(cameraPosition);
    cannon.getTrajectory()->getMatrix()->LookAt(cameraPosition);
    cannon.onUpdate();

    for (auto& proj : cannon.getProjectiles())
    {
        fetchMatrix(proj)->LookAt(cameraPosition);
    }

    target.getObject()->getMatrix()->LookAt(cameraPosition);
    target.onUpdate();

    auto ball = cannon.getProjectile();
    auto currentPosition = ball->getPosition().x;
    auto targetPosition = target.getPosition().x;
    auto startPosition = ball->getStartPos().x;
    auto distanceToTarget = ((targetPosition - startPosition) + TARGETWIDTH / 2 - (currentPosition - startPosition)) / METRE;
    auto distanceTravelled = std::to_string((currentPosition - startPosition) / METRE).append("m");
    auto missed = distanceToTarget > TARGETWIDTH / (2 * METRE) || distanceToTarget < -TARGETWIDTH / (2 * METRE);
    auto hit = ball->getPosition().y < TARGETHEIGHT / 4;

    statusStrings[0].setString(missed ? "Missed!" : hit ? "Hit!" : "");
    statusStrings[1].setString(std::to_string(abs(distanceToTarget)).append("m"));
    statusStrings[2].setString(distanceTravelled);

    uiStrings[0].setString(std::to_string((int)(ball->getMass() * 1000.0f)).append("g"));
    uiStrings[3].setString(std::to_string((int)cannon.getAngle()));
    uiStrings[2].setString(std::to_string((int)cannon.getBallMaterial()));
    uiStrings[1].setString(getMateralName(cannon.getBallMaterial()));
    
    headerTexture.setID(textureIDs[(int)cannon.getBallMaterial()-1]);
}

void MainScene::onRender()
{
    renderBackground(backgroundTexture);
    renderCannon(&cannon);
    renderTarget(&target);

    renderer.RenderTexture(&headerTexture);
    renderer.RenderTexture(quitButton.getTexture());
    renderer.RenderString(quitButton.getString());
    renderer.RenderTexture(&settingsTexture);
    renderer.RenderTexture(airResistanceButton.getTexture());
    renderer.RenderTexture(&backPlate);

    if (reloadCannon)
    {
        renderer.RenderTexture(reloadButton.getTexture());
    }

    for (auto& status : statusStrings)
    {
        renderer.RenderString(&status);
    }

    for (auto& uiString : uiStrings)
    {
        renderer.RenderString(&uiString);
    }

    for (auto& uiButton : uiButtons)
    {
        renderer.RenderTexture(uiButton.getTexture());
    }
}

void MainScene::renderBackground(GL_Texture * background)
{
    renderer.RenderTexture(background);
}

void MainScene::renderCannon(Cannon * cannon)
{
    for (auto& projectile : cannon->getProjectiles())
    {
        if (projectile->hasFired())
        {
            auto position = projectile->getPosition() + projectile->getVelocity();
            cannon->getTrajectory()->PlotPoint(position.x, position.y, 5.0f);
            cannon->getTrajectory()->onRender();
            renderer.RenderTexture(projectile->getSprite());
        }
    }

    for (auto& texture : cannon->getTextures())
    {
        renderer.RenderTexture(texture);
    }
}

void MainScene::renderTarget(Target * pTarget)
{
    renderer.RenderTexture(pTarget->getSprite());
}

std::string MainScene::getMessage()
{
    return "Back button pressed";
}

void MainScene::onTriggered(void * data)
{
    auto scenes = SceneManager::get();
    auto ball = cannon.getProjectile();

    if (data == &quitButton)
    {
        scenes->SwitchTo((int)SceneStates::MainMenu);
    }

    else if (data == &uiButtons[3])
    {
        onKeyPress(ARROW_UP, PRESSED);
    }
    else if (data == &uiButtons[7])
    {
        onKeyPress(ARROW_DOWN, PRESSED);
    }
    else if (data == &uiButtons[6] || data == &uiButtons[5])
    {
        switch (cannon.getBallMaterial())
        {
        case Material::Iron:
            onKeyPress(FOUR, PRESSED);
            break;
        case Material::Aluminium:
            onKeyPress(ONE, PRESSED);
            break;
        case Material::Copper:
            onKeyPress(TWO, PRESSED);
            break;
        case Material::Stone:
            onKeyPress(THREE, PRESSED);
            break;
        default:
            break;
        };
    }
    else if (data == &uiButtons[2] || data == &uiButtons[1])
    {
        switch (cannon.getBallMaterial())
        {
        case Material::Iron:
            onKeyPress(TWO, PRESSED);
            break;
        case Material::Aluminium:
            onKeyPress(THREE, PRESSED);
            break;
        case Material::Copper:
            onKeyPress(FOUR, PRESSED);
            break;
        case Material::Stone:
            onKeyPress(ONE, PRESSED);
            break;
        default:
            break;
        };
    }
    else if (data == &uiButtons[0])
    {
        onKeyPress(W_KEY, PRESSED);
    }
    else if (data == &uiButtons[4])
    {
        onKeyPress(S_KEY, PRESSED);
    }
    else if (data == &reloadButton)
    {
        onKeyPress(R_KEY, PRESSED);
    }
    else if (data == &airResistanceButton)
    {
        const auto& buttonTexture = airResistanceButton.getTexture();
        const auto textureID = buttonTexture->getTextureID();
        buttonTexture->setID(textureIDs[textureID != textureIDs[4] ? 4 : 5]);
        ball->toggleDragForce();
    }
}

void MainScene::setupCannon()
{
    cannon.Initialise();
    cannon.getProjects()->SetMaterial(Material::Iron);

    target.Setup(vec2(1000, 200));
}

void MainScene::setupUI()
{
    auto textureManager = TextureManagerGL::get();
    auto horizontalX = std::array<float, 4>{ 1150.0f, 1143.0f, 1160.0f, 1160.0f };
    auto positions = std::array<float, 8> { 
        467.0f, 482.0f, 497.0f, 512.0f,
        467.0f, 482.0f, 497.0f, 512.0f 
    };

    for (auto i = 0, y = 467; i < 4; i++, y += 15)
    {
        uiObjects[i].setOrtho2D(vec4(0, 0, 1280, 720));
        uiObjects[i].setPosition(vec2(horizontalX[i], y));
        uiObjects[i].setSize(vec2(18, 18));

        uiStrings[i].PrepareFont("data/version.xml", "data/version.png");
        uiStrings[i].setParameters(&uiObjects[i]);
        uiStrings[i].setColour(1, 1, 1, 1);
        uiStrings[i].setString("0");
        uiStrings[i].Prepare();
    }

    for (auto i = 0, y = 380; i < 4; i++, y += 15)
    {
        statusObject[i].setOrtho2D(vec4(0, 0, 1280, 720));
        statusObject[i].setPosition(vec2(1125, y));
        statusObject[i].setSize(vec2(15, 15));

        statusStrings[i].PrepareFont("data/version.xml", "data/version.png");
        statusStrings[i].setParameters(&statusObject[i]);
        statusStrings[i].setString("0");
        statusStrings[i].setColour(1, 1, 1, 1);
        statusStrings[i].Prepare();
    }

    airResistanceButton.SetTexture("data/img/enabled.png");
    airResistanceButton.SetPosition("", vec2(1125, 428), vec2(78, 14));
    airResistanceButton.OnPress(this);

    reloadButton.OnPress(this);
    reloadButton.SetTexture("data/img/reload.png");
    reloadButton.SetPosition("", vec2(1126, 526), vec2(78, 14));

    settingsObject.setOrtho2D(vec4(0, 0, 1280, 720));
    settingsObject.setPosition(vec2(1000, 358));
    settingsObject.setSize(vec2(228, 96));

    settingsTexture.setTexture("data/img/status.png", GL_CLAMP_TO_EDGE);
    settingsTexture.setParameters(&settingsObject);
    settingsTexture.Prepare();

    for (int i = 0; i < 8; i++)
    {
        uiButtons[i].OnPress(this);
        uiButtons[i].SetTexture(i < 4 ? "data/img/plus.png" : "data/img/minus.png");
        uiButtons[i].SetPosition("", vec2(i < 4 ? 1190 : 1125, positions[i]), vec2(14, 13));
    }

    headerObject.setOrtho2D(vec4(0, 0, 1280, 720));
    headerObject.setPosition(vec2(1000, 550));
    headerObject.setSize(vec2(228, 96));

    headerTexture.setTexture("data/img/header1.png", GL_CLAMP_TO_EDGE);
    headerTexture.setParameters(&headerObject);
    headerTexture.Prepare();

    quitButton.SetPosition("Back", vec2(25, 600), vec2(200, 50));
    quitButton.OnPress(this);

    backplateObject.setOrtho2D(vec4(0, 0, 1280, 720));
    backplateObject.setPosition(vec2(1000, 454));
    backplateObject.setSize(vec2(228, 96));

    backPlate.setTexture("data/img/console.png", GL_CLAMP_TO_EDGE);
    backPlate.setParameters(&backplateObject);
    backPlate.Prepare();

    textureIDs.push_back(headerTexture.getTextureID());
    textureIDs.push_back(textureManager->CreateTexture("data/img/header2.png", GL_CLAMP_TO_EDGE)->m_ID);
    textureIDs.push_back(textureManager->CreateTexture("data/img/header3.png", GL_CLAMP_TO_EDGE)->m_ID);
    textureIDs.push_back(textureManager->CreateTexture("data/img/header4.png", GL_CLAMP_TO_EDGE)->m_ID);
    textureIDs.push_back(textureManager->CreateTexture("data/img/disabled.png", GL_CLAMP_TO_EDGE)->m_ID);
    textureIDs.push_back(textureManager->CreateTexture("data/img/enabled.png", GL_CLAMP_TO_EDGE)->m_ID);
}