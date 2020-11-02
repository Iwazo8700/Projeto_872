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

int main(){
	//std::vector<std::vector<bool>> vec(4, std::vector<bool>(4, true));
	std::shared_ptr<Formato> format (new Formato("../assets/Formatos.dat"));
	std::shared_ptr<SDL_Model> sdl (new SDL_Model(200,400));
	std::shared_ptr<View> view (new View(sdl));
	std::shared_ptr<Sprite> sprite (new Sprite("../assets/Bloco.png",sdl));
	std::shared_ptr<Sprite> sprite2 (new Sprite("../assets/Fundo.png",sdl));
	std::shared_ptr<Sprite> sprite3 (new Sprite("../assets/luffy.png",sdl));
	std::shared_ptr<Map> map (new Map(10,20,20,20));
	std::shared_ptr<Image> img (new Image(0,0,200,400,sprite2));
	std::shared_ptr<Image> end_screen (new Image(0,0,200,400,sprite3));
	std::shared_ptr<Bloco> block (new Bloco(0,-5,format->get_random(),sprite,20,20));
	std::shared_ptr<BlockPosition> blk_pos(new BlockPosition(0, 0));
	std::shared_ptr<Collision> collision (new Collision(map));
	std::vector<std::shared_ptr<Sprite>> vecin;
	vecin.push_back(sprite);
	vecin.push_back(sprite2);
	map->set_sprites(vecin);

//	map->add_to_map(block,1);

	//std::vector<std::shared_ptr<Image>> prints = blk_pos->create_image_vector(map);
	

	std::shared_ptr<Keyboard> key (new Keyboard(block));
	std::shared_ptr<Player> player (new Player(block, key, 200));
	std::vector<std::shared_ptr<Player>> player_vec;
	player_vec.push_back(player);
	std::shared_ptr<MainController> ctrl (new MainController(map, player_vec, format));

	while(1){
		if(key->Quit()) break;
/*		if (!(key->Read(block))) break;
		prints = blk_pos->create_image_vector(block);
		view->render(prints);
		SDL_Delay(100);	*/
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
	
	
	std::vector<std::shared_ptr<Image>> prints;
	prints.push_back(end_screen);
	std::cout << player_vec[0]->get_points() << std::endl;

	while(1){
		if(key->Quit()) break;

		view->render(prints);
		SDL_Delay(50);		
	}
	
	
	return 0;
}
