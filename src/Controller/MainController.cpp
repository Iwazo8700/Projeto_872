#include "MainController.hpp"
		
MainController::MainController(std::shared_ptr<Map> map, std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Formato> formato){
	this->map = map;
	this->players = players;
	std::shared_ptr<Collision> col (new Collision(this->map));
	this->collision = col;
	this->formats = formato;
}

MainController::MainController(std::shared_ptr<Map> map, std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Formato> formato, std::vector<std::shared_ptr<IAFunctions>> iafunc_vec){
	this->map = map;
	this->players = players;
	std::shared_ptr<Collision> col (new Collision(this->map));
	this->collision = col;
	this->formats = formato;
	this->iafunc_vec = iafunc_vec;
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
	
	for(auto line : player->get_piece()->get_formato()){
		if(y+i < 0 && std::count(line.begin(), line.end(), 1) != 0)
			return true;
		i++;
	}
	return false;
		
}

void MainController::step(){
	int tmp,points=0, is_space = 0;
	std::shared_ptr<Bloco> tmp_blk;
	int player_num = 1;
	for(auto player : this->players){
		is_space = player->get_keyboard()->Space(this->collision);
		if((should_move(player) && player->is_alive()) || is_space){
			player->get_piece()->set_y(player->get_piece()->get_y()+1);

			if(this->collision->is_colliding(player->get_piece())){
				player->get_piece()->set_y(player->get_piece()->get_y()-1);
				if(is_dead(player)){
					player->kill();
					continue;
				}
				this->map->add_to_map(player->get_piece(),player_num);
				player->set_piece(this->create_random_block(player->get_piece()->get_initial_x(),player->get_piece()->get_initial_x()));
				points = this->update_board();
				switch(points){
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
				player->set_lines_completed(player->get_lines_completed() + points);
				continue;
			}
		}
		std::vector<std::shared_ptr<Bloco>> tmp_vector;
		for(auto pl_piece : this->players)
			if(pl_piece != player)
				tmp_vector.push_back(pl_piece->get_piece());


		tmp = player->get_piece()->get_x();
		player->get_piece()->set_x(player->get_keyboard()->Desloc());
		if(this->collision->is_colliding(player->get_piece()) || this->collision->is_colliding(tmp_blk,tmp_vector))
			player->get_piece()->set_x(tmp);
		
		tmp_blk = std::make_shared<Bloco>(*(player->get_piece()));
		tmp_blk->set_formato(player->get_keyboard()->Rotation());
		if(!(this->collision->is_colliding(tmp_blk) || this->collision->is_colliding(tmp_blk,tmp_vector)))
			player->get_piece()->set_formato(tmp_blk->get_formato());

		tmp = player->get_piece()->get_y();
		player->get_piece()->set_y(player->get_keyboard()->Desloc_Vert());
		if(this->collision->is_colliding(player->get_piece()) || this->collision->is_colliding(player->get_piece(),tmp_vector))
			player->get_piece()->set_y(tmp);

		player_num++;
	}
}

void MainController::set_players(std::vector<std::shared_ptr<Player>> players){
	this->players = players;
}

std::shared_ptr<Bloco> MainController::create_random_block(int x, int y){
	std::vector<std::vector<bool>> vec = this->formats->get_random();
	return (std::shared_ptr<Bloco>) new Bloco(x, -1*vec.size(), vec);
}





