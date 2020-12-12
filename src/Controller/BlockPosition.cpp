#include "BlockPosition.hpp"

BlockPosition::BlockPosition(int x, int y, std::shared_ptr<SDL_Model> sdl){
	this->x_begin = x;
	this->y_begin = y;
	this->numbers.push_back(std::shared_ptr<Sprite>(new Sprite(sdl,"../assets/0.png")));
	this->numbers.push_back(std::shared_ptr<Sprite>(new Sprite(sdl,"../assets/1.png")));
	this->numbers.push_back(std::shared_ptr<Sprite>(new Sprite(sdl,"../assets/2.png")));
	this->numbers.push_back(std::shared_ptr<Sprite>(new Sprite(sdl,"../assets/3.png")));
	this->numbers.push_back(std::shared_ptr<Sprite>(new Sprite(sdl,"../assets/4.png")));
	this->numbers.push_back(std::shared_ptr<Sprite>(new Sprite(sdl,"../assets/5.png")));
	this->numbers.push_back(std::shared_ptr<Sprite>(new Sprite(sdl,"../assets/6.png")));
	this->numbers.push_back(std::shared_ptr<Sprite>(new Sprite(sdl,"../assets/7.png")));
	this->numbers.push_back(std::shared_ptr<Sprite>(new Sprite(sdl,"../assets/8.png")));
	this->numbers.push_back(std::shared_ptr<Sprite>(new Sprite(sdl,"../assets/9.png")));
}

std::vector<std::shared_ptr<Image>> BlockPosition::create_image_vector(std::shared_ptr<Bloco> block){
	int i = 0, j=0;
	int x = block->get_x();
	int y = block->get_y();
	int w = block->get_width();
	int h = block->get_height();
	std::vector<std::vector<bool>> vec = block->get_formato();
	std::shared_ptr<Sprite> texture = block->get_sprite();
	std::vector<std::shared_ptr<Image>> images(0,0);

	for(auto squares : vec){
		for(auto square : squares){
			if(square){
				std::shared_ptr<Image> img (new Image(this->x_begin+((x+j)*w),this->y_begin+((y+i)*h),w,h,texture));
				images.push_back(img);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return images;
}

std::vector<std::shared_ptr<Image>> BlockPosition::create_image_vector(std::shared_ptr<Map> map){
	int i = 0, j=0;
	int w = map->get_block_width();
	int h = map->get_block_height();
	std::vector<std::vector<int>> vec = map->get_map();
	std::vector<std::shared_ptr<Image>> images;
	
	for(std::vector<int> squares : vec){
		for(int square : squares){
			if(square){
				std::shared_ptr<Image> img (new Image(this->x_begin+(j*w),this->y_begin+(i*h),w,h,map->get_texture(i,j)));
				images.push_back(img);
			}
			j++;
		}
		j = 0;
		i++;
	}
	
	return images;
}

std::vector<std::shared_ptr<Image>> BlockPosition::create_score_image(int num, int x_0, int y_0, int size){
	std::vector<std::shared_ptr<Image>> prints;
	int points = num;
	int i;

	for(i = 5; i >= 0; i--,points=points/10)
		prints.push_back(std::shared_ptr<Image>(new Image(x_0+i*size,y_0,size,size, this->numbers[points%10])));
	return prints;
}

std::vector<std::shared_ptr<Image>> BlockPosition::create_block_image(int x_0, int y_0, int size, std::shared_ptr<Sprite> sprite){
	std::vector<std::shared_ptr<Image>> prints;
	prints.push_back(std::shared_ptr<Image>(new Image(x_0,y_0,size,size,sprite)));
	return prints;
}
