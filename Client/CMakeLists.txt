cmake_minimum_required(VERSION 3.19)
project(Client)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-pthread")

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

set(SOURCE_FILES main.cpp MainWindow.cpp MainWindow.h)

add_executable(Client main.cpp ClientSock.cpp ClientSock.h UI.h Interface.h)
target_link_libraries(Client sfml-graphics sfml-window sfml-system)
target_link_libraries(${CMAKE_PROJECT_NAME} ${GTKMM_LIBRARIES})