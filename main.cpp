#include "include/httplib.h"
#include <stdio.h>
#include <cstdlib>
#include <string>
#ifdef _WIN32
#include "window_win32.h"
#else
#include "window_win32.h"
#endif

#define SERVER_ADDRESS "localhost"
#define SERVER_PORT 9013

using namespace httplib;

int main() {

    Server svr;
    svr.Get("/status", [](const Request &req, Response &res) {
        std::string window_title =  get_window_title();
        std::string json_output = std::string("{ 'active_window' : '") + window_title + "'}";
        res.set_content(json_output, "application/json" );
    });
    
    printf("running server at %s:%i\n",SERVER_ADDRESS,SERVER_PORT);
    svr.listen(SERVER_ADDRESS, SERVER_PORT);
    return 0;
}