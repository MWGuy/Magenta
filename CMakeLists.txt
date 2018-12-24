cmake_minimum_required(VERSION 2.6)

project(Magenta)

#set(SFML_STATIC_LIBRARIES TRUE)

INCLUDE_DIRECTORIES(D:\\sfml\\include\\)
LINK_DIRECTORIES(D:\\sfml\\lib\\)


add_executable(
    Magenta WIN32
        src/Magenta.cpp
        src/Magenta.h
        src/Window.cpp
        src/Window.h
		src/WindowCaption.cpp
        src/WindowCaption.h
        src/Layout.cpp
        src/Layout.h
        src/Widget.cpp
        src/Widget.h
		src/Rect.cpp
        src/Rect.h
		src/TabRegion.cpp
        src/TabRegion.h
		src/forms/AppWindowF.cpp
        src/forms/AppWindowF.h
)

target_link_libraries(Magenta sfml-graphics sfml-window sfml-system)
