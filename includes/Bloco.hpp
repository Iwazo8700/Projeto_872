#pragma once

#include <memory>
#include <vector> 
#include "Sprite.hpp"
#include <unistd.h>
#include <SDL2/SDL_image.h>

/*! \brief
*
* Classe Bloco
* Model responsável por armazenar os dados de um bloco, 
* guardando seu sprite, sua forma e sua posição
* */

class Bloco {
	private:
		int x,y,height,width; /*!< Posição do bloco relativo ao mapa e o tamanho de cada bloco*/
		std::vector<std::vector<bool>> formato; /*!< Matriz representando a forma do bloco*/
		std::shared_ptr<Sprite> sprite; /*!< Shared Pointer para Sprite (previamente alocado) que será usada para renderizar o bloco*/

	public:
		/*! \brief Construtor do Bloco
		*
		* Deve receber um char representando o formato do Bloco, 
		* dois ints representando sua posição relativa no mapa e
		* um shared_ptr para um Sprite que será usado para renderiza-lo
		*
		* \param std::vector<std::vector<bool>> Um formato para a peça
		* \param int x, y Coordenadas iniciais relativas ao mapa
		* \param Sprite sprite Sprite da peça
		* \param int height, width Tamanho de cada bloco da peça
		* \return Nada (este é um construtor!)
		* */
                Bloco(int x, int y, std::vector<std::vector<bool>> formato, std::shared_ptr<Sprite> sprite, int height, int width);

		int get_x();
		int get_y();
		int get_height();
		int get_width();
		SDL_Texture* get_texture();		
		
		std::vector<std::vector<bool>> get_formato();
		std::shared_ptr<Sprite> get_sprite();

		void set_x(int x);
		void set_y(int y);
		void set_formato(std::vector<std::vector<bool>> formato);
		void set_sprite(std::shared_ptr<Sprite> sprite); 
		void set_size(int height, int width);
};
