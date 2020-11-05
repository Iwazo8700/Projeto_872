#include "IA.hpp"



IA::IA(std::shared_ptr<Player> player, float a, float b, float c, float d){
	this->player = player;
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
}

void IA::set_player(std::shared_ptr<Player> player){
	this->player = player;
}

void IA::set_a(float a){
	this->a = a;
}

void IA::set_b(float b){
	this->b = b;
}

void IA::set_c(float c){
	this->c = c;
}
void IA::set_d(float d){
	this->d = d;
}

float IA::get_a(){
	return this->a;
}

float IA::get_b(){
	return this->b;
}

float IA::get_c(){
	return this->c;
}

float IA::get_d(){
	return this->d;
}

std::shared_ptr<Player> IA::get_player(){
	return this->player;
}


