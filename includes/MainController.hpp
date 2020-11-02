#pragma once

#include "Formato.hpp"
#include "Bloco.hpp"
#include "Map.hpp"
#include "Image.hpp"
#include "BlockPosition.hpp"
#include "Collision.hpp"
#include "Keyboard.hpp"
#include "Player.hpp"
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map> 
#include <algorithm>

class MainController{
	private:
		std::shared_ptr<Formato> formats;
		std::shared_ptr<Map> map;
		std::shared_ptr<Collision> collision;
		std::vector<std::shared_ptr<Player>> players;
		unsigned int timer, move_time;
	public:
		MainController(std::shared_ptr<Map> map, std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Formato> formato);
		bool should_move(std::shared_ptr<Player> player);
		void step();
		std::shared_ptr<Bloco> create_random_block(int x, int y, int height, int width, std::shared_ptr<Sprite> sprite);
		void set_players(std::vector<std::shared_ptr<Player>> player);
		int update_board();
		bool is_dead(std::shared_ptr<Player> player);
};
