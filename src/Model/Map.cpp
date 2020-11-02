#include "Map.hpp"

Map::Map(int width, int height, int block_width, int block_height){
	std::vector<std::vector<int>> map(height, std::vector<int>(width, 0));
	this->height = height;
	this->width = width;
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
			if(format[i][j] && i+y >= 0 && i+y < this->height && x+j >= 0 && x+j < this->width)
				this->map[i+y][j+x] = value;
}

std::shared_ptr<Sprite> Map::get_texture(int i, int j){
	int pos = this->map[i][j] - 1;

	if(pos >= 0)
		return this->sprites[pos];
	else
		return nullptr;
}

std::shared_ptr<Sprite> Map::get_texture(int pos){
	return this->sprites[pos];
}

void Map::set_sprites(std::vector<std::shared_ptr<Sprite>> sprites){
	this->sprites = sprites;
}

void Map::completed_lines(int n){
	this->map.erase(this->map.end()-n+1, this->map.end());
	for(int i = 0; i < n; i++)
		this->map.insert(this->map.begin(),std::vector<int>(width, 0));
}

void Map::completed_lines(std::vector<int> lines){
	for(auto i : lines){
		this->map.erase(this->map.begin()+i);
		this->map.insert(this->map.begin(),std::vector<int>(width, 0));
	}
}
