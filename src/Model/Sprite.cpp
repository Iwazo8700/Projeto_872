#include "Sprite.hpp"

Sprite::Sprite(std::shared_ptr<SDL_Model> sdl, char const *dir=""){
	this->sdl = sdl;
	if(dir != "")
		this->texture = IMG_LoadTexture(this->sdl->get_renderer(), dir);
}

Sprite::~Sprite(){
	SDL_DestroyTexture(this->texture);
}

void Sprite::set_image(char const *dir){
	this->texture = IMG_LoadTexture(this->sdl->get_renderer(), dir);
}

void Sprite::set_texture(SDL_Texture *texture){
	this->texture = texture;
}

SDL_Texture* Sprite::get_texture(){
	return this->texture;
}
