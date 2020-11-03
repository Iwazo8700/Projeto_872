#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Sprite.hpp"
#include <memory>


/*! \brief Classe Image
*
* Classe responsável por guardar todas as informações necessárias para a renderização de uma imagem,
* guardando o seu Sprite, tamanho e posição
*
*/

class Image{
	private:
		SDL_Rect target; /*<! SDL_Rect contendo as posições x,y da imagem e sua altura e largura*/
		std::shared_ptr<Sprite> sprite; /*<! std::shared_ptr<Sprite> para o Sprite contendo a textura que será renderizada*/
	public:
		/*! \brief Construtor da Classe Image
		*
		* Inicializa as variáveis da Image
		*
		* \param int x, y Posições x,y que serão salvas no SDL_Rect target (em px)
		* \param int height, width Altura e largura da imagem que serão salvas no SDL_Rect target (em px)
		* \param std::shared_ptr<Sprite> sprite Ponteiro para Sprite contendo a textura que será renderizada
		* \return Nada (é um Construtor)
		*/
		Image(int x, int y, int width, int height, std::shared_ptr<Sprite> sprite);
		SDL_Rect* get_target();
		SDL_Texture* get_texture();
};		
