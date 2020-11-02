#include "MainController.hpp"
		
MainController::MainController(std::shared_ptr<Map> map, std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Formato> formato){
	this->map = map;
	this->players = players;
	std::shared_ptr<Collision> col (new Collision(this->map));
	this->collision = col;
	this->formats = formato;
}

bool MainController::should_move(std::shared_ptr<Player> player){
	if(player->get_time()+player->get_speed() <= SDL_GetTicks()){
		player->set_time(SDL_GetTicks());
		return true;
	}
	
	return false;
}

int MainController::update_board(){
	std::vector<std::vector<int>> format = this->map->get_map();
	std::vector<int> complete_lines;
	int i = 0;
	for(auto line : format){
		if(std::count(line.begin(),line.end(),0) == 0)
			complete_lines.push_back(i);
		i++;
	}
	this->map->completed_lines(complete_lines);

	return complete_lines.size();
}

bool MainController::is_dead(std::shared_ptr<Player> player){
	int i = 0, y = player->get_piece()->get_y();
	
	for(auto line : player->get_piece()->get_formato())
		if(y+i < 0 && std::count(line.begin(), line.end(), 1) != 0)
			return true;
	return false;
		
}

void MainController::step(){
	int tmp;
	std::shared_ptr<Bloco> tmp_blk;
	for(auto player : this->players){
		if(should_move(player) && player->is_alive()){
			player->get_piece()->set_y(player->get_piece()->get_y()+1);
			if(this->collision->is_colliding(player->get_piece())){
				if(is_dead(player)){
					player->kill();
					continue;
				}
				player->get_piece()->set_y(player->get_piece()->get_y()-1);
				this->map->add_to_map(player->get_piece(),1);
				player->set_piece(this->create_random_block(0,-5,20,20, player->get_piece()->get_sprite()));
				switch(this->update_board()){
					case 1:
						player->add_points(40);
						break;
					case 2:
						player->add_points(100);
						break;
					case 3:
						player->add_points(300);
						break;
					case 4:
						player->add_points(1200);
						break;
				}
				continue;
			}
		}
		tmp = player->get_piece()->get_x();
		player->get_piece()->set_x(player->get_keyboard()->Desloc());
		if(this->collision->is_colliding(player->get_piece()))
			player->get_piece()->set_x(tmp);
		
		tmp_blk = std::make_shared<Bloco>(*(player->get_piece()));
		tmp_blk->set_formato(player->get_keyboard()->Rotation());
		if(!this->collision->is_colliding(tmp_blk))
			player->get_piece()->set_formato(tmp_blk->get_formato());

		player->get_piece()->set_y(player->get_keyboard()->Space(this->collision));
	}
}

void MainController::set_players(std::vector<std::shared_ptr<Player>> players){
	this->players = players;
}

std::shared_ptr<Bloco> MainController::create_random_block(int x, int y, int height, int width, std::shared_ptr<Sprite> sprite){
	std::vector<std::vector<bool>> vec = this->formats->get_random();
	return (std::shared_ptr<Bloco>) new Bloco(x, y, vec, sprite, height, width);
}
