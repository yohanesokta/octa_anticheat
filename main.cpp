#include "include/httplib.h"
#include <stdio.h>
#include <cstdlib>
#include <string>
#include "window_manager.h"

#define SERVER_ADDRESS "localhost"
#define SERVER_PORT 9013

using namespace httplib;

void listen_server() {
    Server svr;
    svr.Get("/status", [](const Request &req, Response &res) {
        std::string window_title =  get_window_title();
        std::string json_output = std::string("{ 'active_window' : '") + window_title + "'}";
        res.set_content(json_output, "application/json" );
    });
    
    printf("running server at %s:%i\n",SERVER_ADDRESS,SERVER_PORT);
    svr.listen(SERVER_ADDRESS, SERVER_PORT);
}


#ifdef _WIN32
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
    {
        listen_server();
        return 0;
    }
#else
    int main() {
        listen_server();
        return 0;
    }
#endif