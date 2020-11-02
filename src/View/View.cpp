#include "View.hpp"

View::View(std::shared_ptr<SDL_Model> sdl){
	this->sdl = sdl;
}

void View::render(std::vector<std::shared_ptr<Image>> objects){
	SDL_RenderClear(this->sdl->get_renderer());
	std::vector<std::shared_ptr<Image>>::iterator image;

	// Desenha cada objeto da cena
	for(std::shared_ptr<Image> image : objects)
		SDL_RenderCopy(this->sdl->get_renderer(), image->get_texture(), nullptr, image->get_target());
	SDL_RenderPresent(this->sdl->get_renderer());
}

/*
void View::render(std::string text, int x, int y, int height, int width){
	SDL_RenderClear(this->sdl->get_renderer());
	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);

	SDL_Color White = {255, 255, 255};

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, text, White);

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect Message_rect; 
	Message_rect.x = x;
	Message_rect.y = y;
	Message_rect.w = width; 
	Message_rect.h = height;ct

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}*/
