#pragma once 

#include "GL_Header.h"
#include "SceneManager.h"
#include "Win32System.h"
#include "Win32Timer.h"
#include <array>

#ifdef WINDOW_MAIN
    #define MAIN WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
#else
    #define MAIN main(int, const char*[])
#endif

enum class SceneStates
{
    MainMenu,
    MainScene
};

const auto FULCRUM_X = 144.0f;
const auto FULCRUM_Y = 75.0f;
const auto CAMERASPEED = 10.0f;
const auto METRE = 64.0f;
const auto M3 = METRE * METRE * METRE;
const auto SECOND = 60.0f;
const auto SS = SECOND * SECOND;
const auto KG = 1.0f;
const auto N = (KG * METRE) / SS;
const auto CM = METRE / 100.0f;
const auto CM3 = CM * CM * CM;
const auto G = KG / 1000.0f;
const auto DENSITY_AIR = 1.225f * (KG / M3);
const auto DRAG_COEFICIENT = 0.47f;
const auto FORCE = 1600.0f * N; // 1600 Newtons
const auto GRAVITY = vec2(0.0f, -9.8f * N); // Weight force
const auto TARGETWIDTH = 4.0f * METRE;
const auto TARGETHEIGHT = 0.5f * METRE;
const auto DENSITY = std::array<float, 4>
{
    7.86f * G / CM3, // iron density
    2.71f * G / CM3, // aluminium density
    8.96f * G / CM3, // copper density	
    3.44f * G / CM3  // zinc density
};

class Demo
{
    unsigned int framerate;
    Win32System system;
    Win32Timer timer;
public:
    Demo();
    ~Demo();

    void execute();
    void setFrameRate(unsigned int);
    void setupStates();
    void setupWindow();
};

