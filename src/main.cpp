#include "SDL_Model.hpp"
#include <string> 
#include "Sprite.hpp"
#include "Bloco.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "View.hpp"
#include "Image.hpp"
#include "Formato.hpp"
#include "MainController.hpp"
#include "Collision.hpp"
#include "BlockPosition.hpp"
#include "Keyboard.hpp"
#include "ConfigReader.hpp"
#include "IA.hpp"
#include "IAFunctions.hpp"
#include <memory>
#include <vector>
#include <map>
#include <iostream>
#include<bits/stdc++.h>
#include <cstdlib>

int main(){
	std::shared_ptr<ConfigReader> config (new ConfigReader("../assets/config"));

	int speed = config->get_speed();
	int delay = config->get_delay();
	int keyboard_time = config->get_keyboard_time();
	int decrease = config->get_decrease();
	int decrease_n = config->get_decrease_n();
	int SCREEN_W = config->get_screen_width();
	int SCREEN_H = config->get_screen_height();
	int BLOCK_SIZE_X = config->get_block_size_x();
	int BLOCK_SIZE_Y = config->get_block_size_y();
	int LINES = config->get_lines();
	int num_lines = config->get_num_lines();
	int COLUMNS = config->get_columns();
	int SHIFT_X = config->get_shift_x();
	int SHIFT_Y = config->get_shift_y();

	std::shared_ptr<Formato> format (new Formato("../assets/Formatos.dat"));
	std::shared_ptr<SDL_Model> sdl (new SDL_Model(SCREEN_W,SCREEN_H));
	std::shared_ptr<View> view (new View(sdl));
	std::shared_ptr<Sprite> sprite (new Sprite("../assets/Bloco.png",sdl));
	std::shared_ptr<Sprite> sprite2 (new Sprite("../assets/Fundo.png",sdl));
	std::shared_ptr<Sprite> sprite3 (new Sprite("../assets/score.png",sdl));
	//std::shared_ptr<Map> map (new Map(COLUMNS,LINES,BLOCK_SIZE_Y,BLOCK_SIZE_X));
	std::shared_ptr<Image> img (new Image(SHIFT_X, SHIFT_Y,BLOCK_SIZE_X*COLUMNS,BLOCK_SIZE_Y*LINES,sprite2));
	std::shared_ptr<Image> end_screen (new Image(SCREEN_W/2-2*BLOCK_SIZE_X,SCREEN_H/2-2*BLOCK_SIZE_Y,4*BLOCK_SIZE_X,2*BLOCK_SIZE_Y,sprite3));
	std::shared_ptr<Bloco> block (new Bloco(COLUMNS/2,-5,format->get_random(),sprite,BLOCK_SIZE_Y,BLOCK_SIZE_X));
	std::shared_ptr<BlockPosition> blk_pos(new BlockPosition(SHIFT_X, SHIFT_Y, sdl));
	//std::shared_ptr<Collision> collision (new Collision(map));

	std::shared_ptr<Keyboard> key (new Keyboard(block, keyboard_time, num_lines));

	std::shared_ptr<Image> score (new Image(BLOCK_SIZE_X*(COLUMNS*3/2),2*BLOCK_SIZE_Y,4*BLOCK_SIZE_X,2*BLOCK_SIZE_Y,sprite3));

	std::vector<std::shared_ptr<IA>> ia_vec;
	float a,b,c,d;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-1, 1);
	dis(gen);
	std::vector<std::shared_ptr<Player>> player_vec;
	int repeticoes = 3;
	int EPOCH = 100;
	int REMOVE;
	int CROSSOVER;
	int BATCH = 50;
	for(int i=0; i<BATCH; i++){
		std::shared_ptr<Player> player (new Player(block, key, speed));
		player_vec.push_back(player);
		//std::shared_ptr<IA> ia(new IA(player_vec[i], -0.510066, 0.760666, -0.35663, -0.184483));
		std::shared_ptr<IA> ia(new IA(player_vec[i], dis(gen), dis(gen), dis(gen), dis(gen)));	
		ia_vec.push_back(ia);
	}
	for(int epoch = 0; epoch < EPOCH; epoch++){
		std::cout << "-----------------------" <<"Epoch: " <<  epoch << "-----------------------"  << std::endl;
		for(int i=0; i<ia_vec.size(); i++){
			//SDL_Delay(100);		
			for(int j = 0; j < repeticoes; j++){
				std::shared_ptr<Map> map (new Map(COLUMNS,LINES,BLOCK_SIZE_Y,BLOCK_SIZE_X));
				std::vector<std::shared_ptr<Sprite>> vecin;
				vecin.push_back(sprite);
				vecin.push_back(sprite2);
				map->set_sprites(vecin);
				std::shared_ptr<Collision> collision (new Collision(map));
				std::shared_ptr<IAFunctions> iafunctions (new IAFunctions(ia_vec[i], map, collision));
				std::shared_ptr<MainController> ctrl (new MainController(map, player_vec, format, ia_vec));
				while(1){
					if(key->Quit()) break;
					ctrl->IAstep(iafunctions, i);
					if(!ia_vec[i]->get_player()->is_alive()){
						break;}
					//std::vector<std::shared_ptr<Image>> prints = blk_pos->create_image_vector(ia_vec[i]->get_player()->get_piece());
					
					//std::vector<std::shared_ptr<Image>> prints2 = blk_pos->create_image_vector(map);
					
					//std::vector<std::shared_ptr<Image>> prints3 = blk_pos->create_score_image(ia_vec[i]->get_player()->get_points(), BLOCK_SIZE_X*(3*COLUMNS/2-1), 4*BLOCK_SIZE_Y, BLOCK_SIZE_X);
					
					//prints.insert(prints.end(), prints2.begin(),prints2.end());		
					//prints.insert(prints.end(), prints3.begin(),prints3.end());
					//prints.insert(prints.end(), score);		

					//prints.insert(prints.begin(),img);
					//view->render(prints);
					
					ia_vec[i]->get_player()->set_speed(speed - ((ia_vec[i]->get_player()->get_lines_completed()/decrease_n)*decrease));
				//	SDL_Delay(50);		
				}
				//std::cout << " IA: " << i << " Repeticao: " << j << std::endl;
				//std::cout<<ia_vec[i]->get_a()<<" | "<<ia_vec[i]->get_b()<<" | "<<ia_vec[i]->get_c()<<" | "<<ia_vec[i]->get_d()<<" | "<<ia_vec[i]->get_player()->get_points()<<std::endl; 
				ia_vec[i]->get_player()->Revive();
			}
			//ia_vec[i]->get_player()->set_points(points);

		}
	

		//std::cout << "-----------------------" << "Pesos e Score antes das mudanças" << "-----------------------" << std::endl;
		for(int ii=0; ii < ia_vec.size(); ii++){
			if(ia_vec[ii]->get_player()->get_points()/10 > 1000000)
				std::cout<<ia_vec[ii]->get_a()<<" | "<<ia_vec[ii]->get_b()<<" | "<<ia_vec[ii]->get_c()<<" | "<<ia_vec[ii]->get_d()<<" | "<<ia_vec[ii]->get_player()->get_points()<<std::endl; 
		}
		
		std::shared_ptr<Map> map (new Map(COLUMNS,LINES,BLOCK_SIZE_Y,BLOCK_SIZE_X));
		std::vector<std::shared_ptr<Sprite>> vecin;
		vecin.push_back(sprite);
		vecin.push_back(sprite2);
		map->set_sprites(vecin);
		std::shared_ptr<Collision> collision (new Collision(map));
		std::shared_ptr<MainController> ctrl (new MainController(map, player_vec, format, ia_vec));
		REMOVE = (int) (ia_vec.size()*0.3);
		CROSSOVER = (int) (ia_vec.size()*0.1);	
		ia_vec = ctrl->Fitness();
		ia_vec.erase(ia_vec.end()-REMOVE, ia_vec.end());
		
		for(int ii=0; ii<CROSSOVER; ii++){
			ia_vec.push_back(ctrl->Crossover(ia_vec[ii], ia_vec[ii+1]));
		}
		
		for(int ii=0; ii<ia_vec.size(); ii++){
			ia_vec[ii] = ctrl->Mutation(ia_vec[ii]);
		}
		if(ia_vec.size() < BATCH){
			for(int i=0; i<BATCH-ia_vec.size(); i++){
				std::shared_ptr<Player> player (new Player(block, key, speed));
				player_vec.push_back(player);
				//std::shared_ptr<IA> ia(new IA(player_vec[i], -0.510066, 0.760666, -0.35663, -0.184483));
				std::shared_ptr<IA> ia(new IA(player_vec[i], dis(gen), dis(gen), dis(gen), dis(gen)));	
				ia_vec.push_back(ia);
			}
		}
		//std::cout << "-----------------------" << "Pesos e Score depois das mudanças" << "-----------------------" << std::endl;
		for(int ii=0; ii < ia_vec.size(); ii++){
			ia_vec[ii]->get_player()->set_points(0);
			//std::cout<<ia_vec[ii]->get_a()<<" | "<<ia_vec[ii]->get_b()<<" | "<<ia_vec[ii]->get_c()<<" | "<<ia_vec[ii]->get_d()<<" | "<<ia_vec[ii]->get_player()->get_points()<<std::endl; 
		}

	}


	return 0;
}
