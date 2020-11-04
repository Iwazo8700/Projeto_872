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
	std::shared_ptr<Map> map (new Map(COLUMNS,LINES,BLOCK_SIZE_Y,BLOCK_SIZE_X));
	std::shared_ptr<Image> img (new Image(SHIFT_X, SHIFT_Y,BLOCK_SIZE_X*COLUMNS,BLOCK_SIZE_Y*LINES,sprite2));
	std::shared_ptr<Image> end_screen (new Image(SCREEN_W/2-2*BLOCK_SIZE_X,SCREEN_H/2-2*BLOCK_SIZE_Y,4*BLOCK_SIZE_X,2*BLOCK_SIZE_Y,sprite3));
	std::shared_ptr<Bloco> block (new Bloco(COLUMNS/2,-5,format->get_random(),sprite,BLOCK_SIZE_Y,BLOCK_SIZE_X));
	std::shared_ptr<BlockPosition> blk_pos(new BlockPosition(SHIFT_X, SHIFT_Y, sdl));
	std::shared_ptr<Collision> collision (new Collision(map));
	std::vector<std::shared_ptr<Sprite>> vecin;
	vecin.push_back(sprite);
	vecin.push_back(sprite2);
	map->set_sprites(vecin);

	std::shared_ptr<Keyboard> key (new Keyboard(block, keyboard_time, num_lines));
	std::shared_ptr<Player> player (new Player(block, key, speed));
	std::vector<std::shared_ptr<Player>> player_vec;
	player_vec.push_back(player);
	std::shared_ptr<Image> score (new Image(BLOCK_SIZE_X*(COLUMNS*3/2),2*BLOCK_SIZE_Y,4*BLOCK_SIZE_X,2*BLOCK_SIZE_Y,sprite3));
	std::shared_ptr<IA> ia(new IA(player, -0.510066, 0.760666, -0.35663, -0.184483));
	std::shared_ptr<IAFunctions> iafunctions (new IAFunctions(ia, map, collision));
	std::vector<std::shared_ptr<IAFunctions>> iafunc_vec;
	iafunc_vec.push_back(iafunctions);
	std::shared_ptr<MainController> ctrl (new MainController(map, player_vec, format, iafunc_vec));

	bool normal = false; 
	if(normal){
	while(1){
		if(key->Quit()) break;
		ctrl->step();
		if(!player_vec[0]->is_alive())
			break;
		std::vector<std::shared_ptr<Image>> prints = blk_pos->create_image_vector(player_vec[0]->get_piece());
		std::vector<std::shared_ptr<Image>> prints2 = blk_pos->create_image_vector(map);
		std::vector<std::shared_ptr<Image>> prints3 = blk_pos->create_score_image(player_vec[0]->get_points(), BLOCK_SIZE_X*(3*COLUMNS/2-1), 4*BLOCK_SIZE_Y, BLOCK_SIZE_X);
	
		prints.insert(prints.end(), prints2.begin(),prints2.end());		
		prints.insert(prints.end(), prints3.begin(),prints3.end());
		prints.insert(prints.end(), score);		

		prints.insert(prints.begin(),img);
		view->render(prints);
	
		player_vec[0]->set_speed(speed - ((player_vec[0]->get_lines_completed()/decrease_n)*decrease));
		SDL_Delay(delay);		
	}
	
	std::vector<std::shared_ptr<Image>> prints = blk_pos->create_score_image(player_vec[0]->get_points(), BLOCK_SIZE_X*(COLUMNS/2-1), SCREEN_H/2, 2*BLOCK_SIZE_X);
	prints.insert(prints.end(), end_screen);
	
	while(1){
		if(key->Quit()) break;

		view->render(prints);
		SDL_Delay(50);		
	}
	
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
		view->render(prints);
	
		iafunctions->get_IA()->get_player()->set_speed(speed - ((iafunctions->get_IA()->get_player()->get_lines_completed()/decrease_n)*decrease));
		SDL_Delay(50);		
	}
	std::vector<std::shared_ptr<Image>> prints = blk_pos->create_score_image(iafunctions->get_IA()->get_player()->get_points(), BLOCK_SIZE_X*(COLUMNS/2-1), SCREEN_H/2, 2*BLOCK_SIZE_X);
	prints.insert(prints.end(), end_screen);
	
	while(1){
		if(key->Quit()) break;

		view->render(prints);
		SDL_Delay(50);		
	}

	
	
	
	}


	return 0;
}
