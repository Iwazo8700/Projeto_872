#include "SDL_Model.hpp"
#include "Sprite.hpp"
#include "Bloco.hpp"
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
	std::shared_ptr<Map> map (new Map(10,20,20,20));
	std::shared_ptr<Image> img (new Image(0,0,200,400,sprite2));
	std::shared_ptr<Bloco> block (new Bloco(0,0,format->get_L(),sprite,20,20));
	std::shared_ptr<BlockPosition> blk_pos(new BlockPosition(0, 0));
	std::shared_ptr<Collision> collision (new Collision(map));
	std::vector<std::shared_ptr<Sprite>> vecin;
	vecin.push_back(sprite);
	vecin.push_back(sprite2);
	map->set_sprites(vecin);
	std::shared_ptr<std::map<int, std::shared_ptr<Bloco>>> b_map (new std::map<int, std::shared_ptr<Bloco>>());
	std::shared_ptr<std::map<int, std::shared_ptr<Keyboard>>> k_map (new std::map<int, std::shared_ptr<Keyboard>>());
	

//	map->add_to_map(block,1);

	//std::vector<std::shared_ptr<Image>> prints = blk_pos->create_image_vector(map);
	

	std::shared_ptr<Keyboard> key (new Keyboard(block));
	b_map->insert({0,block});	
	k_map->insert({0,key});	
	std::shared_ptr<MainController> ctrl (new MainController(map, b_map, k_map, collision, 300));

	while(1){
		if(key->Quit()) break;
/*		if (!(key->Read(block))) break;
		prints = blk_pos->create_image_vector(block);
		view->render(prints);
		SDL_Delay(100);	*/
		ctrl->step();
		std::vector<std::shared_ptr<Image>> prints = blk_pos->create_image_vector(b_map->find(0)->second);
		std::vector<std::shared_ptr<Image>> prints2 = blk_pos->create_image_vector(map);
		
		prints.insert(prints.end(), prints2.begin(),prints2.end());		

		prints.insert(prints.begin(),img);
		view->render(prints);
		SDL_Delay(50);		
	}

	return 0;
}
