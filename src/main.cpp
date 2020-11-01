#include "SDL_Model.hpp"
#include "Sprite.hpp"
#include "Bloco.hpp"
#include "Map.hpp"
#include "View.hpp"
#include "Image.hpp"
#include "Formato.hpp"
#include "BlockPosition.hpp"
#include <memory>
#include <vector>
#include <iostream>

int main(){
	std::vector<std::vector<bool>> vec(4, std::vector<bool>(4, true));
	std::shared_ptr<Formato> format (new Formato("../assets/Formatos.dat"));
	std::shared_ptr<SDL_Model> sdl (new SDL_Model(200,400));
	std::shared_ptr<View> view (new View(sdl));
	std::shared_ptr<Sprite> sprite (new Sprite("../assets/Bloco.png",sdl));
	std::shared_ptr<Sprite> sprite2 (new Sprite("../assets/Fundo.png",sdl));
	std::shared_ptr<Map> map (new Map(10,20,20,20));
	std::shared_ptr<Bloco> block (new Bloco(0,0,vec,sprite,20,20));
	std::shared_ptr<Image> img (new Image(0,0,200,400,sprite2));
	std::shared_ptr<BlockPosition> blk_pos(new BlockPosition(20, 20));
	std::vector<std::shared_ptr<Sprite>> vecin;
	vecin.push_back(sprite);
	vecin.push_back(sprite2);
	map->set_sprites(vecin);
	map->add_to_map(block,1);

	std::vector<std::shared_ptr<Image>> prints = blk_pos->create_image_vector(map);
	view->render(prints);
	
	while(1);

	return 0;
}
