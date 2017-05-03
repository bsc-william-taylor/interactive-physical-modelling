
#pragma once

#include "GL_Renderer.h"
#include "Cannon.h"
#include "Target.h"
#include "Scene.h"
#include "Button.h"

class MainScene : public Scene, public IEvent
{
    GL_Texture* backgroundTexture;
    GL_Texture m_pSettingsTexture;
    GL_Texture m_pHeaderTexture;
    GL_Texture m_pBackPlate;

    GL_String* m_pStatusStrings[4];
    GL_String* m_pStrings[4];

    GL_Object m_pSettingsObject;
    GL_Object m_pStatusObjects[3];
    GL_Object m_pHeaderObject;
    GL_Object m_pBackObject;
    GL_Object m_pObjects[4];

    GL_Renderer renderer;

    Button m_pAirResistance;
    Button m_pReloadButton;
    Button m_pQuitButton;
    Button buttons[8];

    Cannon m_pCannon;
    Target m_pTarget;

    std::vector<GLuint> m_IDs;
    vec2 m_Camera;
    bool m_Reload;
public:
    MainScene();
    ~MainScene();

    Target* getTarget();
    Cannon* getCannon();

    bool mustReload();

    std::string getMessage();
    void onTriggered(void *);

    void onRequest(SceneFactory *);
    void onMousePress(int, int, int, int);
    void onKeyPress(int, int);
    void onUpdate();
    void onRender();

    void RenderBackground(GL_Texture *);
    void RenderCannon(Cannon *);
    void RenderTarget(Target*);
};