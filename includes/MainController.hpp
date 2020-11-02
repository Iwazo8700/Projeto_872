#pragma once

#include "Bloco.hpp"
#include "Map.hpp"
#include "Image.hpp"
#include "BlockPosition.hpp"
#include "Collision.hpp"
#include "Keyboard.hpp"
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map> 
#include <algorithm>

class MainController{
	private:
		std::shared_ptr<Map> map;
		std::shared_ptr<Collision> collision;
		std::shared_ptr<std::map<int,std::shared_ptr<Bloco>>> pieces;
		std::shared_ptr<std::map<int,std::shared_ptr<Keyboard>>> movements;
		unsigned int timer, move_time;
	public:
		MainController(std::shared_ptr<Map> map, std::shared_ptr<std::map<int,std::shared_ptr<Bloco>>> pieces, std::shared_ptr<std::map<int,std::shared_ptr<Keyboard>>> movements, std::shared_ptr<Collision> collision, unsigned int move_time);
		bool should_move();
		void step();
		std::shared_ptr<Bloco> create_random_block(int x, int y, int height, int width, int id, std::shared_ptr<Sprite> sprite);
		void set_block(int id, std::shared_ptr<Bloco> block);
		void set_keyboard(int id, std::shared_ptr<Keyboard> keyboard);
		void update_board();
};
