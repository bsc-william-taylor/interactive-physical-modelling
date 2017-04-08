
#include "Demo.h"

#define _RELEASE_MODE

// Main Function
UINT PhysicsMain()
{
	Demo * PhsyicsDemo = new Demo();
	PhsyicsDemo->Execute();
	delete PhsyicsDemo;
	return NULL;
}

/* This is just a simple alteration so when we change from a console
   application to a windows application the code has already been 
   written for us.													*/
#ifndef _RELEASE_MODE

int main(int argc, const char * argv[])
{
	return PhysicsMain();
}

#else

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE pInstance, LPSTR str, INT show)
{
	return PhysicsMain();
}

#endif