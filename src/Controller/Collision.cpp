#include "Collision.hpp"

Collision::Collision(std::shared_ptr<Map> map){
	this->map = map;
}

void Collision::set_map(std::shared_ptr<Map> map){
	this->map = map;
}

bool Collision::is_colliding(std::shared_ptr<Bloco> block){
	std::vector<std::vector<bool>> vec = block->get_formato();
	std::vector<std::vector<int>> current_map = this->map->get_map();
	int x = block->get_x();
	int y = block->get_y();
	int i = 0, j = 0;

	for(auto line : vec){
		for(auto element : line){
			if(element && current_map[x+i][y+j])
				return true;
			j++;
		}
		j = 0;
		i++;
	}
	
	return false;
}
