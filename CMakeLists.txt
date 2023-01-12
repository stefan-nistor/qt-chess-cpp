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

add_executable(client main.cpp
        LoginWidget.cpp LoginWidget.h
        MainWidget.cpp MainWidget.h
        MainWidget.h Drawable.h
        utility.h
        LobbyFinderWidget.cpp LobbyFinderWidget.h
        LobbyWidget.cpp LobbyWidget.h
        #        src/board/Board.cpp src/board/Board.h
#        src/board/BoardTile.cpp src/board/BoardTile.h
#        src/pieces/Piece.cpp src/pieces/Piece.h
#        src/pieces/Properties.h src/pieces/Properties.h
        Session.h
        BoardView.cpp BoardView.h
        Piece.cpp Piece.h
        Tile.h)

add_executable(test_ui test_ui.cpp BoardView.cpp BoardView.h Tile.h Piece.cpp Piece.h)

target_link_libraries(client
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

target_link_libraries(test_ui
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

