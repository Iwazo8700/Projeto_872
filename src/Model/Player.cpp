#include "Player.hpp"

Player::Player(std::shared_ptr<Bloco> piece, std::shared_ptr<Keyboard> keyboard, int speed){
	this->piece = piece;
	this->keyboard = keyboard; 
	this->speed = speed;
	this->points = 0;
	this->lines_completed = 0;
	this->time = 0;
	this->alive = true;
}

void Player::kill(){
	this->alive = false;
}
		
void Player::set_speed(int speed){
	this->speed = speed;
}

void Player::set_points(int points){
	this->points = points;
}

void Player::set_piece(std::shared_ptr<Bloco> piece){
	this->piece = piece;
	this->keyboard->set_bloco(this->piece);
}

void Player::set_keyboard(std::shared_ptr<Keyboard> keyboard){
	this->keyboard = keyboard;
}

void Player::increase_speed(int speed){
	this->speed += speed;
}

bool Player::is_alive(){
	return this->alive;
}

void Player::add_points(int points){
	this->points += points;
}

std::shared_ptr<Bloco> Player::get_piece(){
	return this->piece;
}

std::shared_ptr<Keyboard> Player::get_keyboard(){
	return this->keyboard;
}

int Player::get_points(){
	return this->points;
}

int Player::get_speed(){
	return this->speed;
}

void Player::set_time(unsigned int time){
	this->time = time;
}

unsigned int Player::get_time(){
	return this->time;
}

int Player::get_lines_completed(){
	return this->lines_completed;
}

void Player::set_lines_completed(int lines){
	this->lines_completed = lines;
}
