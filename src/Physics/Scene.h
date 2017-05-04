
#pragma once

#include "SceneFactory.h"

class Scene
{
public:
    virtual ~Scene() {}
    virtual void onRequest(SceneFactory *) {}
    virtual void onCommit(SceneFactory *) {}
    virtual void onMousePress(int, int, int, int) {}
    virtual void onMotion(float, float) {}
    virtual void onKeyPress(int, int) {}
    virtual void onUpdate() {}
    virtual void onRender() {}
    virtual void onEnter() {}
    virtual void onExit() {}
};