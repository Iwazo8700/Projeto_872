#pragma once

#include "Bloco.hpp"

Bloco::Bloco(int x, int y, char formato, std::shared_ptr<Sprite> sprite){
	this->x = x;
	this->y = y;
	this->formato = formato;
	this->sprite = sprite;
}

int Bloco::get_x() {
	return this->x;
}
int Bloco::get_y(){
	return this->y;
}
char Bloco::get_formato(){
	return this->formato;
}
std::shared_ptr<Sprite> Bloco::get_sprite(){
	return this->sprite;
}

void Bloco::set_x(int x){
	this->x = x;
}
void Bloco::set_y(int y){
	this->y = y;
}
void Bloco::set_formato(char formato){
	this->formato = formato;
}
void Bloco::set_sprite(std::shared_ptr<Sprite> sprite){
	this->sprite = sprite;
} 

