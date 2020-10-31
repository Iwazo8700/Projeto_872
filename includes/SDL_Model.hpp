#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

/*! \brief Classe SDL_Model
*
* Classe responsável por inicializar e armazenar
* as variáveis relacionadas ao SDL (renderer e window)
* e de finalizar  o SDL com o término do programa
* */

class SDL_Model{
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		int SCREEN_WIDTH, SCREEN_HEIGHT;
	public:
		/*! \brief Construtor da SDL_Model
		*
		* Deve receber a largura e a altura da tela.
		* Inicializa o SDL.
		*
		* \param int width
		* \param int height
		* \return Nada (este é um construtor!)
		* */
		SDL_Model(int width, int height);
		/*! \brief Destrutor da SDL_Model
		*
		* Finaliza o SDL
		* 
		*
		* \param Nada
		* \return Nada (este é um construtor!)
		* */
		~SDL_Model();
		SDL_Renderer* get_renderer();	
};
