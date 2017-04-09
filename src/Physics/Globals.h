#pragma once 

 #include "GL_Header.h"
 
const float METRE = 64.0f;
const float M3 = METRE * METRE * METRE;
const float SECOND = 60.0f;
const float SS = SECOND * SECOND;
const float KG = 1.0f;
const float N = ( KG * METRE ) / SS;
const float CM = METRE / 100.0f;
const float CM3 = CM * CM * CM;
const float G = KG / 1000.0f;
const float DENSITY_AIR = 1.225f * ( KG / M3 );
const float DRAG_COEFICIENT = 0.47f;
const float FORCE = 1600 * N; // 1600 Newtons
const vec2 GRAVITY( 0.0f, -9.8f * N ); // Weight force

const float DENSITY[ 4 ] =
{
	7.86f * G / CM3, // iron density
	2.71f * G / CM3, // aluminium density
	8.96f * G / CM3, // copper density	
	3.44f * G / CM3  // zinc density
};

#define TARGETWIDTH 4 * METRE
#define TARGETHEIGHT 0.5 * METRE
