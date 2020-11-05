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

SDL_Texture* SDL_Model::create_map_texture(int num_lines, int num_columns, int block_width, int block_height, int thickness=2, int r=255, int g=255, int b=255){

	SDL_Surface *surf = SDL_CreateRGBSurface(0, block_width*num_columns,block_height*num_lines,32,0,0,0,255);
	Uint32 color = SDL_MapRGB(surf->format, r, g, b);
	SDL_Rect rect;

	rect.x = 0;

	for(int line = 0; line <= num_lines; line++){
		rect.y = block_height*line - thickness/2;
	
		rect.w = num_columns*block_width;
		rect.h = thickness;


		SDL_FillRect(surf, &rect, color);
  	}
	rect.y = 0;
	for(int column = 0; column <= num_columns; column++){
		rect.x = block_width*column - thickness/2;
	
		rect.h = num_lines*block_height;
		rect.w = thickness;


		SDL_FillRect(surf, &rect, color);
  	}


	return SDL_CreateTextureFromSurface(renderer,surf);
}

SDL_Texture* SDL_Model::create_block_texture(int block_width, int block_height, int r=255, int g=255, int b=255){

	SDL_Surface *surf = SDL_CreateRGBSurface(0, block_width,block_height,32,0,0,0,255);
	Uint32 color = SDL_MapRGB(surf->format, r, g, b);
	SDL_Rect rect;

	rect.x = 0;
	rect.y = 0;

	rect.w = block_width;
	rect.h = block_height;


	SDL_FillRect(surf, &rect, color);


	return SDL_CreateTextureFromSurface(renderer,surf);
}
