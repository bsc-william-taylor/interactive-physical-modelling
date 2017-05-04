
#pragma once

#include "RendererGL.h"
#include "Cannon.h"
#include "Target.h"
#include "Scene.h"
#include "Button.h"

class MainScene : public Scene, public IEvent
{
    TextureGL* backgroundTexture;
    TextureGL settingsTexture;
    TextureGL headerTexture;
    TextureGL backPlate;

    StringGL statusStrings[4];
    StringGL uiStrings[4];

    ObjectGL settingsObject;
    ObjectGL statusObject[3];
    ObjectGL headerObject;
    ObjectGL backplateObject;
    ObjectGL uiObjects[4];

    RendererGL renderer;

    Button airResistanceButton;
    Button reloadButton;
    Button quitButton;
    Button uiButtons[8];

    Cannon cannon;
    Target target;

    std::vector<GLuint> textureIDs;
    vec2 cameraPosition;
    bool reloadCannon;
public:
    MainScene();
    ~MainScene();

    void setupUI();
    void setupCannon();
    void onTriggered(void *);
    void onRequest(SceneFactory *);
    void onMousePress(int, int, int, int);
    void onKeyPress(int, int);
    void onUpdate();
    void onRender();

    std::string getMessage();
    std::string getMateralName(Material mat);

    void renderBackground(TextureGL *);
    void renderCannon(Cannon *);
    void renderTarget(Target*);
};