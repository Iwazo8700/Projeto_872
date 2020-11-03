# Versao minima do cmake
cmake_minimum_required(VERSION 3.0)

# Nome do meu projeto
project(Sirtet)

#
add_executable(Sirtet src/main.cpp)

# Especificar onde estao os header files
include_directories(includes/)

# Bibliotecas locais (estaticas)
add_library(func1 src/Model/Sprite.cpp)
add_library(func2 src/Model/Bloco.cpp)
add_library(func3 src/Model/Map.cpp)
add_library(func4 src/Model/SDL_Model.cpp)
add_library(func5 src/Model/Formato.cpp)
add_library(func6 src/Controller/BlockPosition.cpp)
add_library(func7 src/View/View.cpp)
add_library(func8 src/Model/Image.cpp)
add_library(func9 src/Controller/Collision.cpp)
add_library(func10 src/Controller/Keyboard.cpp)
add_library(func11 src/Controller/MainController.cpp)
add_library(func12 src/Model/Player.cpp)
add_library(func13 src/Controller/ConfigReader.cpp)

target_link_libraries(Sirtet func1)
target_link_libraries(Sirtet func2)
target_link_libraries(Sirtet func3)
target_link_libraries(Sirtet func4)
target_link_libraries(Sirtet func5)
target_link_libraries(Sirtet func6)
target_link_libraries(Sirtet func7)
target_link_libraries(Sirtet func8)
target_link_libraries(Sirtet func9)
target_link_libraries(Sirtet func10)
target_link_libraries(Sirtet func11)
target_link_libraries(Sirtet func12)
target_link_libraries(Sirtet func13)

# Garantir que usaremos C++11 (ou superior, se preciso)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Bibliotecas linkadas externamente
target_link_libraries(Sirtet SDL2)
target_link_libraries(Sirtet SDL2_image)

# Automatizacao do Doxygen
find_package(Doxygen REQUIRED dot)

set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_EXTRACT_PRIVATE YES)
set(DOXYGEN EXTRACT_STATIC YES)
set(DOXYGEN_TEMPLATE_RELATIONS YES)
set(DOXYGEN_COLLABORATION_GRAPH YES)
set(DOXYGEN_UML_LOOK YES)
set(DOXYGEN_CLASS_GRAPH YES)

doxygen_add_docs(doc)
