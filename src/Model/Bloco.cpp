#include "Bloco.hpp"

Bloco::Bloco(int x, int y, std::vector<std::vector<bool>> formato, std::shared_ptr<Sprite> sprite, int height, int width){
	this->x = x;
	this->y = y;
	this->initial_x = x;
	this->initial_y = y;
	this->formato = formato;
	this->sprite = sprite;
	this->height = height;
	this->width = width;
}

Bloco::Bloco(int x, int y, std::vector<std::vector<bool>> formato){
	this->x = x;
	this->y = y;
	this->formato = formato;
}

/*
SDL_Texture* Bloco::get_texture(){
	return this->sprite->get_texture();
}
*/
int Bloco::get_x() {
	return this->x;
}

int Bloco::get_y(){
	return this->y;
}

int Bloco::get_initial_y(){
	return this->initial_y;
}

int Bloco::get_initial_x(){
	return this->initial_x;
}

std::vector<std::vector<bool>> Bloco::get_formato(){
	return this->formato;
}

std::shared_ptr<Sprite> Bloco::get_sprite(){
	return this->sprite;
}

void Bloco::set_x(int x){
	this->x = x;
}

void Bloco::set_format_name(char name){
	this->format_name = name;
}

char Bloco::get_format_name(){
	return this->format_name;
}

void Bloco::set_y(int y){
	this->y = y;
}

void Bloco::set_formato(std::vector<std::vector<bool>> formato){
	this->formato = formato;
}

void Bloco::set_sprite(std::shared_ptr<Sprite> sprite){
	this->sprite = sprite;
} 

void Bloco::set_size(int height, int width){
	this->height = height;
	this->width = width;
}

int Bloco::get_width(){
	return this->width;
}

int Bloco::get_height(){
	return this->height;
}
