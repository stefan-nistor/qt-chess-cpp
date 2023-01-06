cmake_minimum_required(VERSION 3.24)
project(qt_chess_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(client main.cpp LoginWidget.cpp LoginWidget.h MainWidget.cpp MainWidget.h MainWidget.h Drawable.h utility.h LobbyFinderWidget.cpp LobbyFinderWidget.h LobbyWidget.cpp LobbyWidget.h)

target_link_libraries(client
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

