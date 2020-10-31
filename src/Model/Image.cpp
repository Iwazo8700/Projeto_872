#include "Image.hpp"

Image::Image(int x, int y, int width, int height, std::shared_ptr<Sprite> sprite){
	this->target.x = x;
	this->target.y = y;
	this->target.h = height;
	this->target.w = width;
	this->sprite = sprite;
}

SDL_Rect* Image::get_target(){
	return &(this->target);
}

SDL_Texture* Image::get_texture(){
	return this->sprite->get_texture();
}
