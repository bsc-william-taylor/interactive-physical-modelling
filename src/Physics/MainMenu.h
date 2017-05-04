
#pragma once

#include "PlayEvent.h"
#include "Scene.h"
#include "TextureGL.h"
#include "RendererGL.h"
#include "Button.h"

class MainMenu : public Scene
{
    RendererGL renderer;
    TextureGL backgroundTexture;
    ObjectGL backgroundObject;
    ObjectGL titleObject;
    ObjectGL m_Objects[3];
    StringGL m_Banners[3];
    StringGL title;

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