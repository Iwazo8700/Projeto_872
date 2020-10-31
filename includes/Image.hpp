#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Sprite.hpp"
#include <memory>

class Image{
	private:
		SDL_Rect target;
		std::shared_ptr<Sprite> sprite;
	public:
		Image(int x, int y, int width, int height, std::shared_ptr<Sprite> sprite);
		SDL_Rect* get_target();
		SDL_Texture* get_texture();
};		
