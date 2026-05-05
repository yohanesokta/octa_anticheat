#include "include/httplib.h"
#include <stdio.h>
#include <cstdlib>
#include <string>
#include "window_manager.h"

#define SERVER_ADDRESS "localhost"
#define SERVER_PORT 9013

using namespace httplib;
Server svr;

void listen_server() {

    svr.Get("/status", [](const Request &req, Response &res) {
        std::string window_title =  get_window_title();
        std::string json_output = std::string("{ 'active_window' : '") + window_title + "'}";
        res.set_content(json_output, "application/json" );
    });
    
    printf("running server at %s:%i\n",SERVER_ADDRESS,SERVER_PORT);
    svr.listen(SERVER_ADDRESS, SERVER_PORT);
} 


#ifdef _WIN32
    #include "res/resource.h"
    #include <threads.h>


    std::thread server_thread(listen_server);

    NOTIFYICONDATA nid;
    LRESULT CALLBACK WindowProcess(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
        switch (msg)
        {
        case WM_TRAYICON:
            if (lParam == WM_RBUTTONUP ) {
                POINT pt;
                GetCursorPos(&pt);

                HMENU hMenu = CreatePopupMenu();
                AppendMenu(hMenu,MF_STRING,ID_TRAY_EXIT,"Matikan");

                SetForegroundWindow(hwnd);

                TrackPopupMenu(
                    hMenu,
                    TPM_BOTTOMALIGN,
                    pt.x,
                    pt.y,
                    0,
                    hwnd,
                    NULL
                );
                DestroyMenu(hMenu);
            }
            break;
        case WM_COMMAND:
            if (LOWORD(wParam) == ID_TRAY_EXIT) {
                svr.stop();
                server_thread.join();
                Shell_NotifyIcon(NIM_DELETE,&nid);
                PostQuitMessage(0);
            }
            break;
        case WM_DESTROY:
            svr.stop();
            server_thread.join();
            Shell_NotifyIcon(NIM_DELETE,&nid);
            PostQuitMessage(0);
            break;
        default:
            break;
        }
        return DefWindowProc(hwnd,msg,wParam,lParam);
    }

    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
    {
        const char CLASS_NAME[] = "octa-anticheat";
        HANDLE Mutex = CreateMutex(NULL,TRUE,"Global\\OctaAntiCheatMutex");

        if (GetLastError() == ERROR_ALREADY_EXISTS) {
            MessageBoxA(NULL,
                "Program Sudah Berjalan, Tidak Perlu Dijalankan Lagi",
                "Woyyyy Astaga",
                MB_OK | MB_ICONWARNING
            );
            return 0;
        }

        WNDCLASS wc = {0}; 
        wc.lpfnWndProc = WindowProcess;
        wc.hInstance = hInstance;
        wc.lpszClassName = CLASS_NAME;

        RegisterClass(&wc);

        HWND hwnd = CreateWindowEx(
            0,
            CLASS_NAME,
            "octa-anticheat-service",
            0,
            0,0,0,0,
            NULL,
            NULL,
            hInstance,
            NULL
        );

        nid.cbSize = sizeof(NOTIFYICONDATA);
        nid.hWnd = hwnd;
        nid.uID = 1;
        nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
        nid.uCallbackMessage = WM_TRAYICON;
        nid.hIcon = (HICON)LoadImage(
            NULL,
            "icon.ico",
            IMAGE_ICON,
            16,16,
            LR_LOADFROMFILE);
        lstrcpy(nid.szTip, "Octa Anticheat Service");
        Shell_NotifyIcon(NIM_ADD, &nid);
        MSG msg;
        while (GetMessage(&msg,NULL,0,0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        return 0;
    }
#else
    int main() {
        listen_server();
        return 0;
    }
#endif