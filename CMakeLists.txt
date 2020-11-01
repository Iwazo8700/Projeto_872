# Versao minima do cmake
cmake_minimum_required(VERSION 3.0)

# Nome do meu projeto
project(Sirtet)

#
add_executable(Sirtet src/main.cpp)

# Especificar onde estao os header files
include_directories(includes/)

# Bibliotecas locais (estaticas)
add_library(func2 src/Model/Sprite.cpp)
add_library(func3 src/Model/Bloco.cpp)
add_library(func4 src/Model/Map.cpp)
add_library(func5 src/Model/SDL_Model.cpp)
add_library(func1 src/Model/Image.cpp)
add_library(func7 src/Model/Formato.cpp)

#add_library(func2 src/Controller/.cpp)
add_library(func6 src/View/View.cpp)
target_link_libraries(Sirtet func1)
target_link_libraries(Sirtet func2)
target_link_libraries(Sirtet func3)
target_link_libraries(Sirtet func4)
target_link_libraries(Sirtet func5)
target_link_libraries(Sirtet func6)
target_link_libraries(Sirtet func7)

# Garantir que usaremos C++11 (ou superior, se preciso)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Bibliotecas linkadas externamente
target_link_libraries(Sirtet SDL2)
target_link_libraries(Sirtet SDL2_image)
