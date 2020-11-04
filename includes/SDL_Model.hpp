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
		* Inicializa o SDL (renderer e window).
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
		/* \brief Cria uma textura com as linhas e colunas para o mapa
		*
		*
		* \param int num_lines, num_columns Número de linhas e colunas para o mapa
		* \param int block_width, block_height Tamanho de cada quadrado do mapa 
		* \param thickness Grossura de cada linha (opcional)
		* \param r,g,b Valores r,g,b para a cor da linha no mapa (opcional)
		* \return SDL_Texture* textura do mapa
		*/
		SDL_Texture* create_map_texture(int num_lines, int num_columns, int block_width, int block_height, int thickness, int r, int g, int b);
		/* \brief Cria uma textura para o bloco
		* \param int block_width, block_height Tamanho do bloco (em px)
		* \param r,g,b Valores r,g,b para a cor do bloco (opcional)
		* \return SDL_Texture* textura do bloco
		*/
		SDL_Texture* create_block_texture(int block_width, int block_height, int r, int g, int b);
		SDL_Renderer* get_renderer();	
};
