#include <stdio.h>
#include <string>
#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif


std::string get_window_title();