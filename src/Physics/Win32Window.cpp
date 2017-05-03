
#include "Win32Window.h"

Win32Window::Win32Window() 
{
	HWND HandleDesktop = GetDesktopWindow();																
	RECT DesktopSize;

	GetWindowRect(HandleDesktop, &DesktopSize);															

	m_Sizes.h = DesktopSize.bottom/2;
	m_Sizes.w = DesktopSize.right/2;
	m_Title = "Default Title";
	m_Sizes.x = NULL;
	m_Sizes.y = NULL;
}

Win32Window::~Win32Window()
{
	wglDeleteContext(m_Context);
	wglMakeCurrent(NULL, NULL);
	DestroyWindow(m_Window);
}

void Win32Window::Initialise() 
{
	WNDCLASSEX WindowClass;

	WindowClass.hCursor			= LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	WindowClass.hIcon			= LoadIcon(NULL, MAKEINTRESOURCE(IDI_WINLOGO));
	WindowClass.hbrBackground   = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WindowClass.style		    = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
	WindowClass.cbSize			= sizeof(WNDCLASSEX);	
	WindowClass.lpszClassName	= "W";															
	WindowClass.hInstance		= GetModuleHandle(NULL);												
	WindowClass.lpfnWndProc		= WndProc;																
	WindowClass.hIconSm			= NULL;
	WindowClass.lpszMenuName	= 0;	
	WindowClass.cbClsExtra		= 0;		
	WindowClass.cbWndExtra		= 0;

	RegisterClassEx(&WindowClass);
}

bool Win32Window::onUpdate()
{
	PeekMessage(&GetMsg(), NULL, NULL, NULL, PM_REMOVE);
	
	if(GetMsg().message == WM_QUIT) 
	{
		return FALSE;
	}

	TranslateMessage(&GetMsg());
	DispatchMessage(&GetMsg());
	return TRUE;
}

LRESULT CALLBACK Win32Window::WndProc(HWND Hwnd, UINT Message, WPARAM wParam, LPARAM lParam) 
{
	switch(Message)
	{
		case WM_DESTROY: PostQuitMessage(0); return NULL;
		case WM_SIZE: glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));  break;
		
		default:
			break;
	}	

    return DefWindowProc(Hwnd, Message, wParam, lParam);
}

void Win32Window::Display(Type type) 
{
	HINSTANCE Inst = GetModuleHandle(NULL);
	DWORD Set = WS_BORDER | WS_SYSMENU | WS_MINIMIZEBOX;

	if(type == FULLSCREEN)
	{
		DEVMODE Screen;

		ZeroMemory(&Screen, sizeof(DEVMODE));

		Screen.dmSize			= sizeof(DEVMODE);
		Screen.dmPelsHeight		= m_Sizes.h;
		Screen.dmPelsWidth		= m_Sizes.w;
		Screen.dmBitsPerPel		= 32;
		Screen.dmFields			= DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

		if(ChangeDisplaySettings(&Screen, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL)
		{
			RECT rect;
		
			rect.bottom = m_Sizes.h;
			rect.right = m_Sizes.w;
			rect.left = NULL;
			rect.top = NULL;

			AdjustWindowRectEx(&rect, WS_POPUP, false, WS_EX_APPWINDOW);
		}

		m_Window = CreateWindowEx(0, "W", m_Title, WS_POPUP, m_Sizes.x, m_Sizes.y, m_Sizes.w, m_Sizes.h, 0, 0, Inst, 0);
	} 
	else
	{
		m_Window = CreateWindowEx(0, "W", m_Title, Set, m_Sizes.x, m_Sizes.y, m_Sizes.w, m_Sizes.h, 0, 0, Inst, 0);
	}

	UpdateWindow(m_Window);
	ShowWindow(m_Window, SW_SHOW);
}

void Win32Window::EnableOpenGL()
{
	PIXELFORMATDESCRIPTOR pfd;

	HDC hDC = GetDC(m_Window);
	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize			= sizeof(pfd);
	pfd.nVersion		= 1;
	pfd.cColorBits		= 32;
	pfd.cDepthBits		= 32;
	pfd.iLayerType		= PFD_MAIN_PLANE;
	pfd.dwFlags			= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType		= PFD_TYPE_RGBA;

	int iFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, iFormat, &pfd);

	m_Context = wglCreateContext(hDC);
	wglMakeCurrent(hDC, m_Context);
}

HWND& Win32Window::GetHandle()
{ 
	return m_Window; 
}

MSG& Win32Window::GetMsg()
{ 
	return m_Msg; 
}

void Win32Window::setTraits(TCHAR * Title, int x, int y, int Width, int Height)
{
	m_Title = Title;
	m_Sizes.h = Height;
	m_Sizes.w = Width;
	m_Sizes.x = x;
	m_Sizes.y = y;

    if (m_Sizes.x == Center)
    {
        m_Sizes.x = (GetSystemMetrics(SM_CXSCREEN) - Width) / 2;
    }

    if (m_Sizes.y == Center)
    {
        m_Sizes.y = (GetSystemMetrics(SM_CYSCREEN) - Height) / 2;
    }
}

