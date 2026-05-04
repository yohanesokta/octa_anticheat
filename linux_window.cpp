#ifndef _WIN32
#include "window_manager.h"
std::string BIN_DIR = std::string(std::getenv("HOME")) + "/.config/octaAnticheat/";
char* DESKTOP_ENVIRONTMENT = std::getenv("XDG_SESSION_TYPE");

std::string run_command(const std::string& command) {
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        printf("Failed to run command: %s\n", command.c_str());
        return "";
    } else {
        char buffer[128];
        std::string result = "";
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            result += buffer;
        }
        pclose(pipe);
        return result;
    }
}

std::string get_window_title() {
    DESKTOP_ENVIRONTMENT = std::getenv("XDG_SESSION_TYPE");
    if (strcmp(DESKTOP_ENVIRONTMENT,"wayland") == 0) {
        std::string window_id = run_command(BIN_DIR + "kdotool getactivewindow");
        std::string window_title = run_command(BIN_DIR + "kdotool getwindowname " + window_id);
        if (window_title.length() == 0) {
            return std::string("title is unknown window id - ") + window_id; 
        }
        return window_title;
    } else {
        std::string window_title = run_command("xdotool getactivewindow getwindowpid");
        if (window_title.length() == 0) {
            return "title is unknown"; 
        }
        return window_title;
    }
}
#endif