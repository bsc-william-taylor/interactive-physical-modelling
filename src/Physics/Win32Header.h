
#pragma once

#define DIRECTINPUT_VERSION 0x0800

#include <Windows.h>
#include <dinput.h>	
#include <algorithm>
#include <iostream>														
#include <stdarg.h>		
#include "glew.h"
#include <gl\GLU.h>	
#include <dshow.h>
#include <Mfidl.h>
#include <fcntl.h>	
#include <gl\gl.h>
#include <Psapi.h>
#include <string>													
#include <vector>
#include <time.h>
#include <Evr.h>
#include <io.h>
#include <list>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "glu32.lib")	
#pragma comment(lib, "strmiids")

using std::vector;

template<typename T>
void SAFE_RELEASE(T*& pointer)
{
    if (pointer != nullptr)
    {
        delete pointer;
        pointer = nullptr;
    }
}

template<typename T>
void SAFE_RELEASE_SINGLETON(T* pointer)
{
    auto copy = pointer;
    SAFE_RELEASE(copy);
}