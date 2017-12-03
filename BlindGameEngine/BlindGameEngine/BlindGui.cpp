#include "stdafx.h"
#include "BlindGui.h"


void BlindGui::Init()
{
	//Get the instance handle for the window
	hInst = GetModuleHandle(0); // Store instance handle in our global variable

	winID = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr);
	
	if (!winID)
	{
		return;
	}
	STARTUPINFO sInfo;
	GetStartupInfoW(&sInfo);
	int win;
	if ((sInfo.dwFlags & STARTF_USESHOWWINDOW) != 0)
	{
		win = sInfo.wShowWindow;
	}
	win = SW_SHOWDEFAULT;
	ShowWindow(winID, win);
	UpdateWindow(winID);
}

BlindGui::BlindGui()
{
	Init();
}


BlindGui::~BlindGui()
{
}
