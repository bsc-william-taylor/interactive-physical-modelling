
/* -------------------------------------------------
  
 @Filename  : GL_Array.cpp
 @author	: William Taylor
 @date		: 14/02/2014
 @purpose	: A Common header file for all
			  GL_Headers

 ------------------------------------------------- */

#pragma once

#define GLM_FORCE_RADIANS

#include "Win32Header.h"

#include "freeimage/include/freeimage.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/glm.hpp"

#include "tinyxml2/tinyxml2.h"
#include "glew.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#pragma comment(lib, "tinyxml2.lib")
#pragma comment(lib, "freeimage.lib")
#pragma comment(lib, "glew32.lib")

#define PI 3.14159265359;
#define RADIAN(v) (v / 180.0f) * PI


using namespace glm;
using std::vector;
using std::map;