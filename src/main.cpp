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
#include "Container.hpp"
#include "IAFunctions.hpp"
#include <memory>
#include <vector>
#include <map>
#include <iostream>
#include <chrono>
#include "json.hpp"
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

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
	int thickness = config->get_thickness();
	int r = config->get_r();
	int g = config->get_g();
	int b = config->get_b();
	int block_r = config->get_block_r();
	int block_g = config->get_block_g();
	int block_b = config->get_block_b();
	bool normal = config->get_normal();

	std::shared_ptr<Formato> format (new Formato("../assets/Formatos.dat"));
	std::shared_ptr<SDL_Model> sdl (new SDL_Model(SCREEN_W,SCREEN_H));
	std::shared_ptr<View> view (new View(sdl));
	std::shared_ptr<Sprite> sprite (new Sprite(sdl,""));
	std::shared_ptr<Sprite> sprite2 (new Sprite(sdl,""));
	sprite2->set_texture(sdl->create_map_texture(LINES,COLUMNS,BLOCK_SIZE_X,BLOCK_SIZE_Y,thickness,r,g,b));
	sprite->set_texture(sdl->create_block_texture(BLOCK_SIZE_X,BLOCK_SIZE_Y,block_r,block_g,block_b));
	std::shared_ptr<Sprite> sprite3 (new Sprite(sdl, "../assets/score.png"));
	std::shared_ptr<Map> map (new Map(COLUMNS,LINES,BLOCK_SIZE_X,BLOCK_SIZE_Y));
	std::shared_ptr<Image> img (new Image(SHIFT_X, SHIFT_Y,BLOCK_SIZE_X*COLUMNS,BLOCK_SIZE_Y*LINES,sprite2));
	std::shared_ptr<Image> end_screen (new Image(SCREEN_W/2-2*BLOCK_SIZE_X,SCREEN_H/2-2*BLOCK_SIZE_Y,4*BLOCK_SIZE_X,2*BLOCK_SIZE_Y,sprite3));
	std::shared_ptr<Bloco> block (new Bloco(COLUMNS/2,-5,format->get_random(),sprite,BLOCK_SIZE_Y,BLOCK_SIZE_X));
	std::shared_ptr<BlockPosition> blk_pos(new BlockPosition(SHIFT_X, SHIFT_Y, sdl));
	std::shared_ptr<Collision> collision (new Collision(map));
	std::vector<std::shared_ptr<Sprite>> vecin;
	vecin.push_back(sprite);
	vecin.push_back(sprite2);
	map->set_sprites(vecin);

	
	std::shared_ptr<MainController> ctrl;
	std::shared_ptr<IA> ia;
	std::vector<std::shared_ptr<IAFunctions>> iafunc_vec;
	std::shared_ptr<IAFunctions> iafunctions;
	std::shared_ptr<Keyboard> key (new Keyboard(block, keyboard_time, num_lines));
	std::shared_ptr<Player> player (new Player(block, key, speed));
	std::vector<std::shared_ptr<Player>> player_vec;
	player_vec.push_back(player);
	
	if(normal)
		 ctrl = std::shared_ptr<MainController>(new MainController(map, player_vec, format));
	else{
		ia = std::shared_ptr<IA>(new IA(player, -0.510066, 0.760666, -0.35663, -0.184483));
		iafunctions = std::shared_ptr<IAFunctions>(new IAFunctions(ia, map, collision));
		iafunc_vec.push_back(iafunctions);
		ctrl = std::shared_ptr<MainController>(new MainController(map, player_vec, format, iafunc_vec));
	}

	std::shared_ptr<Image> score (new Image(SCREEN_W*3/4-2*BLOCK_SIZE_X,2*BLOCK_SIZE_Y,4*BLOCK_SIZE_X,2*BLOCK_SIZE_Y,sprite3));

	json j;

	char v[120];
	boost::asio::io_service my_io_service;
	udp::endpoint local_endpoint(udp::v4(), 9001);
	udp::socket my_socket(my_io_service,local_endpoint);
	udp::endpoint remote_endpoint;
	my_socket.receive_from(boost::asio::buffer(v,120),remote_endpoint);
	 
	if(normal){
		while(1){
			auto start = std::chrono::steady_clock::now();
			if(key->Quit()) break;

			ctrl->step();

			if(!player_vec[0]->is_alive())
				break;

			
			std::vector<std::shared_ptr<Image>> prints = blk_pos->create_image_vector(player_vec[0]->get_piece());
			std::vector<std::shared_ptr<Image>> prints2 = blk_pos->create_image_vector(map);
			std::vector<std::shared_ptr<Image>> prints3 = blk_pos->create_score_image(player_vec[0]->get_points(), SCREEN_W*3/4-3*BLOCK_SIZE_X, 4*BLOCK_SIZE_Y, BLOCK_SIZE_X);
		
			prints.insert(prints.end(), prints2.begin(),prints2.end());		
			prints.insert(prints.end(), prints3.begin(),prints3.end());
			prints.insert(prints.end(), score);		

			prints.insert(prints.begin(),img);
			view->render(prints);
			

			player_vec[0]->set_speed(speed - ((player_vec[0]->get_lines_completed()/decrease_n)*decrease));
			
			int tmp_count = 0;
			std::vector<Container> containers(player_vec.size());
			for(auto plyr : player_vec){
				containers[tmp_count++].set_data(*plyr,*(plyr->get_piece()));
			}

			j["Players"] = containers;
			j["Map"] = *map;
			j["Over"] = false;
			my_socket.send_to(boost::asio::buffer(j.dump()), remote_endpoint);

			auto end = std::chrono::steady_clock::now();
			std::chrono::duration<double> diff = end-start;
			if(diff.count()/1000 < delay)
				SDL_Delay(delay-diff.count()/1000);


			if(key->Save()){
				int tmp_count = 0;
				std::vector<Container> containers(player_vec.size());
				for(auto plyr : player_vec){
					containers[tmp_count++].set_data(*plyr,*(plyr->get_piece()));
				}

				j["Players"] = containers;
				j["Map"] = *map;
				std::ofstream o("../assets/savefile.json");
				o << j << std::endl;
			}
			if(key->Load()){
				std::ifstream i("../assets/savefile.json");
  				if (i.is_open() ) {
    					i >> j;
    					i.close();
					std::vector<Container> containers;
					int player_num = 0;
					for(auto plyr : player_vec){
						plyr->set_points(j["Players"][player_num]["player"]["points"]);
						plyr->set_speed(j["Players"][player_num]["player"]["speed"]);
						plyr->set_lines_completed(j["Players"][player_num]["player"]["lines_completed"]);
						map->set_map(j["Players"][player_num]["map"]["map"]);
						plyr->get_piece()->set_formato(j["Players"][player_num]["block"]["formato"]);
						plyr->get_piece()->set_x(j["Players"][player_num]["block"]["x"]);
						plyr->get_piece()->set_y(j["Players"][player_num]["block"]["y"]);
						player_num++;
					}
  				} else {
    					std::cout << "Erro ao tentar ler arquivo de saves!" << std::endl;
  				}
			}
		}
		
		std::vector<std::shared_ptr<Image>> prints = blk_pos->create_score_image(player_vec[0]->get_points(), SCREEN_W/2-BLOCK_SIZE_X*6, SCREEN_H/2, 2*BLOCK_SIZE_X);
		prints.insert(prints.end(), end_screen);
		
		while(1){
			if(key->Quit()) break;
			
			view->render(prints);
			SDL_Delay(50);		
		}

		j["Over"] = true;
		my_socket.send_to(boost::asio::buffer(j.dump()), remote_endpoint);
		
	}else{
		while(1){
			if(key->Quit()) break;
			ctrl->IAstep();
			if(!iafunctions->get_IA()->get_player()->is_alive())
				break;
			
			/*teste = map->get_map();
			for(int i=0; i<teste.size(); i++){
				for(int j=0; j<teste[i].size(); j++){
					std::cout << teste[i][j];
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
			*/
			std::vector<std::shared_ptr<Image>> prints = blk_pos->create_image_vector(iafunctions->get_IA()->get_player()->get_piece());
			std::vector<std::shared_ptr<Image>> prints2 = blk_pos->create_image_vector(map);
			std::vector<std::shared_ptr<Image>> prints3 = blk_pos->create_score_image(iafunctions->get_IA()->get_player()->get_points(), BLOCK_SIZE_X*(3*COLUMNS/2-1), 4*BLOCK_SIZE_Y, BLOCK_SIZE_X);
			
		
			prints.insert(prints.end(), prints2.begin(),prints2.end());		
			prints.insert(prints.end(), prints3.begin(),prints3.end());
			prints.insert(prints.end(), score);		

			prints.insert(prints.begin(),img);
			//view->render(prints);
		
			iafunctions->get_IA()->get_player()->set_speed(speed - ((iafunctions->get_IA()->get_player()->get_lines_completed()/decrease_n)*decrease));
			SDL_Delay(50);		
		}
		std::vector<std::shared_ptr<Image>> prints = blk_pos->create_score_image(iafunctions->get_IA()->get_player()->get_points(), BLOCK_SIZE_X*(COLUMNS/2-1), SCREEN_H/2, 2*BLOCK_SIZE_X);
		prints.insert(prints.end(), end_screen);
		
		while(1){
			if(key->Quit()) break;

			//view->render(prints);
			SDL_Delay(50);		
		}

		
		
		
	}


	return 0;
}
