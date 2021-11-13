cmake_minimum_required(VERSION 3.20)
project(QtHDR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
        )
find_package(OpenCV REQUIRED)

add_executable(QtHDR main.cpp view/MainWindow.cpp view/MainWindow.hpp model/Image.cpp model/Image.hpp model/StackImage.cpp model/StackImage.hpp view/ImageWidget.cpp view/ImageWidget.hpp)
target_link_libraries(QtHDR
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        ${OpenCV_LIBS}
        )
