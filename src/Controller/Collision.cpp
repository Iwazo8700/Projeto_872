#include "Collision.hpp"

Collision::Collision(std::shared_ptr<Map> map, bool piece_collide = false){
	this->map = map;
	this->piece_collide = piece_collide;
}

void Collision::set_map(std::shared_ptr<Map> map){
	this->map = map;
}

bool Collision::is_colliding(std::shared_ptr<Bloco> block){
	std::vector<std::vector<bool>> vec = block->get_formato();
	std::vector<std::vector<int>> current_map = this->map->get_map();
	int height = current_map.size();
	int width = current_map[0].size();
	int x = block->get_x();
	int y = block->get_y();
	int i = 0, j = 0;

	for(auto line : vec){
		for(auto element : line){
			if(element && (y+i >= height || j+x < 0 || j+x >= width))
				return true;
			if(element && y+i >= 0 && y+i < height && j+x >= 0 && j+x <width && current_map[y+i][x+j])
				return true;
			j++;
		}
		j = 0;
		i++;
	}
	
	return false;
}

bool Collision::is_colliding(std::shared_ptr<Bloco> block, std::vector<std::shared_ptr<Bloco>> others){
	if(this->piece_collide && others.size()){
		std::vector<std::vector<bool>> vec = block->get_formato();
		std::vector<std::vector<int>> current_block = this->map->get_map();
		std::vector<std::vector<int>> current_map = this->map->get_map();
		int height = current_map.size();
		int width = current_map[0].size();
		int x = block->get_x(), x_other;
		int y = block->get_y(), y_other;
		int size_y = vec.size();
		int size_x = vec[0].size();
		int i = 0, j = 0;

		for(std::shared_ptr<Bloco> other : others){
			x_other = other->get_x();
			y_other = other->get_y();
			std::vector<std::vector<bool>> tmp_vec = other->get_formato();
			int other_width = tmp_vec.size();
			int other_height = tmp_vec[0].size();
			for(auto line : vec){
				for(auto element : line){
					if(element && (y+i >= height || j+x < 0 || j+x >= width))
						return true;
					if(element && y+i-y_other>=0 && y+i-y_other<other_height && j+x-x_other>=0 && j+x-x_other<other_width && tmp_vec[y+i-y_other][j+x-x_other])
						return true;
					j++;
				}
				j = 0;
				i++;
			}
		}
	}

	return false;
	
}
