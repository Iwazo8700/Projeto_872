#include "View.hpp"

View::View(std::shared_ptr<SDL_Model> sdl){
	this->sdl = sdl;
}

void View::render(std::vector<std::shared_ptr<Image>> objects){

	SDL_RenderClear(this->sdl->get_renderer());
	std::vector<std::shared_ptr<Image>>::iterator image;

	// Desenha cada objeto da cena
	for(std::shared_ptr<Image> image : objects){
		std::cout << image->get_target()->x << ' ' << image->get_target()->y << std::endl;
		SDL_RenderCopy(this->sdl->get_renderer(), image->get_texture(), nullptr, image->get_target());
		SDL_RenderPresent(this->sdl->get_renderer());
	}
}

