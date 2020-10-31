#pragma once

#include "SDL_Model.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>

/*! \brief
*
* Classe Sprite
* Model responsável por armazenar sprites SDL 
*
* */

class Sprite{
	private:
		SDL_Texture *texture;
		std::shared_ptr<SDL_Model> sdl;
	public:
		/*! \brief Construtor do Sprite
		*
		* Inicializa e salva o sprite
		*
		* \param const char *dir nome do arquivo contendo o sprite
		* \return Nada (este é um construtor!)
		* */
		Sprite(char const *dir, std::shared_ptr<SDL_Model> sdl);
		/*! \brief Destrutor do Sprite
		*
		* Destroi textura no SDL
		*
		* \return Nada (este é um destrutor!)
		* */
		~Sprite();

		void set_image(char const *dir);
		SDL_Texture* get_texture();
};
