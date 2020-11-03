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
#include <memory>
#include <vector>
#include <map>
#include <iostream>

#define SCREEN_W 400
#define SCREEN_H 440
#define BLOCK_SIZE 20
#define LINES 20
#define COLUMNS 10
#define SHIFT_X 20
#define SHIFT_Y 20

int main(){
	const int speeds[] = {500,450,400,350,300,250,200,150,100};
	//std::vector<std::vector<bool>> vec(4, std::vector<bool>(4, true));
	std::shared_ptr<Formato> format (new Formato("../assets/Formatos.dat"));
	std::shared_ptr<SDL_Model> sdl (new SDL_Model(SCREEN_W,SCREEN_H));
	std::shared_ptr<View> view (new View(sdl));
	std::shared_ptr<Sprite> sprite (new Sprite("../assets/Bloco.png",sdl));
	std::shared_ptr<Sprite> sprite2 (new Sprite("../assets/Fundo.png",sdl));
	std::shared_ptr<Sprite> sprite3 (new Sprite("../assets/score.png",sdl));
	std::shared_ptr<Map> map (new Map(COLUMNS,LINES,BLOCK_SIZE,BLOCK_SIZE));
	std::shared_ptr<Image> img (new Image(SHIFT_X, SHIFT_Y,BLOCK_SIZE*COLUMNS,BLOCK_SIZE*LINES,sprite2));
	std::shared_ptr<Image> end_screen (new Image(SCREEN_W/2-2*BLOCK_SIZE,SCREEN_H/2-2*BLOCK_SIZE,4*BLOCK_SIZE,2*BLOCK_SIZE,sprite3));
	std::shared_ptr<Bloco> block (new Bloco(COLUMNS/2,-5,format->get_random(),sprite,BLOCK_SIZE,BLOCK_SIZE));
	std::shared_ptr<BlockPosition> blk_pos(new BlockPosition(SHIFT_X, SHIFT_Y, sdl));
	std::shared_ptr<Collision> collision (new Collision(map));
	std::vector<std::shared_ptr<Sprite>> vecin;
	vecin.push_back(sprite);
	vecin.push_back(sprite2);
	map->set_sprites(vecin);

	std::shared_ptr<Keyboard> key (new Keyboard(block));
	std::shared_ptr<Player> player (new Player(block, key, speeds[0]));
	std::vector<std::shared_ptr<Player>> player_vec;
	player_vec.push_back(player);
	std::shared_ptr<MainController> ctrl (new MainController(map, player_vec, format));

	std::shared_ptr<Image> score (new Image(BLOCK_SIZE*(3+COLUMNS),2*BLOCK_SIZE,4*BLOCK_SIZE,2*BLOCK_SIZE,sprite3));

	while(1){
		if(key->Quit()) break;
		ctrl->step();
		if(!player_vec[0]->is_alive())
			break;
		std::vector<std::shared_ptr<Image>> prints = blk_pos->create_image_vector(player_vec[0]->get_piece());
		std::vector<std::shared_ptr<Image>> prints2 = blk_pos->create_image_vector(map);
		std::vector<std::shared_ptr<Image>> prints3 = blk_pos->create_score_image(player_vec[0]->get_points(), BLOCK_SIZE*(2+COLUMNS), 4*BLOCK_SIZE, BLOCK_SIZE);
	
		prints.insert(prints.end(), prints2.begin(),prints2.end());		
		prints.insert(prints.end(), prints3.begin(),prints3.end());
		prints.insert(prints.end(), score);		

		prints.insert(prints.begin(),img);
		view->render(prints);
	
		player_vec[0]->set_speed(speeds[player_vec[0]->get_lines_completed()/10]);
		SDL_Delay(50);		
	}
	
	std::vector<std::shared_ptr<Image>> prints = blk_pos->create_score_image(player_vec[0]->get_points(), BLOCK_SIZE*(COLUMNS/2-1), SCREEN_H/2, 2*BLOCK_SIZE);
	prints.insert(prints.end(), end_screen);
	
	while(1){
		if(key->Quit()) break;

		view->render(prints);
		SDL_Delay(50);		
	}
	
	
	return 0;
}
