// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN             

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//Direct X Math library
#include <DirectXMath.h>

#include <d3d11.h>

// TODO: reference additional headers your program requires here
#include "Mesh.h"
#include "DataManager.h"
#include "BlindRenderer.h"
#include "BlindEngine.h"