
#pragma once

#include "Win32Header.h"

enum Type 
{ 
    FULLSCREEN, 
    WINDOWED 
};			

enum Location 
{ 
    Center = -1 
};			

struct Region 
{ 
    int x, y, w, h; 
};
    
class Win32Window 
{
	HGLRC m_Context;		
	HWND m_Window;			
	TCHAR * m_Title;		
	Region m_Sizes;			
	MSG m_Msg;				
public:
	Win32Window();
	~Win32Window();

	// Member Functions
	void EnableOpenGL();
	void Display(Type);
	void Initialise();
	bool onUpdate();

	void setTraits(TCHAR *, int, int, int, int);
	void setWindowTraits(Type);

	HWND& GetHandle();
	MSG& GetMsg();

private:

	static LRESULT __stdcall WndProc(HWND, UINT, WPARAM, LPARAM);	
};

using Window = Win32Window;