# Versao minima do cmake
cmake_minimum_required(VERSION 3.0)

# Nome do meu projeto
project(Sirtet)

#
add_executable(Sirtet src/main.cpp)
add_executable(client src/client.cpp)

# Especificar onde estao os header files
include_directories(includes/)

# Bibliotecas locais (estaticas)
add_library(Sprites src/Model/Sprite.cpp)
add_library(Piece src/Model/Bloco.cpp)
add_library(Map src/Model/Map.cpp)
add_library(SDL_Funcs src/Model/SDL_Model.cpp)
add_library(Formatos src/Model/Formato.cpp)
add_library(BlockController src/Controller/BlockPosition.cpp)
add_library(View src/View/View.cpp)
add_library(Image src/Model/Image.cpp)
add_library(Collisions src/Controller/Collision.cpp)
add_library(Keyboard src/Controller/Keyboard.cpp)
add_library(Main src/Controller/MainController.cpp)
add_library(Player src/Model/Player.cpp)
add_library(Config src/Controller/ConfigReader.cpp)
add_library(IA src/Model/IA.cpp)
add_library(IAFunctions src/Controller/IAFunctions.cpp)
add_library(Container src/Model/Container.cpp)


target_link_libraries(Sirtet Sprites)
target_link_libraries(Sirtet Piece)
target_link_libraries(Sirtet Map)
target_link_libraries(Sirtet SDL_Funcs)
target_link_libraries(Sirtet Formatos)
target_link_libraries(Sirtet BlockController)
target_link_libraries(Sirtet View)
target_link_libraries(Sirtet Image)
target_link_libraries(Sirtet Collisions)
target_link_libraries(Sirtet Keyboard)
target_link_libraries(Sirtet Main)
target_link_libraries(Sirtet Player)
target_link_libraries(Sirtet Config)
target_link_libraries(Sirtet IA)
target_link_libraries(Sirtet Container)
target_link_libraries(Sirtet IAFunctions)

target_link_libraries(client Sprites)
target_link_libraries(client Piece)
target_link_libraries(client Map)
target_link_libraries(client SDL_Funcs)
target_link_libraries(client Formatos)
target_link_libraries(client BlockController)
target_link_libraries(client View)
target_link_libraries(client Image)
target_link_libraries(client Collisions)
target_link_libraries(client Keyboard)
target_link_libraries(client Main)
target_link_libraries(client Player)
target_link_libraries(client Config)
target_link_libraries(client IA)
target_link_libraries(client Container)
target_link_libraries(client IAFunctions)

# Garantir que usaremos C++11 (ou superior, se preciso)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Bibliotecas linkadas externamente
target_link_libraries(Sirtet SDL2)
target_link_libraries(Sirtet SDL2_image)

target_link_libraries(client SDL2)
target_link_libraries(client SDL2_image)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS thread system date_time) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    target_link_libraries(client ${Boost_LIBRARIES})
    target_link_libraries(Sirtet ${Boost_LIBRARIES})
endif()

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
