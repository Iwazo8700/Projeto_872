#pragma once

#include <vector>
#include <memory>
#include "Bloco.hpp"
#include "Sprite.hpp"

class Map{
	private:
		std::vector<std::vector<int>> map;
		int block_width, block_height,height,width;
		std::vector<std::shared_ptr<Sprite>> sprites;
	public:
		Map(int height, int width, int block_height, int block_width);
		int get_block_width();
		int get_block_height();
		std::vector<std::vector<int>> get_map();
		void add_to_map(std::shared_ptr<Bloco> block, int value);
		std::shared_ptr<Sprite> get_texture(int i, int j);
		void set_sprites(std::vector<std::shared_ptr<Sprite>> sprites);
		void completed_lines(int n);
		void completed_lines(std::vector<int> lines);
};
