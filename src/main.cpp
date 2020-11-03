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

#define SCREEN_W 200
#define SCREEN_H 400
#define BLOCK_SIZE 20
#define LINES 20
#define COLUMNS 10

int main(){
	//std::vector<std::vector<bool>> vec(4, std::vector<bool>(4, true));
	std::shared_ptr<Formato> format (new Formato("../assets/Formatos.dat"));
	std::shared_ptr<SDL_Model> sdl (new SDL_Model(SCREEN_W,SCREEN_H));
	std::shared_ptr<View> view (new View(sdl));
	std::shared_ptr<Sprite> sprite (new Sprite("../assets/Bloco.png",sdl));
	std::shared_ptr<Sprite> sprite2 (new Sprite("../assets/Fundo.png",sdl));
	std::shared_ptr<Sprite> sprite3 (new Sprite("../assets/score.png",sdl));
	std::shared_ptr<Map> map (new Map(COLUMNS,LINES,BLOCK_SIZE,BLOCK_SIZE));
	std::shared_ptr<Image> img (new Image(0, 0,SCREEN_W,SCREEN_H,sprite2));
	std::shared_ptr<Image> end_screen (new Image(SCREEN_W/2-2*BLOCK_SIZE,SCREEN_H/2-2*BLOCK_SIZE,4*BLOCK_SIZE,2*BLOCK_SIZE,sprite3));
	std::shared_ptr<Bloco> block (new Bloco(COLUMNS/2,-5,format->get_random(),sprite,BLOCK_SIZE,BLOCK_SIZE));
	std::shared_ptr<BlockPosition> blk_pos(new BlockPosition(0, 0));
	std::shared_ptr<Collision> collision (new Collision(map));
	std::vector<std::shared_ptr<Sprite>> vecin;
	vecin.push_back(sprite);
	vecin.push_back(sprite2);
	map->set_sprites(vecin);

//	map->add_to_map(block,1);

	//std::vector<std::shared_ptr<Image>> prints = blk_pos->create_image_vector(map);
	

	std::shared_ptr<Keyboard> key (new Keyboard(block));
	std::shared_ptr<Player> player (new Player(block, key, 500));
	std::vector<std::shared_ptr<Player>> player_vec;
	player_vec.push_back(player);
	std::shared_ptr<MainController> ctrl (new MainController(map, player_vec, format));

	while(1){
		if(key->Quit()) break;
		ctrl->step();
		if(!player_vec[0]->is_alive())
			break;
		std::vector<std::shared_ptr<Image>> prints = blk_pos->create_image_vector(player_vec[0]->get_piece());
		std::vector<std::shared_ptr<Image>> prints2 = blk_pos->create_image_vector(map);
		
		prints.insert(prints.end(), prints2.begin(),prints2.end());		

		prints.insert(prints.begin(),img);
		view->render(prints);
		SDL_Delay(50);		
	}
	
	
	std::vector<std::shared_ptr<Sprite>> numbers;
	numbers.push_back(std::shared_ptr<Sprite>(new Sprite("../assets/0.png",sdl)));
	numbers.push_back(std::shared_ptr<Sprite>(new Sprite("../assets/1.png",sdl)));
	numbers.push_back(std::shared_ptr<Sprite>(new Sprite("../assets/2.png",sdl)));
	numbers.push_back(std::shared_ptr<Sprite>(new Sprite("../assets/3.png",sdl)));
	numbers.push_back(std::shared_ptr<Sprite>(new Sprite("../assets/4.png",sdl)));
	numbers.push_back(std::shared_ptr<Sprite>(new Sprite("../assets/5.png",sdl)));
	numbers.push_back(std::shared_ptr<Sprite>(new Sprite("../assets/6.png",sdl)));
	numbers.push_back(std::shared_ptr<Sprite>(new Sprite("../assets/7.png",sdl)));
	numbers.push_back(std::shared_ptr<Sprite>(new Sprite("../assets/8.png",sdl)));
	numbers.push_back(std::shared_ptr<Sprite>(new Sprite("../assets/9.png",sdl)));

	std::vector<std::shared_ptr<Image>> prints;
	prints.push_back(end_screen);
	int points = player_vec[0]->get_points();
	int i;

	for(i = 2; i > -3; i--,points=points/10)
		prints.push_back(std::shared_ptr<Image>(new Image(SCREEN_W/2+i*BLOCK_SIZE,SCREEN_H/2,BLOCK_SIZE,BLOCK_SIZE, numbers[points%10])));

	while(1){
		if(key->Quit()) break;

		view->render(prints);
		SDL_Delay(50);		
	}
	
	
	return 0;
}
