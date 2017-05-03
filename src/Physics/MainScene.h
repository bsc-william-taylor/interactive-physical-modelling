
#pragma once

#include "GL_Renderer.h"
#include "Cannon.h"
#include "Target.h"
#include "Scene.h"
#include "Button.h"

class MainScene : public Scene, public IEvent
{
    GL_Texture* backgroundTexture;
    GL_Texture settingsTexture;
    GL_Texture headerTexture;
    GL_Texture backPlate;

    GL_String statusStrings[4];
    GL_String uiStrings[4];

    GL_Object settingsObject;
    GL_Object statusObject[3];
    GL_Object headerObject;
    GL_Object backplateObject;
    GL_Object uiObjects[4];

    GL_Renderer renderer;

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

    void renderBackground(GL_Texture *);
    void renderCannon(Cannon *);
    void renderTarget(Target*);
};