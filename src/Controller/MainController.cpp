#include "MainController.hpp"
		
MainController::MainController(std::shared_ptr<Map> map, std::shared_ptr<std::map<int, std::shared_ptr<Bloco>>> pieces, std::shared_ptr<std::map<int,std::shared_ptr<Keyboard>>> movements, std::shared_ptr<Collision> collision, unsigned int move_time, std::shared_ptr<Formato> formato){
	this->map = map;
	this->pieces = pieces;
	this->movements = movements;
	this->move_time = move_time;
	this->collision = collision;
	this->timer = 0;
	this->formats = formato;
}

bool MainController::should_move(){
	if(this->timer+this->move_time <= SDL_GetTicks()){
		this->timer = SDL_GetTicks();
		return true;
	}
	
	return false;
}

void MainController::update_board(){
	std::vector<std::vector<int>> format = this->map->get_map();
	std::vector<int> complete_lines;
	int i = 0;
	for(auto line : format){
		if(std::count(line.begin(),line.end(),0) == 0)
			complete_lines.push_back(i);
		i++;
	}
	this->map->completed_lines(complete_lines);
}

void MainController::step(){
	int tmp;
	std::shared_ptr<Bloco> tmp_blk;
	for(auto block : *(this->pieces)){
		if(should_move()){
			block.second->set_y(block.second->get_y()+1);
			if(this->collision->is_colliding(block.second)){
				block.second->set_y(block.second->get_y()-1);
				this->map->add_to_map(block.second,1);
				this->pieces->find(block.first)->second = this->create_random_block(0,0,20,20,block.first, block.second->get_sprite());
				this->movements->find(block.first)->second->set_bloco(this->pieces->find(block.first)->second);
				continue;
			}
		}
		tmp = block.second->get_x();
		block.second->set_x(this->movements->find(block.first)->second->Desloc());
		if(this->collision->is_colliding(block.second))
			block.second->set_x(tmp);
		
		tmp_blk = std::make_shared<Bloco>(*block.second);
		tmp_blk->set_formato(this->movements->find(block.first)->second->Rotation());
		if(!this->collision->is_colliding(tmp_blk))
			block.second->set_formato(tmp_blk->get_formato());
	}
	this->update_board();
}

void MainController::set_keyboard(int id, std::shared_ptr<Keyboard> keyboard){
	this->movements->insert({id, keyboard});
}

void MainController::set_block(int id, std::shared_ptr<Bloco> block){
	this->pieces->insert({id, block});
}

std::shared_ptr<Bloco> MainController::create_random_block(int x, int y, int height, int width, int id, std::shared_ptr<Sprite> sprite){
	std::vector<std::vector<bool>> vec = this->formats->get_random();
	return (std::shared_ptr<Bloco>) new Bloco(x, y, vec, sprite, height, width);
}
