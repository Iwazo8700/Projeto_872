#pragma once

#include "json.hpp"
#include <memory>
#include <vector> 
#include "Sprite.hpp"
#include <unistd.h>
#include <SDL2/SDL_image.h>

using nlohmann::json;

/*! \brief
*
* Classe Bloco
* Model responsável por armazenar os dados de uma peça, 
* guardando seu sprite, sua forma e sua posição
* */

class Bloco {
	private:
		int x; /*!< Coluna da peça relativa ao mapa*/
		int y; /*!< Linha da peça relativa ao mapa*/
		int height; /*!< Altura de cada bloco da peça (em px)*/
		int width;  /*!< Largura de cada bloco da peça (em px)*/
		std::vector<std::vector<bool>> formato; /*!< Matriz representando a forma do bloco*/
		std::shared_ptr<Sprite> sprite; /*!< Shared Pointer para Sprite (previamente alocado) que será usada para renderizar o bloco*/

	public:
		/*! \brief Construtor do Bloco
		*
		* Deve receber dois ints representando sua posição relativa no mapa,
		* uma vector de vector representando o formato da peça, 
		* um shared_ptr para um Sprite que será usado para renderiza-lo
		* e dois ints representando a altura e largura de cada bloco
		*
		* \param std::vector<std::vector<bool>> Um formato para a peça
		* \param int x, y Coordenadas iniciais relativas ao mapa
		* \param Sprite sprite Sprite da peça
		* \param int height, width Tamanho de cada bloco da peça
		* \return Nada (este é um construtor!)
		* */
                Bloco(int x, int y, std::vector<std::vector<bool>> formato, std::shared_ptr<Sprite> sprite, int height, int width);

		Bloco(){};
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Bloco, x, y, formato);

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
