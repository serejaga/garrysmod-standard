#pragma once

/* Standard C/C++ headers */
#include <filesystem>

#include <iostream>
#include <fstream>

/* Windows SDK */
#define WIN32_LEAN_AND_MEAN
#include <windows.h> 

/* Garrys Mod lua */
#define DLL_EXPORT extern "C" __declspec( dllexport )

#include "../thirdparty/garrysmod/luabase.h"
#include "../thirdparty/garrysmod/luashared.h"
#include "../thirdparty/garrysmod/interface.h"

/* Module framework stuff */
#include "features.h"

#include "features/filesystem.h"
#include "features/filestream.h"

#include "framework.h"