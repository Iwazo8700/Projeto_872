#include "Sprite.hpp"

Sprite::Sprite(char const *dir, std::shared_ptr<SDL_Model> sdl){
	this->sdl = sdl;
	this->texture = IMG_LoadTexture(this->sdl->get_renderer(), dir);
}

Sprite::~Sprite(){
	SDL_DestroyTexture(this->texture);
}

void Sprite::set_image(char const *dir){
	this->texture = IMG_LoadTexture(this->sdl->get_renderer(), dir);
}

SDL_Texture* Sprite::get_texture(){
	return this->texture;
}
