#pragma once

#include <vector>
#include <memory>
#include "Bloco.hpp"
#include "Keyboard.hpp"

class Player{
	private:
		std::shared_ptr<Bloco> piece;
		std::shared_ptr<Keyboard> keyboard;
		int points, speed;
		unsigned int time;
		bool alive;
	public:
		Player(std::shared_ptr<Bloco> piece, std::shared_ptr<Keyboard> keyboard, int speed);
		void set_piece(std::shared_ptr<Bloco> piece);
		void set_keyboard(std::shared_ptr<Keyboard> keyboard);
		void increase_speed(int speed);
		void add_points(int points);
		void set_time(unsigned int time);	

		std::shared_ptr<Bloco> get_piece();
		std::shared_ptr<Keyboard> get_keyboard();
		int get_points();
		int get_speed();
		unsigned int get_time();
		bool is_alive();
		void kill();
};
