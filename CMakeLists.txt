cmake_minimum_required(VERSION 3.30)
project(teste)

set(CMAKE_CXX_STANDARD 20)

add_executable(teste main.cpp
                      BatchMode.cpp
                        Data.cpp
Dijkstra.cpp Menu.cpp RoutePlanner.cpp Location.cpp)
