#ifdef _WIN32
#include "window_manager.h"

void get_process_name(HWND hwnd, char* output, DWORD size) {
    DWORD pid;
    GetWindowThreadProcessId(hwnd,&pid);
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!hProcess) {
        // Is end of strings
        output[0] = '\0';
        return;
    }

    char path[MAX_PATH];
    DWORD path_size = MAX_PATH;
    if (QueryFullProcessImageNameA(hProcess,0,path,&path_size)){
        char *lastSlash = strrchr(path, '\\');    
        if (lastSlash) {
            strcpy(output,lastSlash + 1);
        } else {
            strcpy(output,path);
        }
    } else {
        output[0] = '\0';
    }

    CloseHandle(hProcess);
}


void get_active_window_titlebar(char *output, DWORD size) {
    HWND hwnd = GetForegroundWindow();
    if (!hwnd) {
        strcpy(output,"tidak ada active window");
        return;
    }

    char title[512];
    GetWindowTextA(hwnd,title,sizeof(title));
    
    char processName[MAX_PATH];
    get_process_name(hwnd,processName,sizeof(processName));
    if (strlen(title) == 0) {
        if (strlen(processName) > 0) {
            strcpy(output,processName);
        } else {
            strcpy(output,"Window Tidak Terdeteksi!");
        }
        return;
    }

    if (strlen(processName) > 0) {
        snprintf(output,size,"%s [%s]",title,processName);
    } else {
        strcpy(output,title);
    }
    return;
}


std::string get_window_title() {
    char result[2*SIZE];
    get_active_window_titlebar(result,sizeof(result));
    return result;
}

#endif