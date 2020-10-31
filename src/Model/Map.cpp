#include "Map.hpp"

Map::Map(int width, int height, int block_width, int block_height){
	std::vector<std::vector<int>> map(height, std::vector<int>(width, 0));
	this->map = map;
	this->block_width = block_width;
	this->block_height = block_height;
}

int Map::get_block_width(){
	return this->block_width;
}

int Map::get_block_height(){
	return this->block_height;
}

std::vector<std::vector<int>> Map::get_map(){
	return this->map;
}

void Map::add_to_map(std::shared_ptr<Bloco> block, int value=1){
	int i, j;
	int x = block->get_x();
	int y = block->get_y();
	
	std::vector<std::vector<bool>> format = block->get_formato();	

	for(i = 0; i < format.size(); i++)
		for(j = 0; j < format[i].size(); j++)
			if(format[i][j])
				this->map[i+x][j+y] = value;
}
