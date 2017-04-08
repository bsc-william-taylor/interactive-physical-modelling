#pragma once 

 #include "GL_Header.h"
 
/*
+	*--* INSTRUCTIONS *--*
+	SCALE: 1 meter = 64 pixels and 1 second = 60 frames;
+	
+	TEST: 40 meters/second is 42.6 pixels/frame
+	
+	The screen currently has 800 pixels width, the cannon has 235
+	so the distance on the screen is 565 pixels about 8.82 metres 
+
+	At 45degrees with a velocity of 42.6 pixels/frame^2 the projectile
+	travels 1107 pixels in 38 frames which means 17.3m in 0.61s
+*/
 
/*
	The standard scale for meter to pixels
*/
const float METRE = 64.0f;
/*
+	The system runs at 60 frames/second which means
+	we have 1 frame at every 1 / 60 = 0.016 seconds. 
+	In other words, 1 second has 60 frames, this is the most important part.
+*/
const float SECOND = 60.0f;
 
/*
+	For testing purposes, a ball with a velocity of 40 m/s would have
+	40 * ( 64 pixels / 60 frames ) = 42 pixels/frame
*/
const float INITIAL_SPEED = 42.6f;

/*
+	Gravity is 10 Newtons and points downwards
+*/
const vec2 GRAVITY = vec2( 0.0f, -9.8f * ( METRE / ( SECOND * SECOND ) ) );
 