// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here
#include <iostream>
#include <vector>
#include <sstream>
template<typename T>
void alert(T item)
{
	//this accepts all types that supports operator << 
	std::ostringstream os;
	os << item;
	MessageBoxA(NULL, os.str().c_str(), "Refreshing Shape", MB_OK | MB_ICONINFORMATION);
}
