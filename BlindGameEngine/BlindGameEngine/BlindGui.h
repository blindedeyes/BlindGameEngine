#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
class BlindGui
{
#ifdef _WIN32
	//Windows def
#define MAX_LOADSTRING 100

	HINSTANCE hInst;                                // current instance
	WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
	WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

	HWND winID;
	// Forward declarations of functions included in this code module:
	ATOM                MyRegisterClass(HINSTANCE hInstance);
	BOOL                InitInstance(HINSTANCE, int);
	LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
#else

#endif

#ifdef LINUX //SOONTM
#endif


#ifdef _WIN32
	//Win32 def of windows form creation
private:
	//Init the window, and get the HWND
	void Init();
public:

	BlindGui();
	BlindGui(int wHeight, int wWidth);
	~BlindGui();



	//Direct cast to HWND
	operator HWND()
	{
		return winID;
	}
	//Get HWND : Returns the HWND for the window
	HWND GetHWND()
	{
		return winID;
	}

#else
#endif
};

