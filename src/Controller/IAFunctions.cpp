#include "IAFunctions.hpp"



IAFunctions::IAFunctions(std::shared_ptr<IA> ia, std::shared_ptr<Map> map, std::shared_ptr<Collision> collision){
	this->ia = ia;
	this->tmp_map = std::make_shared<Map>(*map);
	this->map = map;
	this->collision = collision;
}

void IAFunctions::set_Map(std::shared_ptr<Map> map){
	this->tmp_map = std::make_shared<Map>(*map);
}
std::shared_ptr<Map> IAFunctions::get_Map(){
	return tmp_map;
}

std::shared_ptr<IA> IAFunctions::get_IA(){
	return this->ia;
}

void IAFunctions::set_IA(std::shared_ptr<IA> ia){
	this->ia = ia;
}

int IAFunctions::AggregateHeights(){
	std::vector<std::vector<int>> matrix = tmp_map->get_map();
	int retorno = 0;
	for(int i=0; i<matrix.size(); i++){
		for(int j=0; j<matrix[i].size(); j++){
			retorno+=matrix[i][j];
		}
	}
	//std::cout << "Aggregate" << std::endl;
	return retorno;
}

int IAFunctions::CompleteLines(){
	std::vector<std::vector<int>> matrix = tmp_map->get_map();
	int retorno = 0;
	bool line;
	for(int i=0; i<matrix.size(); i++){
		line = true;
		for(int j=0; j<matrix[i].size(); j++){
			if(matrix[i][j]){
				line=false;
				break;
			}
		}
		if(line) retorno++;
	}
	//std::cout << "Lines" << std::endl;
	return retorno;
}

int IAFunctions::Holes(){
	std::vector<std::vector<int>> matrix = tmp_map->get_map();
	int retorno = 0;
	bool hole;
	for(int j=0; j<matrix[0].size(); j++){
		hole = false;
		for(int i=0; i<matrix.size(); i++){
			if(matrix[i][j]) hole=true;
			if(hole && !matrix[i][j]) retorno++;
		}
	}
	//std::cout << "Holes" << std::endl;
	return retorno;
}


int IAFunctions::Bumpiness(){
	std::vector<std::vector<int>> matrix = tmp_map->get_map();
	std::vector<int> heights;
	int line;
	for(int j=0; j<matrix[0].size(); j++){
		line = true;
		for(int i=0; i<matrix.size(); i++){
			if(matrix[i][j]){
				heights.push_back(matrix.size()-i);
				line = false;
				break;
			}
		}
		if(line) heights.push_back(0);
	}
	int retorno = 0;
	for(int i=0; i<heights.size()-1; i++){
		//std::cout << heights[i] << std::endl;
		retorno += std::abs(heights[i]-heights[i+1]);
	}
	//std::cout << "Bump2" << std::endl;

	return retorno;
}


float IAFunctions::Score(){
	return this->ia->get_a()*AggregateHeights() + this->ia->get_b()*CompleteLines() + this->ia->get_c()*Holes() + this->ia->get_d()*Bumpiness();
}

std::shared_ptr<Bloco> IAFunctions::TestAll(){
	std::vector<std::vector<int>> matrix = map->get_map();
	std::shared_ptr<Bloco> block = ia->get_player()->get_piece();
	std::shared_ptr<Keyboard> keyboard = ia->get_player()->get_keyboard();
	std::shared_ptr<Player> player = ia->get_player();
	int tmp;
        std::shared_ptr<Bloco> tmp_blk;
	//std::cout << "Score0" <<std::endl;	
	float score = Score();
	//std::cout << "Score1" <<std::endl;	
	float tmp_score;
	std::shared_ptr<Bloco> return_block = player->get_piece();

	for(int i=0; i<4; i++){
		//std::cout << i <<std::endl;
		for(int j=0; j<matrix.size(); j++){
			//std::cout << j <<std::endl;
			this->tmp_map = std::make_shared<Map>(*map);
			tmp = player->get_piece()->get_x();
                	player->get_piece()->set_x(j);
                	if(this->collision->is_colliding(player->get_piece()))
                        	player->get_piece()->set_x(tmp);

			
                	player->get_piece()->set_y(player->get_keyboard()->Down(this->collision));
			tmp_map->add_to_map(player->get_piece(), 1);
			tmp_score = Score();
			if(tmp_score > score){
				score = tmp_score;
				return_block = player->get_piece();
			}
		}
                tmp_blk = std::make_shared<Bloco>(*(player->get_piece()));
                tmp_blk->set_formato(player->get_keyboard()->RotHoraria());
                if(!this->collision->is_colliding(tmp_blk))
                       	player->get_piece()->set_formato(tmp_blk->get_formato());
	
	}
	return return_block;
}





