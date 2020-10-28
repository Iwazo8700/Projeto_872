# Versao minima do cmake
cmake_minimum_required(VERSION 3.0)

# Nome do meu projeto
project(Sirtet)

#
add_executable(Sirtet src/main.cpp)

# Especificar onde estao os header files
include_directories(includes/)

# Bibliotecas locais (estaticas)
add_library(func1 src/Model/Massa.cpp)
add_library(func2 src/Model/Mola.cpp)
add_library(func3 src/Model/Amortecedor.cpp)
add_library(func4 src/Model/Images.cpp)
add_library(func5 src/Controller/Simulador.cpp)
add_library(func6 src/Controller/PixelConverter.cpp)
add_library(func7 src/Controller/Keyboard.cpp)
add_library(func8 src/Controller/ImageControl.cpp)
add_library(func9 src/View/View.cpp)
target_link_libraries(Luffy func1)
target_link_libraries(Luffy func2)
target_link_libraries(Luffy func3)
target_link_libraries(Luffy func4)
target_link_libraries(Luffy func5)
target_link_libraries(Luffy func6)
target_link_libraries(Luffy func7)
target_link_libraries(Luffy func8)
target_link_libraries(Luffy func9)

# Garantir que usaremos C++11 (ou superior, se preciso)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Bibliotecas linkadas externamente
target_link_libraries(Sirtet SDL2)
target_link_libraries(Sirtet SDL2_image)
