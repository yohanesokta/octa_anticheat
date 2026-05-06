#include <stdio.h>
#include <string>
#ifdef _WIN32
//  Declaration on windows32
// #pragma once

#include <windows.h>
#include <Psapi.h>
#include <shellapi.h>
#pragma comment(lib, "user32.lib");
#pragma comment(lib, "kernel32.lib");

#define WM_TRAYICON (WM_USER + 1)
#define SIZE 1024
#define ID_TRAY_EXIT 1001

#else
#include <cstdlib>
#include <cstring>

#endif


std::string get_window_title();
