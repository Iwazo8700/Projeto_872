#include "SDL_Model.hpp"
#include "Sprite.hpp"
#include "Bloco.hpp"
#include "Map.hpp"
#include "View.hpp"
#include "Image.hpp"
#include "Formato.hpp"
#include <memory>
#include <vector>
#include <iostream>

int main(){
	std::vector<std::vector<bool>> vec(4, std::vector<bool>(4, true));
	std::shared_ptr<SDL_Model> sdl (new SDL_Model(800,800));
	std::shared_ptr<Sprite> sprite (new Sprite("../assets/fundo.jpg",sdl));
	std::shared_ptr<Map> map (new Map(22,10,100,100));
	std::shared_ptr<Bloco> block (new Bloco(0,0,vec,sprite,50,50));
	std::shared_ptr<View> view (new View(sdl));
	std::shared_ptr<Image> img (new Image(0,0,100,100,sprite));
	std::vector<std::shared_ptr<Image>> veci = {img};
	view->render(veci);
	std::shared_ptr<Formato> format (new Formato("../assets/Formatos.dat"));
	std::vector<std::vector<bool>> vect = format->get_I();
	for (int i=0; i<vect.size(); i++){
		for(int j=0; j<vect.size(); j++){
			std::cout << vect[i][j];
		}
		std::cout << '\n';
	}
	
	std::cout << '\n';
	
	vect = format->get_J();
	for (int i=0; i<vect.size(); i++){
		for(int j=0; j<vect.size(); j++){
			std::cout << vect[i][j];
		}
		std::cout << '\n';
	}
	
	std::cout << '\n';
	
	vect = format->get_L();
	for (int i=0; i<vect.size(); i++){
		for(int j=0; j<vect.size(); j++){
			std::cout << vect[i][j];
		}
		std::cout << '\n';
	}
	
	std::cout << '\n';
	
	 vect = format->get_O();
	for (int i=0; i<vect.size(); i++){
		for(int j=0; j<vect.size(); j++){
			std::cout << vect[i][j];
		}
		std::cout << '\n';
	}
	
	std::cout << '\n';
	
	vect = format->get_S();
	for (int i=0; i<vect.size(); i++){
		for(int j=0; j<vect.size(); j++){
			std::cout << vect[i][j];
		}
		std::cout << '\n';
	}
	
	std::cout << '\n';
	
	vect = format->get_T();
	for (int i=0; i<vect.size(); i++){
		for(int j=0; j<vect.size(); j++){
			std::cout << vect[i][j];
		}
		std::cout << '\n';
	}
	
	std::cout << '\n';
	
	vect = format->get_Z();
	for (int i=0; i<vect.size(); i++){
		for(int j=0; j<vect.size(); j++){
			std::cout << vect[i][j];
		}
		std::cout << '\n';
	}


	return 0;
}
