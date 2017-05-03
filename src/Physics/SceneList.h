
#pragma once

#include "SceneFactory.h"

class ISceneList
{
public:
    virtual ~ISceneList() {};
    virtual void onRequest(SceneFactory* factory) {}
    virtual void onCommit(SceneFactory* factory) {}
    virtual void onUpdate() = 0;
    virtual void onRender() = 0;
    virtual void onLoad() = 0;
};