cmake_minimum_required(VERSION 3.10)
project(octa-anticheat VERSION 1.0)

if (WIN32)
    add_executable(octa-anticheat WIN32 main.cpp linux_window.cpp window_win32.cpp
        res/app.rc)
    
else()
    add_executable(octa-anticheat main.cpp linux_window.cpp window_win32.cpp)
endif()
target_compile_options(octa-anticheat PRIVATE
    -Os
    -ffunction-sections
    -fdata-sections
)

target_link_options(octa-anticheat PRIVATE
    -Wl,--gc-sections
)
