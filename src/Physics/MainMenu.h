
#pragma once

#include "PlayEvent.h"
#include "Scene.h"
#include "GL_Texture.h"
#include "GL_Renderer.h"
#include "Button.h"

class MainMenu : public Scene
{
    GL_Renderer renderer;
    GL_Texture backgroundTexture;
    GL_Object backgroundObject;
    GL_Object titleObject;
    GL_Object m_Objects[3];
    GL_String m_Banners[3];
    GL_String title;

    Button playButton;
public:
    MainMenu();
    ~MainMenu();

    void onMousePress(int, int, int, int);
    void onCommit(SceneFactory *);
    void onKeyPress(int, int);
    void onUpdate();
    void onRender();

    void setupLabels();
    void setupButtons();
    void setupImages();
};