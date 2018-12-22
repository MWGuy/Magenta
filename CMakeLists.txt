cmake_minimum_required(VERSION 2.6)

project(Magenta)

add_executable(
    Magenta WIN32
        src/Magenta.cpp
        src/Magenta.h
        src/Window.cpp
        src/Window.h
        src/Layout.cpp
        src/Layout.h
        src/Widget.cpp
        src/Widget.h
		src/Rect.cpp
        src/Rect.h
		src/forms/AppWindowF.cpp
        src/forms/AppWindowF.h
)
