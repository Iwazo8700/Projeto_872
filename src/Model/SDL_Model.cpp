#include "SDL_Model.hpp"

SDL_Model::SDL_Model(int width, int height){
	this->SCREEN_WIDTH = width;
	this->SCREEN_HEIGHT = height;
	// Inicializando o subsistema de video do SDL
	if ( SDL_Init (SDL_INIT_VIDEO) < 0 ) {
		std::cout << SDL_GetError();
	}

	this->window = SDL_CreateWindow("Sirtet",
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED,
	SCREEN_WIDTH,
	SCREEN_HEIGHT,
	SDL_WINDOW_SHOWN);

	// Criando uma janela
	if (this->window==nullptr) { // Em caso de erro...
		std::cout << SDL_GetError();
		SDL_Quit();
	}

 	// Inicializando o renderizador
	this->renderer = SDL_CreateRenderer(
				this->window, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (this->renderer==nullptr) { // Em caso de erro...
		SDL_DestroyWindow(this->window);
		std::cout << SDL_GetError();
		SDL_Quit();
	}

}

SDL_Model::~SDL_Model(){
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

SDL_Renderer* SDL_Model::get_renderer(){
	return this->renderer;
}
