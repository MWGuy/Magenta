cmake_minimum_required(VERSION 2.6)

project(Magenta)

#set(SFML_STATIC_LIBRARIES TRUE)

INCLUDE_DIRECTORIES(D:\\sfml\\include\\)
LINK_DIRECTORIES(D:\\sfml\\lib\\)

add_executable(
    Magenta WIN32
		src/ActionButton.cpp
        src/ActionButton.h
		src/AddressBar.cpp
		src/AddressBar.h
		src/AddressText.cpp
		src/AddressText.h
		src/EventHandler.cpp
		src/EventHandler.h
		src/Figure.cpp
        src/Figure.h
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
		src/Menu.h
		src/Menu.cpp
		src/PanelButton.h
		src/PanelButton.cpp
		src/TabRegion.cpp
        src/TabRegion.h
		src/TextArea.cpp
        src/TextArea.h
		src/TopPanel.h
		src/TopPanel.cpp
		src/ValueAnimation.cpp
        src/ValueAnimation.h
		src/forms/AppWindowF.cpp
        src/forms/AppWindowF.h
		src/shared/NewtooView.cpp
        src/shared/NewtooView.h
		${CMAKE_CURRENT_SOURCE_DIR}/resources/resources.rc
)

target_link_libraries(Magenta sfml-graphics sfml-window sfml-system)
